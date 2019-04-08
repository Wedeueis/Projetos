import tensorflow as tf


tf.set_random_seed(777)  # reproducibility

class InfoGAN:

    def __init__(self, s, batch_size=64, input_height=28, input_width=28, input_channel=1,
                 sample_num=10 * 10, sample_size=10, output_height=28, output_width=28,
                 df_dim=8, gf_dim=64, fc_unit=128,
                 n_categories=10, n_continous_factor=2, z_dim=62,
                 g_lr=1e-3, d_lr=2e-4, is_train=True):

        self.s = s
        self.batch_size = batch_size
        self.is_train = is_train

        self.input_height = input_height
        self.input_width = input_width
        self.input_channel = input_channel
        self.image_shape = [self.batch_size, self.input_height, self.input_width, self.input_channel]

        self.sample_num = sample_num
        self.sample_size = sample_size
        self.output_height = output_height
        self.output_width = output_width

        self.df_dim = df_dim
        self.gf_dim = gf_dim
        self.fc_unit = fc_unit


        self.n_cat = n_categories         # category dist, label
        self.n_cont = n_continous_factor  # gaussian dist, rotate, etc
        self.z_dim = z_dim
        self.lambda_ = 1  # sufficient for discrete latent codes # less than 1

        self.beta1 = 0.5
        self.beta2 = 0.999
        self.lambd = 1.0
        self.d_lr = d_lr
        self.g_lr = g_lr

        # pre-defined
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
        self.c = tf.placeholder(tf.float32, shape=[None, self.n_cat + self.n_cont], name='c')  # (-1, 12)

        self.build_infogan()  # build InfoGAN model

    def classifier(self, x, reuse=None):
        with tf.variable_scope("classifier", reuse=reuse):
            x = tf.layers.dense(x, units=self.fc_unit, activation=tf.nn.leaky_relu, name='c-fc-1')
            x = tf.layers.batch_normalization(x, training=self.is_train)

            logits = tf.layers.dense(x, units=self.n_cat + self.n_cont, name='c-fc-2')
            prob = tf.nn.softmax(logits)

            return prob, logits

    def discriminator(self, x, reuse=None):
        with tf.variable_scope("discriminator", reuse=reuse):
            x = tf.layers.conv2d(x, 8, 4, 2, activation=tf.nn.leaky_relu, padding='SAME', name='d-conv2d-0')

            x = tf.layers.conv2d(x, 16, 4, 2, activation=tf.nn.leaky_relu, padding='SAME', name='d-conv2d-1')
            x = tf.layers.batch_normalization(x, training=True)

            x = tf.layers.conv2d(x, 32, 4, 2, activation=tf.nn.leaky_relu, padding='SAME', name='d-conv2d-2')
            x = tf.layers.batch_normalization(x, training=True)

            x = tf.layers.flatten(x)

            logits = tf.layers.dense(x, units=1, name='d-fc-1')
            prob = tf.nn.sigmoid(logits)

            return prob, logits, x

    def generator(self, z, c, reuse=None):
        with tf.variable_scope("generator", reuse = tf.AUTO_REUSE):
            x = tf.concat([z, c], axis=1)  # (-1, 74)

            x = tf.layers.dense(x, units= 1024, activation=tf.nn.leaky_relu, name='g-fc-0')
            x = tf.layers.batch_normalization(x, training=True)

            x = tf.layers.dense(x, units= 7*7*self.gf_dim*2, activation=tf.nn.leaky_relu, name='g-fc-1')
            x = tf.layers.batch_normalization(x, training=True)

            x = tf.reshape(x, shape=[-1, 7, 7, self.gf_dim * 2])

            x = tf.layers.conv2d_transpose(x, 64, 4, 2, activation=tf.nn.leaky_relu, padding='SAME', name='g-conv2d-1')
            x = tf.layers.batch_normalization(x, training=True)

            x = tf.layers.conv2d_transpose(x, 1, 4, 2, activation=tf.nn.leaky_relu, padding='SAME', name='g-conv2d-2')
            x = tf.nn.tanh(x)

            return x

    def build_infogan(self):
        # Generator
        self.g = self.generator(self.z, self.c, reuse= not self.is_train)

        # Discriminator
        d_real, d_real_logits, _ = self.discriminator(self.x)
        d_fake, d_fake_logits, d_fake_d = self.discriminator(self.g, reuse=True)

        # Classifier
        c_fake, c_fake_logits = self.classifier(d_fake_d)  # Q net

        # Losses
        d_real_loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(logits=d_real_logits,
                                                                             labels=tf.ones_like(d_real)*(0.9)))
        d_fake_loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(logits=d_fake_logits,
                                                                             labels=tf.zeros_like(d_fake)))
        self.d_loss = d_real_loss + d_fake_loss
        self.g_loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(logits=d_fake_logits,
                                                                             labels=tf.ones_like(d_fake)))

        
        # categorical
        q_cat_logits = c_fake[:, :self.n_cat]
        q_cat_labels = self.c[:, :self.n_cat]
        q_cont_logits = c_fake[:, self.n_cat:]
        q_cont_labels = self.c[:, self.n_cat:]

        #q_cat_loss = tf.reduce_mean(-tf.reduce_sum(tf.log(q_cat_logits + 1e-8) * q_cat_labels, 1))
        q_cat_loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=q_cat_logits,
                                                                            labels=q_cat_labels))
        # gaussian
        q_cont_logits = c_fake[:, self.n_cat:]
        q_cont_labels = self.c[:, self.n_cat:]

        q_cont_loss = tf.reduce_mean(tf.reduce_sum(tf.square(q_cont_labels - q_cont_logits), axis=1))  # l2 loss

        self.q_loss = q_cat_loss + 0.001*q_cont_loss

        # Summary
        tf.summary.histogram("z-noise", self.z)

        tf.summary.image("g", self.g, 5)  # generated images by Generative Model
        tf.summary.scalar("d_loss", self.d_loss)
        tf.summary.scalar("d_real_loss", d_real_loss)
        tf.summary.scalar("d_fake_loss", d_fake_loss)
        tf.summary.scalar("g_loss", self.g_loss)
        tf.summary.scalar("q_loss", self.q_loss)

        # Optimizer
        t_vars = tf.trainable_variables()
        d_params = [v for v in t_vars if v.name.startswith('d')]
        g_params = [v for v in t_vars if v.name.startswith('g')]
        q_params = [v for v in t_vars if v.name.startswith('d') or v.name.startswith('g') or v.name.startswith('c')]

        self.d_op = tf.train.AdamOptimizer(learning_rate=self.d_lr,
                                           beta1=self.beta1, beta2=self.beta2).minimize(self.d_loss, var_list=d_params)
        self.g_op = tf.train.AdamOptimizer(learning_rate=self.g_lr,
                                           beta1=self.beta1, beta2=self.beta2).minimize(self.g_loss, var_list=g_params)
        self.q_op = tf.train.AdamOptimizer(learning_rate=self.g_lr,
                                           beta1=self.beta1, beta2=self.beta2).minimize(self.q_loss, var_list=d_params + g_params + q_params)

        # Merge summary
        self.merged = tf.summary.merge_all()

        # Model saver
        self.saver = tf.train.Saver(max_to_keep=1)
        self.writer = tf.summary.FileWriter('./model/', self.s.graph)
