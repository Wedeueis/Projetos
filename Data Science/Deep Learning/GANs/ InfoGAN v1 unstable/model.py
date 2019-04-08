import tensorflow as tf
import numpy as np

tf.set_random_seed(777)

def conv2d(x, f=64, k=4, d=2, pad='SAME', name='conv2d'):
    return tf.layers.conv2d(x,
                            filters=f, kernel_size=k, strides=d,
                            padding=pad, name=name)

def deconv2d(x, f=64, k=4, d=2, pad='SAME', name='deconv2d'):
    return tf.layers.conv2d_transpose(x,
                                      filters=f, kernel_size=k, strides=d,
                                      padding=pad, name=name)
									  
def batch_norm(x, momentum=0.9, eps=1e-5, is_train=True):
    return tf.layers.batch_normalization(inputs=x,
                                         momentum=momentum,
                                         epsilon=eps,
                                         scale=True,
                                         training=is_train)

class InfoGAN:

	def __init__(self, s, batch_size=128, input_height=28, input_width=28, input_channel=1,
					sample_num=10 * 10, sample_size=10, output_height=28, output_width=28,
			        dfilters_dim=128, gfilters_dim=64, fc_unit=1024, 
					n_categories=10, z_dim=62, n_continuos_factor = 2,
			        conv_kernel_dim = 4, conv_stride = 2, g_lr=1e-3, d_lr=2e-4, is_train=True):
		self.s = s
		self.batch_size = batch_size
		self.is_train = is_train

        
		#Input configuration
		self.input_height = input_height
		self.input_width = input_width
		self.input_channel = input_channel
		self.image_shape = [self.batch_size, self.input_height, self.input_width, self.input_channel]

		#Output configuration
		self.sample_num = sample_num
		self.sample_size = sample_size
		self.output_height = output_height
		self.output_width = output_width

		#Networks configuration
		self.n_cat = n_categories
		self.n_cont = n_continuos_factor
		self.z_dim = z_dim
		self.df_dim = dfilters_dim
		self.gf_dim = gfilters_dim
		self.fc_unit = fc_unit
		self.conv_k = conv_kernel_dim
		self.conv_s = conv_stride

		#Hiperparameters
		self.beta1 = 0.5
		self.beta2 = 0.999
		self.cat_lambda = 1.0
		self.cont_lambda = 0.001
		self.d_lr = d_lr
		self.g_lr = g_lr
		self.TINY = 1e-8

		#Variables initialization
		self.d_real = 0.
		self.d_fake = 0.

		self.g_loss = 0.
		self.d_loss = 0.
		self.q_loss = 0.

		self.d_op = None
		self.g_op = None
		self.q_op = None

		self.merged = None
		self.writer = None
		self.saver = None

		# Placeholders
		self.x = tf.placeholder(tf.float32,
		                        shape=[None, self.input_height, self.input_width, self.input_channel],
		                        name="x-image")                                                # (-1, 28, 28, 1)
		self.z = tf.placeholder(tf.float32, shape=[None, self.z_dim], name='z-noise')          # (-1, 62)
		self.c = tf.placeholder(tf.float32, shape=[None, self.n_cat + + self.n_cont], name='c')  # (-1, 10)

		self.build_infogan()  # build InfoGAN model

	def classifier(self, x, reuse=None):
		with tf.variable_scope("classifier", reuse=reuse):
			x = tf.layers.dense(x, units=128, name='d-fc-1')
			x = batch_norm(x, is_train=self.is_train)
			x = tf.nn.leaky_relu(x, alpha=0.1)

			logits = tf.layers.dense(x, units=self.n_cat + self.n_cont, name='d-fc-2')
			prob = tf.nn.sigmoid(logits)

			return prob, logits


	def discriminator(self, x, reuse=None):
		with tf.variable_scope("discriminator", reuse=reuse):
			x = conv2d(x, f=self.df_dim, name='d-conv2d-0')
			x = tf.nn.leaky_relu(x, alpha=0.1)
			
			x = conv2d(x, f=self.df_dim *2, name='d-conv2d-1')
			x = batch_norm(x, is_train=self.is_train)
			x = tf.nn.leaky_relu(x, alpha=0.1)

			x = tf.layers.flatten(x)

			x = tf.layers.dense(x, units=self.fc_unit, name='d-fc-0')
			x = batch_norm(x, is_train=self.is_train)
			x = tf.nn.leaky_relu(x, alpha=0.1)

			logits = tf.layers.dense(x, units=1, name='d-fc-1')
			prob = tf.nn.sigmoid(logits)

			return prob, logits, x

	def generator(self, z, c, reuse=None):
		with tf.variable_scope("generator", reuse = tf.AUTO_REUSE):
			x = tf.concat([z, c], axis=1)  # (-1, 74)

			x = tf.layers.dense(x, units= self.fc_unit, name='g-fc-0')
			x = batch_norm(x, is_train=self.is_train)
			x = tf.nn.leaky_relu(x, alpha=0.1)

			x = tf.layers.dense(x, units= 7*7*self.gf_dim*2, name='g-fc-1')
			x = batch_norm(x, is_train=self.is_train)
			x = tf.nn.leaky_relu(x, alpha=0.1)

			x = tf.reshape(x, shape=[-1, 7, 7, self.gf_dim * 2])

			x = deconv2d(x, f=self.gf_dim, name='g-conv2d-0')
			x = batch_norm(x, is_train=self.is_train)
			x = tf.nn.leaky_relu(x, alpha=0.1)

			x = deconv2d(x, f=1, name='g-conv2d-1')
			x = tf.nn.tanh(x)

			return x

	def build_infogan(self):
		#Build generator G(z,c)
		self.g = self.generator(self.z, self.c, reuse= not self.is_train)

		#Build discriminators (real e fake) D(x)
		d_real, d_real_logits, _ = self.discriminator(self.x)
		d_fake, d_fake_logits, d_fake_d = self.discriminator(self.g, reuse=True)

		# Classifier Q(x)
		c_fake, c_fake_logits = self.classifier(d_fake_d)

		# Losses
		self.d_loss = - tf.reduce_mean(tf.log(d_real + 1e-8) + tf.log(1. - d_fake + 1e-8))
		self.g_loss = - tf.reduce_mean(tf.log(d_fake + 1e-8))

		#Categorical
		q_cat = c_fake[:, :self.n_cat]

		cat_dist_prob = tf.ones([self.batch_size, self.n_cat]) * (1.0 / self.n_cat)
		cat_dist = tf.reduce_sum(tf.log(cat_dist_prob+ 1e-8) * cat_dist_prob, 1)
		cat_dist_h = tf.reduce_mean(-cat_dist)

		cat_Qcx = tf.reduce_sum(tf.log(q_cat + 1e-8) * self.c[:, :self.n_cat], 1)
		cat_cond_h = tf.reduce_mean(-cat_Qcx)

		q_cat_loss = self.cat_lambda * (cat_dist_h-cat_cond_h)

		#Continuos
		q_cont = c_fake[:, self.n_cat:]

		mean = tf.zeros([self.batch_size, self.n_cont])
		stddev = tf.ones([self.batch_size, self.n_cont])

		epsilon_prior = (self.c[:, self.n_cat:] - mean) / (stddev + self.TINY)
		cont_dist = tf.reduce_sum( - 0.5 * np.log(2 * np.pi) - tf.log(stddev + self.TINY) - 0.5 * tf.square(epsilon_prior),reduction_indices=1,)
		cont_dist_h = tf.reduce_mean(-cont_dist)

		epsilon_est = (q_cont - mean) / (stddev + self.TINY)
		cont_Qcx = tf.reduce_sum( - 0.5 * np.log(2 * np.pi) - tf.log(stddev + self.TINY) - 0.5 * tf.square(epsilon_est),reduction_indices=1,)
		cont_cond_h = tf.reduce_mean(-cont_Qcx)

		#l2_loss = tf.reduce_mean(tf.reduce_sum(tf.square(self.c[:, self.n_cat:] - q_cont), axis=1))
		#q_cont_loss = self.cont_lambda * l2_loss

		q_cont_loss = self.cont_lambda * (cont_dist_h - cont_cond_h)

		self.q_loss = - (q_cat_loss + q_cont_loss)

		# Summary
		tf.summary.histogram("z-noise", self.z)
		tf.summary.image("g", self.g, 5)  # generated images by Generative Model
		tf.summary.scalar("d_loss", self.d_loss)
		tf.summary.scalar("g_loss", self.g_loss)
		tf.summary.scalar("q_loss", q_cat_loss + q_cont_loss)

		# Optimizer
		t_vars = tf.trainable_variables()
		d_params = [v for v in t_vars if v.name.startswith('d')]
		g_params = [v for v in t_vars if v.name.startswith('g')]
		q_params = [v for v in t_vars if v.name.startswith('c') or v.name.startswith('g')]

		self.d_op = tf.train.AdamOptimizer(learning_rate=self.d_lr,
		                               beta1=self.beta1, beta2=self.beta2).minimize(self.d_loss, var_list=d_params)
		self.g_op = tf.train.AdamOptimizer(learning_rate=self.g_lr,
		                               beta1=self.beta1, beta2=self.beta2).minimize(self.g_loss, var_list=g_params)
		self.q_op = tf.train.AdamOptimizer(learning_rate=self.g_lr,
		                               beta1=self.beta1, beta2=self.beta2).minimize(self.q_loss, var_list=q_params)

		# Merge summary
		self.merged = tf.summary.merge_all()

		# Model saver
		self.saver = tf.train.Saver(max_to_keep=1)
		self.writer = tf.summary.FileWriter('./model/', self.s.graph)