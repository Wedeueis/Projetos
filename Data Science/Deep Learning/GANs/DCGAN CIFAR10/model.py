import tensorflow as tf
import image_utils as iu 
import layers as lay

class ProgGAN:

    def __init__(self, s, batch_size=64, input_height=32, input_width=32, input_channel=3, n_classes=10,
                 sample_num=10 * 10, sample_size=10, z_dim=100, gf_dim=64, df_dim=64, fc_unit=1024, 
                 g_lr=1e-3, d_lr=2e-4, is_train=True):

        self.s = s
        self.batch_size = batch_size
        self.is_train = is_train

        #Input configuration
        self.input_height = input_height
        self.input_width = input_width
        self.input_channel = input_channel
        self.image_shape = [self.batch_size, self.input_height, self.input_width, self.input_channel]

        #Output configuration
        self.sample_size = sample_size
        self.sample_num = sample_num

        #Networks configuration
        self.n_classes = n_classes
        self.z_dim = z_dim
        self.gf_dim = gf_dim
        self.df_dim = df_dim
        self.fc_unit = fc_unit

        #Hiperparameters
        self.beta1 = 0.5
        self.beta2 = 0.999
        self.d_lr = d_lr
        self.g_lr = g_lr

		# Placeholders
        self.x = tf.placeholder(tf.float32, shape=[None, self.input_height, self.input_width, 
                                    self.input_channel], name="x-image")  # (-1, 32, 32, 1)
        self.z = tf.placeholder(tf.float32, shape=[None, self.z_dim], name='z-noise')          # (-1, 100)

        #Variables initialization
        self.d_real = 0.
        self.d_fake = 0.

        self.g_loss = 0.
        self.d_loss = 0.

        self.d_op = None
        self.g_op = None

        self.merged = None
        self.writer = None
        self.saver = None

        self.build_prog_gan()

    def discriminator(self, x, reuse=None):
        with tf.variable_scope("discriminator", reuse=reuse):
            x = lay.conv2d(x, f=self.df_dim, name='d-conv2d-0')
            x = tf.nn.leaky_relu(x, alpha=0.1)

            x = lay.conv2d(x, f=self.df_dim *2, name='d-conv2d-1')
            x = lay.batch_norm(x)
            x = tf.nn.leaky_relu(x, alpha=0.1)

            x = tf.layers.flatten(x)

            x = tf.layers.dense(x, units=self.fc_unit, name='d-fc-0')
            x = lay.batch_norm(x)
            x = tf.nn.leaky_relu(x, alpha=0.1)

            logits = tf.layers.dense(x, units=1, name='d-fc-1')
            prob = tf.nn.sigmoid(logits)

            return prob, logits, x

    def generator(self, z, reuse=None):
        with tf.variable_scope("generator", reuse = tf.AUTO_REUSE):
            x = tf.layers.dense(z, units= self.fc_unit, name='g-fc-0')
            x = lay.batch_norm(x)
            x = tf.nn.leaky_relu(x, alpha=0.1)

            x = tf.layers.dense(x, units= 8*8*self.gf_dim*2, name='g-fc-1')
            x = lay.batch_norm(x)
            x = tf.nn.leaky_relu(x, alpha=0.1)

            x = tf.reshape(x, shape=[-1, 8, 8, self.gf_dim * 2])

            x = lay.deconv2d(x, f=self.gf_dim, name='g-conv2d-0')
            x = lay.batch_norm(x)
            x = tf.nn.leaky_relu(x, alpha=0.1)

            x = lay.deconv2d(x, f=3, name='g-conv2d-1')
            x = tf.nn.tanh(x)

            return x

    def build_prog_gan(self):
        #Build generator G(z,c)
        self.g = self.generator(self.z, reuse= not self.is_train)

        #Build discriminators (real e fake) D(x)
        d_real, _, _ = self.discriminator(self.x)
        d_fake, _, _ = self.discriminator(self.g, reuse=True)

        # Losses
        self.d_loss = - tf.reduce_mean(tf.log(d_real + 1e-8) + tf.log(1. - d_fake + 1e-8))
        self.g_loss = - tf.reduce_mean(tf.log(d_fake + 1e-8))

        # Summary
        tf.summary.histogram("z-noise", self.z)
        tf.summary.image("g", self.g, 5)  # generated images by Generative Model
        tf.summary.scalar("d_loss", self.d_loss)
        tf.summary.scalar("d_loss", self.d_loss)
        tf.summary.scalar("g_loss", self.g_loss)

        # Optimizer
        t_vars = tf.trainable_variables()
        d_params = [v for v in t_vars if v.name.startswith('d')]
        g_params = [v for v in t_vars if v.name.startswith('g')]

        self.d_op = tf.train.AdamOptimizer(learning_rate=self.d_lr,
                                beta1=self.beta1, beta2=self.beta2).minimize(self.d_loss, var_list=d_params)
        self.g_op = tf.train.AdamOptimizer(learning_rate=self.g_lr,
                                beta1=self.beta1, beta2=self.beta2).minimize(self.g_loss, var_list=g_params)

        # Merge summary
        self.merged = tf.summary.merge_all()

        # Model saver
        self.saver = tf.train.Saver(max_to_keep=1)
        self.writer = tf.summary.FileWriter('./model/', self.s.graph)