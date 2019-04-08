import sys
import os
import subprocess 

dir = sys.argv[1]
print(dir)

for file in os.listdir(dir):
    path = dir + file
    result = subprocess.call(["identify", path])
    if result == 1:
        print("error")
        subprocess.call(["rm", path])