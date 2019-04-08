import cv2
import glob
import numpy as np

def log(text= "teste"):
    print(text)

def read_data(path, table, label=None):
    query = path + "*"
    for file in glob.glob(query):
        img = cv2.imread(file)
        img = cv2.resize(img, (320, 240), cv2.INTER_CUBIC )
        flat = np.append(img.flatten(), label)
        table += [flat]

table = []

read_data("mosquitos_clean/Aedes/", table, 0)
read_data("mosquitos_clean/Culex/", table, 1)

print(len(table))

np.savetxt("mosquitos.csv", table, delimiter= ",",  fmt ='%s' )

