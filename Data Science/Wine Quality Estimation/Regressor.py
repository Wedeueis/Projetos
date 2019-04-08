import csv
import numpy as np
from sklearn import linear_model
from sklearn.model_selection import KFold
from sklearn.tree import DecisionTreeRegressor
from sklearn.neighbors import KNeighborsRegressor
import matplotlib.pyplot as plt
import sys

###Pré processamento dos dados

#Lendo a base de dados de um arquivo csv
if len(sys.argv) != 2:
    print("Please inform the filename")
    exit(1)

fname = sys.argv[1]

try:
    #Lendo a base de dados de um arquivo csv
	csv_file_object = csv.reader(open(fname),
							delimiter=',', quotechar='"')
except IOError:
    print("File %s doesn't exist" % fname)
    exit(1)
data = []
for row in csv_file_object:
	data.append(row)

data = np.array(data)

#Separando os atributos das etiquetas
s = len(data[0])-1
X = data[:,:s]
X = X.astype(np.float)
y = data[:,s]
y = y.astype(np.float)

#Normalizando a amplitude
norm_x = X / X.max(axis=0)

###Treinamento e teste do modelo

#10-fold Cross Validation
kf = KFold(n_splits=10)
errs = []

for train_index, test_index in kf.split(norm_x):
	X_train, X_test = norm_x[train_index], norm_x[test_index]
	y_train, y_test = y[train_index], y[test_index]

	#Criando o modelo de regressão linear
	#regr = linear_model.LinearRegression()
	#regr = DecisionTreeRegressor(max_depth=4)
	regr = KNeighborsRegressor(n_neighbors=22)

	#Treinando o modelo na base de treinamento
	regr.fit(X_train, y_train)

	#RSS
	err = np.sum((regr.predict(X_test) - y_test) ** 2)
	print("RSS: %.2f" % err)

	#Pontuação em variancia explicada: 1 é uma previsão perfeita
	var = regr.score(X_test, y_test)
	print('R^2: %.2f' % var)

	errs.append((err, var))

###Resultados

#Média dos erros das 10 iterações
sumx = 0
sumy = 0

for (x,y) in errs:
	sumx += x
	sumy += y

mean_err = sumx/len(errs)
mean_var= sumy/len(errs)

print("RSS médio: %.2f" % mean_err)
print("R^2 médio: %.2f" % mean_var)