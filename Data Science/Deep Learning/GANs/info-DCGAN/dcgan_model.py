import tensorflow as tf


tf.set_random_seed(777)  # reproducibility


class DCGAN:

    def __init__(self, s, batch_size=64, input_height=28, input_width=28, channel=1, n_classes=10,
                 sample_num=10 * 10, sample_size=10, output_height=28, output_width=28,
                 n_input=784, fc_unit=128,
                 z_dim=100, g_lr=8e-4, d_lr=8e-4):

        self.s = s
        self.batch_size = batch_size

        self.input_height = input_height
        self.input_width = input_width
        self.channel = channel
        self.n_classes = n_classes

        self.sample_num = sample_num
        self.sample_size = sample_size
        self.output_height = output_height
        self.output_width = output_width

        self.n_input = n_input
        self.fc_unit = fc_unit

        self.z_dim = z_dim
        self.beta1 = 0.5
        self.d_lr, self.g_lr = d_lr, g_lr

        # pre-defined
        self.d_loss = 0.
        self.g_loss = 0.

        self.d_op = None
        self.g_op = None

        self.merged = None
        self.writer = None
        self.saver = None

        # Placeholder
        self.x = tf.placeholder(tf.float32, shape=[None, self.input_height, self.input_width, self.channel], name="x-image")  # (-1, 784)
        self.z = tf.placeholder(tf.float32, shape=[None, self.z_dim], name='z-noise')    # (-1, 100)

        self.build_gan()  # build GAN model

    def discriminator(self, x, reuse=None):
        with tf.variable_scope('discriminator', reuse=reuse):
            # Conv 1
            conv1 = tf.layers.conv2d(x, 8, 5, 2, activation=tf.nn.leaky_relu, padding='SAME')
            
            # Conv 2
            conv2 = tf.layers.conv2d(conv1, 16, 5, 2, activation=tf.nn.leaky_relu, padding='SAME')
            batch_norm2 = tf.layers.batch_normalization(conv2, training=True)
            
            # Conv 3
            conv3 = tf.layers.conv2d(batch_norm2, 32, 5, 2, activation=tf.nn.leaky_relu, padding='SAME')
            batch_norm3 = tf.layers.batch_normalization(conv3, training=True)
           
            # Flatten
            flat = tf.reshape(batch_norm3, (-1, 4*4*32))
            
            # Logits
            logits = tf.layers.dense(flat, 1, activation=None)
            
            # Output
            out = tf.sigmoid(logits)
            
            return out, logits

    def generator(self, z, is_train=True):
        with tf.variable_scope('generator', reuse=False if is_train==True else True):
            # First fully connected layer
            x_1 = tf.layers.dense(z, 2*2*25, activation=tf.nn.leaky_relu)
            
            # Reshape it to start the convolutional stack
            deconv_2 = tf.reshape(x_1, (-1, 2, 2, 25))
            batch_norm2 = tf.layers.batch_normalization(deconv_2, training=is_train)
            
            # Deconv 1
            deconv3 = tf.layers.conv2d_transpose(batch_norm2, 256, 5, 2, activation=tf.nn.leaky_relu, padding='VALID')
            batch_norm3 = tf.layers.batch_normalization(deconv3, training=is_train)
            
            # Deconv 2
            deconv4 = tf.layers.conv2d_transpose(batch_norm3, 128, 5, 2, activation=tf.nn.leaky_relu, padding='SAME')
            batch_norm4 = tf.layers.batch_normalization(deconv4, training=is_train)
            
            # Output layer
            logits = tf.layers.conv2d_transpose(batch_norm4, self.channel, 5, 2, activation=tf.nn.leaky_relu, padding='SAME')
            
            out = tf.tanh(logits)
            
            return out,  logits

    def build_gan(self):
        # Generator
        self.g, g_logits = self.generator(self.z)

        # Discriminator
        d_real, d_logits_real = self.discriminator(self.x)
        d_fake, d_logits_fake = self.discriminator(self.g, reuse=True)

        # Calculate losses
        d_labels_real = tf.ones_like(d_logits_real) * (0.9)
        d_labels_fake = tf.zeros_like(d_logits_fake)

        d_loss_real = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_real, logits=d_logits_real)
        d_loss_fake = tf.nn.sigmoid_cross_entropy_with_logits(labels=d_labels_fake, logits=d_logits_fake)

        self.d_loss = tf.reduce_mean(d_loss_real + d_loss_fake)

        self.g_loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(labels=tf.ones_like(d_logits_fake), logits=d_logits_fake))

        # Summary
        tf.summary.histogram("z-noise", self.z)
        tf.summary.histogram("d_real", d_real)
        tf.summary.histogram("d_fake", d_fake)
        tf.summary.scalar("d_loss", self.d_loss)
        tf.summary.scalar("g_loss", self.g_loss)

        # Optimizer
        t_vars = tf.trainable_variables()
        d_params = [v for v in t_vars if v.name.startswith('discriminator')]
        g_params = [v for v in t_vars if v.name.startswith('generator')]

        self.d_op = tf.train.AdamOptimizer(learning_rate=self.d_lr,beta1=self.beta1).minimize(self.d_loss, var_list=d_params)
        self.g_op = tf.train.AdamOptimizer(learning_rate=self.g_lr,beta1=self.beta1).minimize(self.g_loss, var_list=g_params)

        # Merge summary
        self.merged = tf.summary.merge_all()

        # Model saver
        self.saver = tf.train.Saver(max_to_keep=1)
        self.writer = tf.summary.FileWriter('./model/', self.s.graph)
