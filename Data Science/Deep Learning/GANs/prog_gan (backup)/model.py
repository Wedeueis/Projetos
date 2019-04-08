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

        self.g = []
        self.d = []

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
        self.x1 = tf.placeholder(tf.float32, shape=[None, 4, 4, 
                                    self.input_channel], name="x-image4x4")
        self.x2 = tf.placeholder(tf.float32, shape=[None, 8, 8, 
                                    self.input_channel], name="x-image8x8") 
        self.x3 = tf.placeholder(tf.float32, shape=[None, 16, 16, 
                                    self.input_channel], name="x-image16x16") 
        self.x4 = tf.placeholder(tf.float32, shape=[None, 32, 32, 
                                    self.input_channel], name="x-image32x32")
        self.x = [self.x1, self.x2, self.x3, self.x4]

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
            #Input layer
            x_4 = lay.conv2d(x[4], f=8, k=1, name='d-conv2d-8')
            x_4 = tf.nn.leaky_relu(x_4, alpha=0.1)

            #1º discriminator
            x_4 = lay.conv2d(x_4, f=8, name='d-conv2d-7')
            x_4 = tf.nn.leaky_relu(x_4, alpha=0.1)

            x_4 = lay.conv2d(x_4, f=16, name='d-conv2d-6')
            x_4 = tf.nn.leaky_relu(x_4, alpha=0.1)

            d4 = tf.layers.flatten(x_4)
            d4 = tf.layers.dense(d4, units=1, name='d-fc-3')

            #2º discriminator
            x_3 = lay.conv2d(x_4, f=16, name='d-conv2d-5')
            x_3 = tf.nn.leaky_relu(x_3, alpha=0.1)

            x_3 = lay.conv2d(x_3, f=32, name='d-conv2d-4')
            x_3 = tf.nn.leaky_relu(x_3, alpha=0.1)

            d3 = tf.layers.flatten(x_3)
            d3 = tf.layers.dense(d3, units=1, name='d-fc-2')

            #3º discriminator
            x_2 = lay.conv2d(x_3, f=32, name='d-conv2d-3')
            x_2 = tf.nn.leaky_relu(x_2, alpha=0.1)

            x_2 = lay.conv2d(x_2, f=64, name='d-conv2d-2')
            x_2 = tf.nn.leaky_relu(x_2, alpha=0.1)

            d2 = tf.layers.flatten(x_2)
            d2 = tf.layers.dense(d2, units=1, name='d-fc-1')

            #4º discriminator
            x_1 = lay.conv2d(x_2, f=64, name='d-conv2d-1')
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            x_1 = lay.conv2d(x_1, f=64, k=4, name='d-conv2d-0')
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            #Output
            x_out = tf.layers.flatten(x_1)

            d1 = tf.layers.dense(x_out, units=1, name='d-fc-0')
            #prob = tf.nn.sigmoid(d4)

            return [d1, d2, d3, d4]

    def generator(self, z, reuse=None):
        with tf.variable_scope("generator", reuse = tf.AUTO_REUSE):
            #Input layer
            x_1 = tf.layers.dense(z, 4*4*64)

            #1º generator
            x_1 = tf.reshape(x_1, shape=[-1, 4, 4, 64])

            x_1 = lay.deconv2d(x_1, f=64, k=4, name='g-conv2d-0')
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            x_1 = lay.deconv2d(x_1, f=64, name='g-conv2d-1')
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            g1 = tf.nn.tanh(x_1)

            #2º generator
            x_2 = lay.deconv2d(x_1, f=32, name='g-conv2d-2')
            x_2 = tf.nn.leaky_relu(x_2, alpha=0.1)

            x_2 = lay.deconv2d(x_2, f=32, name='g-conv2d-3')
            x_2 = tf.nn.leaky_relu(x_2, alpha=0.1)

            g2 = tf.nn.tanh(x_2)

            #3º generator
            x_3 = lay.deconv2d(x_2, f=16, name='g-conv2d-4')
            x_3 = tf.nn.leaky_relu(x_3, alpha=0.1)

            x_3 = lay.deconv2d(x_3, f=16, name='g-conv2d-5')
            x_3 = tf.nn.leaky_relu(x_3, alpha=0.1)

            g3 = tf.nn.tanh(x_3)

            #4º generator
            x_4 = lay.deconv2d(x_3, f=8, name='g-conv2d-6')
            x_4 = tf.nn.leaky_relu(x_4, alpha=0.1)

            x_4 = lay.deconv2d(x_4, f=8, name='g-conv2d-7')
            x_4 = tf.nn.leaky_relu(x_4, alpha=0.1)

            #Output
            x_out = lay.deconv2d(x_4, f=3, name='g-conv2d-8')
            g4 = tf.nn.tanh(x_out)

            return [g1, g2, g3, g4]

    def build_prog_gan(self):
        #Build generator G(z,c)
        self.g = self.generator(self.z, reuse= not self.is_train)

        #Build discriminators (real e fake) D(x)
        d_real = self.discriminator(self.x)
        d_fake = self.discriminator(self.g[0], reuse=True)

        d_labels_real = tf.ones_like(d_logits_real) * (0.9)
        d_labels_fake = tf.zeros_like(d_logits_fake)

        d_loss_real = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_real, logits=d_logits_real)
        d_loss_fake = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_fake, logits=d_logits_fake)

        self.d_loss = tf.reduce_mean(d_loss_real + d_loss_fake)

        self.g_loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(labels=tf.ones_like(d_logits_fake), logits=d_logits_fake))

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