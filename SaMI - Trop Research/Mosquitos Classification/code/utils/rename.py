import glob, os
import sys

def rename(dir, pattern):
    i=148
    for pathAndFilename in glob.iglob(os.path.join(dir, pattern)):
        title, ext = os.path.splitext(os.path.basename(pathAndFilename))
        os.rename(pathAndFilename, os.path.join(dir, str(i) + ext))
        i+= 1

rename(sys.argv[1], "*")