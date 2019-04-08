from __future__ import absolute_import
from __future__ import print_function
from __future__ import division

import tensorflow as tf
import numpy as np

import sys
import time

import model as infogan

sys.path.append('../')
import image_utils as iu
from tensorflow.examples.tutorials.mnist import input_data


results = {
    'output': './gen_img/',
    'checkpoint': './model/checkpoint',
    'model': './model/InfoGAN-model.ckpt'
}

train_step = {
    'global_step': 100001,
    'logging_interval': 200,
}


def main():
    start_time = time.time()  # Clocking start

    # MNIST Dataset load
    mnist = input_data.read_data_sets('../data/MNIST_data', one_hot=True)

    # GPU configure
    config = tf.ConfigProto()
    config.gpu_options.allow_growth = True

    with tf.Session(config=config) as s:
        # InfoGAN Model
        model = infogan.InfoGAN(s)

        # Initializing
        s.run(tf.global_variables_initializer())

        sample_x, _ = mnist.test.next_batch(model.sample_num)
        sample_x = np.reshape(sample_x, [-1] + model.image_shape[1:])
        sample_z = np.random.uniform(-1., 1., [model.sample_num, model.z_dim]).astype(np.float32)
        sample_c = np.zeros(shape=[model.sample_num, model.n_cat])
        k = 0
        for j in range(100):
            sample_c[j][k] = 1
            j+=1
            k+=1
            if k == 10:
                k = 0

        d_overpowered = False
        for step in range(train_step['global_step']):
            batch_x, _ = mnist.train.next_batch(model.batch_size)
            batch_x = np.reshape(batch_x, [-1] + model.image_shape[1:])
            batch_x = batch_x*2 - 1
            batch_z = np.random.uniform(-1., 1., [model.batch_size, model.z_dim]).astype(np.float32)
            batch_c = np.random.multinomial(1, model.n_cat*[1.0/model.n_cat], size=model.batch_size)

            # Update D network
            if not d_overpowered:
                _, d_loss = s.run([model.d_op, model.d_loss],
                    feed_dict={model.x: batch_x,model.z: batch_z,model.c: batch_c,})

            # Update G network
            _, g_loss = s.run([model.g_op, model.g_loss],
                feed_dict={ model.x: batch_x,model.z: batch_z,model.c: batch_c,})

            _, q_loss = s.run([model.q_op, model.q_loss], feed_dict={model.x: batch_x, model.z:batch_z, model.c: batch_c})

            d_overpowered = d_loss < g_loss / 2

            # Logging
            if step % train_step['logging_interval'] == 0:
                batch_x, _ = mnist.test.next_batch(model.batch_size)
                batch_x = np.reshape(batch_x, [-1] + model.image_shape[1:])
                batch_x = batch_x*2 - 1
                batch_z = np.random.uniform(-1., 1., [model.batch_size, model.z_dim]).astype(np.float32)
                batch_c = np.random.multinomial(1, model.n_cat*[1.0/model.n_cat], size=model.batch_size)

                d_loss, g_loss, q_loss, summary = s.run([model.d_loss, model.g_loss, model.q_loss, model.merged],
                                                feed_dict={model.x: batch_x,model.z: batch_z,model.c: batch_c,})

                d_overpowered = d_loss < g_loss / 2

                # Print loss
                print("[+] Step %08d => " % step,
                      "Dloss: {:.8f}".format(d_loss),
                      "Gloss: {:.8f}".format(g_loss),
                      "Qloss: {:.8f}".format(-q_loss))

                # Training G model with sample image and noise
                samples = s.run(model.g,
                                feed_dict={model.x: sample_x,model.z: sample_z,model.c: sample_c})

                # Summary saver
                model.writer.add_summary(summary, step)

                # Export image generated by model G
                sample_image_height = model.sample_size
                sample_image_width = model.sample_size
                sample_dir = results['output'] + 'train_{:08d}.png'.format(step)

                # Generated image save
                iu.save_images(samples,
                               size=[sample_image_height, sample_image_width],
                               image_path=sample_dir)

                # Model save
                model.saver.save(s, results['model'], global_step=step)

    end_time = time.time() - start_time  # Clocking end

    # Elapsed time
    print("[+] Elapsed time {:.8f}s".format(end_time))

    # Close tf.Session
    s.close()


if __name__ == '__main__':
    main()