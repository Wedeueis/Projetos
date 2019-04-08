import tensorflow as tf


tf.set_random_seed(777)


# In image_utils, up/down_sampling
def image_sampling(img, sampling_type='down'):
    shape = img.get_shape()  # [batch, height, width, channels]

    if sampling_type == 'down':
        h = int(shape[1] // 2)
        w = int(shape[2] // 2)
    else:  # 'up'
        h = int(shape[1] * 2)
        w = int(shape[2] * 2)

    return tf.image.resize_images(img, [h, w], tf.image.ResizeMethod.BILINEAR)


class LAPGAN:

    def __init__(self, s, batch_size=64, input_height=28, input_width=28, input_channel=1, n_classes=10,
                 sample_num=10 * 10, sample_size=10,
                 z_dim=100, gf_dim=64, df_dim=64, fc_unit=128):

        self.s = s
        self.batch_size = batch_size
        self.input_height = input_height
        self.input_width = input_width
        self.input_channel = input_channel
        self.n_classes = n_classes

        self.sample_size = sample_size
        self.sample_num = sample_num

        self.image_shape = [self.input_height, self.input_width, self.input_channel]

        self.z_dim = z_dim

        self.gf_dim = gf_dim
        self.df_dim = df_dim
        self.fc_unit = fc_unit

        # Placeholders
        self.y = tf.placeholder(tf.float32, shape=[None, self.n_classes], name='y-classes')  # one_hot

        self.x1_fine = tf.placeholder(tf.float32,
                                      shape=[None, self.input_height, self.input_width, self.input_channel],
                                      name='x-images')
        self.x1_scaled = image_sampling(self.x1_fine, 'down')
        self.x1_coarse = image_sampling(self.x1_scaled, 'up')
        self.x1_diff = self.x1_fine - self.x1_coarse

        self.x2_fine = self.x1_scaled  # [16, 16]
        self.x2_scaled = image_sampling(self.x2_fine, 'down')
        self.x2_coarse = image_sampling(self.x2_scaled, 'up')
        self.x2_diff = self.x2_fine - self.x2_coarse

        self.x3_fine = self.x2_scaled  # [8, 8]

        self.z = []
        self.z_noises = [28 * 28, 16 * 16, self.z_dim]
        for i in range(3):
            self.z.append(tf.placeholder(tf.float32,
                                         shape=[None, self.z_noises[i]],
                                         name='z-noise_{0}'.format(i)))

        self.g = []       # generators
        self.g_loss = []  # generator losses

        self.d_reals = []  # discriminator_real logit
        self.d_fakes = []  # discriminator_fake logit
        self.d_reals_prob = []  # discriminator_real prob
        self.d_fakes_prob = []  # discriminator_fake prob
        self.d_loss = []  # discriminator_real losses

        # Training Options
        self.d_op = []
        self.g_op = []

        self.beta1 = 0.5
        self.beta2 = 0.9
        self.learning_rate = 8e-4
        self.lr = tf.train.exponential_decay(
            learning_rate=self.learning_rate,
            decay_rate=0.9,
            decay_steps=150,
            global_step=750,
            staircase=False,
        )

        self.saver = None
        self.merged = None
        self.writer = None

        self.bulid_lapgan()  # build LAPGAN model

    def discriminator(self, x1, x2, y, scale=28, reuse=None):
        with tf.variable_scope('discriminator_{0}'.format(scale), reuse=reuse):
            if scale == 8:
                x1 = tf.reshape(x1, [-1, scale * scale * 3])

                h = tf.concat([x1, y], axis=1)

                h = tf.layers.dense(h, self.fc_unit, activation=tf.nn.leaky_relu, name='d-fc-1')
                h = tf.layers.dropout(h, 0.5, name='d-dropout-1')
                h = tf.layers.dense(h, self.fc_unit // 2, activation=tf.nn.leaky_relu, name='d-fc-2')
                h = tf.layers.dropout(h, 0.5, name='d-dropout-2')
                h = tf.layers.dense(h, 1, name='d-fc-3')
            else:
                x = x1 + x2

                y = tf.layers.dense(y, scale * scale, activation=tf.nn.leaky_relu, name='d-fc-1')
                y = tf.reshape(y, [-1, scale, scale, 1])

                h = tf.concat([x, y], axis=3)

                h = tf.layers.conv2d(h, self.df_dim, 5, 1, activation=tf.nn.leaky_relu, padding='valid', name='d-conv-1')
                h = tf.layers.conv2d(h, self.df_dim, 5, 1, activation=None, padding='valid', name='d-conv-2')

                h = tf.layers.flatten(h)
                h = tf.nn.leaky_relu(h)
                h = tf.layers.dropout(h, 0.5,  name='d-dropout-1')

                h = tf.layers.dense(h, 1, name='d-fc-2')

            return h

    def generator(self, x, y, z, scale=28, reuse=None):
        with tf.variable_scope('generator_{0}'.format(scale), reuse=reuse):
            if scale == 8:
                h = tf.concat([z, y], axis=1)

                # FC Layers
                h = tf.layers.dense(h, self.fc_unit, activation=tf.nn.leaky_relu, name='g-fc-1')
                h = tf.layers.dropout(h, 0.5, name='g-dropout-1')
                h = tf.layers.dense(h, self.fc_unit // 2, activation=tf.nn.leaky_relu, name='g-fc-2')
                h = tf.layers.dropout(h, 0.5, name='g-dropout-2')
                h = tf.layers.dense(h, 3 * 8 * 8, name='g-fc-3')

                h = tf.reshape(h, [-1, 8, 8, 3])
            else:
                y = tf.layers.dense(y, scale * scale, name='g-fc-0')
                y = tf.reshape(y, [-1, scale, scale, 1])
                z = tf.reshape(z, [-1, scale, scale, 1])

                h = tf.concat([z, y, x], axis=3)  # concat into 5 dims

                # Convolution Layers
                for idx in range(1, scale // 8 - 1):
                    h = tf.layers.conv2d(h, self.gf_dim, 5, 1, activation=tf.nn.leaky_relu, padding='SAME', name='g-deconv-{0}'.format(idx))

                h = tf.layers.conv2d(h, 3, 5, 1, activation=None, padding='SAME', name='g-deconv-{0}'.format(scale // 8))

            return h

    def bulid_lapgan(self):
        def sce_loss(x, y):
            return tf.nn.sigmoid_cross_entropy_with_logits(logits=x, labels=y)

        # Generator & Discriminator
        g1 = self.generator(x=self.x1_coarse, y=self.y, z=self.z[0], scale=28)
        d1_fake = self.discriminator(x1=g1, x2=self.x1_coarse, y=self.y, scale=28)
        d1_real = self.discriminator(x1=self.x1_diff, x2=self.x1_coarse, y=self.y, scale=28, reuse=True)

        g2 = self.generator(x=self.x2_coarse, y=self.y, z=self.z[1], scale=16)
        d2_fake = self.discriminator(x1=g2, x2=self.x2_coarse, y=self.y, scale=16)
        d2_real = self.discriminator(x1=self.x2_diff, x2=self.x2_coarse, y=self.y, scale=16, reuse=True)

        g3 = self.generator(x=None, y=self.y, z=self.z[2], scale=8)
        d3_fake = self.discriminator(x1=g3, x2=None, y=self.y, scale=8)
        d3_real = self.discriminator(x1=self.x3_fine, x2=None, y=self.y, scale=8, reuse=True)

        self.g = [g1, g2, g3]
        self.d_reals = [d1_real, d2_real, d3_real]
        self.d_fakes = [d1_fake, d2_fake, d3_fake]

        # Prob
        m_sigmoid = lambda x: tf.reduce_mean(tf.sigmoid(x))
        with tf.variable_scope('prob'):
            for i in range(len(self.g)):
                self.d_reals_prob.append(m_sigmoid(self.d_reals[i]))
                self.d_fakes_prob.append(m_sigmoid(self.d_fakes[i]))

        # Losses
        with tf.variable_scope('loss'):
            for i in range(len(self.g)):
                self.d_loss.append(tf.reduce_mean(sce_loss(self.d_reals[i], tf.ones_like(self.d_reals[i])) +
                                                  sce_loss(self.d_fakes[i], tf.zeros_like(self.d_fakes[i])),
                                                  name="d_loss_{0}".format(i)))
                self.g_loss.append(tf.reduce_mean(sce_loss(self.d_fakes[i], tf.ones_like(self.d_fakes[i])),
                                                  name="g_loss_{0}".format(i)))

        # Summary
        for i in range(len(self.g)):
            # tf.summary.scalar('d_real_{0}'.format(i), self.d_reals[i])
            # tf.summary.scalar('d_fake_{0}'.format(i), self.d_fakes[i])
            tf.summary.scalar('d_real_prob_{0}'.format(i), self.d_reals_prob[i])
            tf.summary.scalar('d_fake_prob_{0}'.format(i), self.d_fakes_prob[i])
            tf.summary.scalar('d_loss_{0}'.format(i), self.d_loss[i])
            tf.summary.scalar('g_loss_{0}'.format(i), self.g_loss[i])

            tf.summary.histogram("z_{0}".format(i), self.z[i])

        # tf.summary.image("g", g1)  # generated image from G model

        # Optimizer
        t_vars = tf.trainable_variables()
        for idx, i in enumerate([28, 16, 8]):
            self.d_op.append(tf.train.AdamOptimizer(learning_rate=self.learning_rate,
                                                    beta1=self.beta1, beta2=self.beta2).
                             minimize(loss=self.d_loss[idx],
                                      var_list=[v for v in t_vars if v.name.startswith('discriminator_{0}'.format(i))]))
            self.g_op.append(tf.train.AdamOptimizer(learning_rate=self.learning_rate,
                                                    beta1=self.beta1, beta2=self.beta2).
                             minimize(loss=self.g_loss[idx],
                                      var_list=[v for v in t_vars if v.name.startswith('generator_{0}'.format(i))]))

        # Merge summary
        self.merged = tf.summary.merge_all()

        # Model Saver
        self.saver = tf.train.Saver(max_to_keep=1)
        self.writer = tf.summary.FileWriter('./model/', self.s.graph)
