"""
Script to convert images to tfrecords format
usage: python images_to_tfrecords.py <list of images> -o <output>
"""
import tensorflow as tf
import scipy.ndimage
import numpy as np
import argparse
import os.path


HEIGHT = 200
WIDTH = 3

def _bytes_feature(value):
    return tf.train.Feature(bytes_list=tf.train.BytesList(value=[value]))

"""
Read points into a matrix collectively
"""
def read_points(filenames):
    points = np.zeros((len(filenames), HEIGHT, WIDTH), dtype=np.uint8)

    for i,pt in enumerate(filenames):
        print('Processing {} as class {}'.format(pt))
        points[i] = np.loadtxt(pt)

    return points


def convert(filenames, output):
    points = read_points(filenames)

    print('Writing output to {}'.format(output))
    with tf.python_io.TFRecordWriter(output) as writer:
        for p in points:
            raw = p.tostring()
            example = tf.train.Example(features=tf.train.Features(feature={
                'point_raw': _bytes_feature(raw)
            }))
            writer.write(example.SerializeToString())

def main():
    # Read arguments
    parser = argparse.ArgumentParser()
    parser.add_argument('source', nargs='+', help='list of image(s)')
    parser.add_argument('-o', '--output', default='result.tfrecords', help='output filename, default to result.tfrecords')

    args = parser.parse_args()

    # Convert!
    convert(args.source, args.output)

if __name__ == '__main__':
    main()