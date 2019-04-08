import tensorflow as tf
import image_utils as iu 
import layers as lay

def image_sampling(img, sampling_type='down'):
    shape = img.get_shape()  # [batch, height, width, channels]

    if sampling_type == 'down':
        h = int(shape[1] // 4)
        w = int(shape[2] // 4)
    else:  # 'up'
        h = int(shape[1] * 4)
        w = int(shape[2] * 4)

    return tf.image.resize_images(img, [h, w], tf.image.ResizeMethod.BILINEAR)

class ProgGAN:

    def __init__(self, s, batch_size=64, input_height=28, input_width=28, input_channel=1, n_classes=10,
                 sample_num=10 * 10, sample_size=10, z_dim=62, n_continuos_factor = 2, gf_dim=64, df_dim=64, fc_unit=1024, 
                 g_lr=1e-3, d_lr=2e-4, is_train=True):

        self.s = s
        self.batch_size = batch_size
        self.is_train = is_train

        self.g1 = None
        self.g2 = None
        self.d1 = None
        self.d2 = None

        #Input configuration
        self.input_height = input_height
        self.input_width = input_width
        self.input_channel = input_channel
        self.image_shape = [self.batch_size, self.input_height, self.input_width, self.input_channel]

        self.second_layer = False

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
        self.x2 = tf.placeholder(tf.float32, shape=[None, self.input_height, self.input_width, self.input_channel], name="x-image32x32")
        self.x1 = image_sampling(self.x2)

        self.z = tf.placeholder(tf.float32, shape=[None, self.z_dim], name='z-noise')          # (-1, 128)

        #Variables initialization
        self.d_real1 = 0.
        self.d_fake1 = 0.

        self.g_loss1 = 0.
        self.d_loss1 = 0.

        self.d_op1 = None
        self.g_op1 = None

        self.d_real2 = 0.
        self.d_fake2 = 0.

        self.g_loss2 = 0.
        self.d_loss2 = 0.

        self.d_op2 = None
        self.g_op2 = None

        self.merged = None
        self.writer = None
        self.saver = None

        self.build_prog_gan()

    def fromImage7(self, x):
        with tf.variable_scope("fromimage1", reuse=tf.AUTO_REUSE):
            x_1 = lay.conv2d(x, f=128, k=1, d=1, name='c-conv2d')
            out = tf.nn.leaky_relu(x_1, alpha=0.1)

            return out

    def discriminator1(self, x, reuse=None):
        with tf.variable_scope("discriminator1", reuse=tf.AUTO_REUSE):
            x_1 = tf.layers.flatten(x)

            x_1 = tf.layers.dense(x_1, units=7*7*128, name='d-fc-2')
            x_1 = lay.batch_norm(x_1)
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            x_1 = tf.layers.dense(x_1, units=1024, name='d-fc-1')
            x_1 = lay.batch_norm(x_1)
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            d1 = tf.layers.dense(x_1, units=1, name='d-fc-0')
            prob = tf.nn.sigmoid(d1)

            return prob

    def fromImage28(self, x):
        with tf.variable_scope("fromimage2", reuse=tf.AUTO_REUSE):
            x_1 = lay.conv2d(x, f=32, k=1, d=1, name='c-conv2d')
            out = tf.nn.leaky_relu(x_1, alpha=0.1)

            return out

    def discriminator2(self, x, reuse=None):
        with tf.variable_scope("discriminator2", reuse=tf.AUTO_REUSE):
            #2º discriminator
            x_2 = lay.conv2d(x, f=64, name='d-conv2d-1')
            x_2 = lay.batch_norm(x_2)
            x_2 = tf.nn.leaky_relu(x_2, alpha=0.1)

            x_2 = lay.conv2d(x_2, f=128, name='d-conv2d-0')
            x_2 = lay.batch_norm(x_2)
            out = tf.nn.leaky_relu(x_2, alpha=0.1)

            return out

    def generator1(self, z):
        with tf.variable_scope("generator1", reuse = tf.AUTO_REUSE):
            #1º generator
            x_1 = tf.layers.dense(z, units=1024, name='g-fc-0')
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            x_1 = tf.layers.dense(x_1, units=7*7*128, name='g-fc-1')
            x_1 = tf.nn.leaky_relu(x_1, alpha=0.1)

            out = tf.reshape(x_1, shape=[-1, 7, 7, 128] )

            return out
    
    def toImage7(self, x):
        with tf.variable_scope("toimage1", reuse=tf.AUTO_REUSE):
            x_1 = lay.conv2d(x, f=1, k=1, d=1, name='c-conv2d')
            img = tf.nn.tanh(x_1)

            return img

    def generator2(self, g1):
        with tf.variable_scope("generator2", reuse = tf.AUTO_REUSE):
            #2º generator
            x_2 = lay.deconv2d(g1, f=64, name='g-conv2d-0')
            x_2 = tf.nn.leaky_relu(x_2, alpha=0.1)

            x_2 = lay.deconv2d(x_2, f=32, name='g-conv2d-1')
            out = tf.nn.leaky_relu(x_2, alpha=0.1)

            return out

    def toImage28(self, x):
        with tf.variable_scope("toimage2", reuse=tf.AUTO_REUSE):
            x_1 = lay.conv2d(x, f=1, k=1, d=1, name='c-conv2d')
            img = tf.nn.tanh(x_1)

            return img

    def build_prog_gan(self):
        #Build generator G1(z,c)
        g1 = self.generator1(self.z)
        self.g1 = self.toImage7(g1)

        real_img = self.fromImage7(self.x1)
        fake_img = self.fromImage7(self.g1)

        #Build discriminators (real e fake) D(x)
        d_real1 = self.discriminator1(real_img)
        d_fake1 = self.discriminator1(fake_img, reuse=True)

        d_labels_real1 = tf.ones_like(d_real1) * (0.9)
        d_labels_fake1 = tf.zeros_like(d_real1)

        d_loss_real1 = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_real1, logits=d_real1)
        d_loss_fake1 = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_fake1, logits=d_fake1)

        self.d_loss1 = tf.reduce_mean(d_loss_real1 + d_loss_fake1)

        self.g_loss1 = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(labels=tf.ones_like(d_fake1), logits=d_fake1))

        # Summary
        tf.summary.histogram("z-noise", self.z)
        tf.summary.image("g", self.g1, 5)  # generated images by Generative Model
        tf.summary.scalar("d_loss", self.d_loss1)
        tf.summary.scalar("g_loss", self.g_loss1)

        # Optimizer
        t_vars = tf.trainable_variables()
        d_params1 = [v for v in t_vars if v.name.startswith('discriminator1') or v.name.startswith('fromimage1')]
        g_params1 = [v for v in t_vars if v.name.startswith('generator1') or v.name.startswith('toimage1')]

        self.d_op1 = tf.train.AdamOptimizer(learning_rate=self.d_lr,
                                beta1=self.beta1, beta2=self.beta2).minimize(self.d_loss1, var_list=d_params1)
        self.g_op1 = tf.train.AdamOptimizer(learning_rate=self.g_lr,
                                beta1=self.beta1, beta2=self.beta2).minimize(self.g_loss1, var_list=g_params1)

        ###SECOND LAYER####
        g2 = self.generator2(g1)
        self.g2 = self.toImage28(g2)

        #Build discriminators (real e fake) D(x)
        real_img = self.fromImage28(self.x2)
        fake_img = self.fromImage28(self.g2)

        d2_real = self.discriminator2(real_img)
        d2_fake = self.discriminator2(fake_img, reuse=True)
        
        d_real2 = self.discriminator1(d2_real)
        d_fake2 = self.discriminator1(d2_fake, reuse=True)

        d_labels_real2 = tf.ones_like(d_real2) * (0.9)
        d_labels_fake2 = tf.zeros_like(d_real2)

        d_loss_real2 = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_real2, logits=d_real2)
        d_loss_fake2 = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_fake2, logits=d_fake2)

        self.d_loss2 = tf.reduce_mean(d_loss_real2 + d_loss_fake2)

        self.g_loss2 = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(labels=tf.ones_like(d_fake2), logits=d_fake2))

        # Summary
        tf.summary.histogram("z-noise", self.z)
        tf.summary.image("g", self.g2, 5)  # generated images by Generative Model
        tf.summary.scalar("d_loss", self.d_loss2)
        tf.summary.scalar("g_loss", self.g_loss2)

        # Optimizer
        t_vars = tf.trainable_variables()
        d_params2 = [v for v in t_vars if v.name.startswith('discriminator2') or v.name.startswith('fromimage2')]
        g_params2 = [v for v in t_vars if v.name.startswith('generator2') or v.name.startswith('toimage2')]

        self.d_op2 = tf.train.AdamOptimizer(learning_rate=self.d_lr,
                                beta1=self.beta1, beta2=self.beta2).minimize(self.d_loss2, var_list=d_params2)
        self.g_op2 = tf.train.AdamOptimizer(learning_rate=self.g_lr,
                                beta1=self.beta1, beta2=self.beta2).minimize(self.g_loss2, var_list=g_params2)

        # Merge summary
        self.merged = tf.summary.merge_all()

        # Model saver
        self.saver = tf.train.Saver(max_to_keep=1)
        self.writer = tf.summary.FileWriter('./model/', self.s.graph)