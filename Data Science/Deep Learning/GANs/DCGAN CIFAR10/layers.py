import numpy as np

import tensorflow as tf

def conv2d(x, f=64, k=4, d=2, pad='SAME', name='conv2d'):
    return tf.layers.conv2d(x, filters=f, kernel_size=k, strides=d, padding=pad, name=name)

def deconv2d(x, f=64, k=4, d=2, pad='SAME', name='deconv2d'):
    return tf.layers.conv2d_transpose(x, filters=f, kernel_size=k, strides=d, padding=pad, name=name)
									  
def batch_norm(x, momentum=0.9, eps=1e-5):
    return tf.layers.batch_normalization(inputs=x, momentum=momentum, epsilon=eps, scale=True, training=True)