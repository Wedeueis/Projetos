import csv
import numpy as np
from sklearn import svm
from sklearn.model_selection import KFold
from sklearn.ensemble import ExtraTreesClassifier
from sklearn.feature_selection import SelectFromModel
from sklearn.model_selection import GridSearchCV
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

#Buscar importancia dos atributos
forest = ExtraTreesClassifier()
forest = forest.fit(norm_x, y)
importances = forest.feature_importances_
std = np.std([tree.feature_importances_ for tree in forest.estimators_],
             axis=0)
indices = np.argsort(importances)[::-1]

#Printar o rank dos atributos
print("Feature ranking:")

for f in range(X.shape[1]):
    print("%d. feature %d (%f)" % (f + 1, indices[f], importances[indices[f]]))

#Plotar a importancia dos atributos
plt.figure()
plt.title("Importancia dos atributos")
plt.bar(range(X.shape[1]), importances[indices],
       color="r", yerr=std[indices], align="center")
plt.xticks(range(X.shape[1]), indices)
plt.xlim([-1, X.shape[1]])
plt.show()

#Selecionar os atributos
model = SelectFromModel(forest, prefit=True)
new_x = model.transform(norm_x)
print(new_x.shape)

###Treinamento e teste do modelo

#10-fold Cross Validation
kf = KFold(n_splits=10,shuffle=True)
print(kf)
scrs = []
C = 1.0
for train_index, test_index in kf.split(new_x):
	X_train, X_test = new_x[train_index], new_x[test_index]
	y_train, y_test = y[train_index], y[test_index]

	#Criando o modelo de regressão linear
	clf = svm.SVC(kernel='linear', C=C)
	#Treinando o modelo na base de treinamento
	clf.fit(X_train, y_train)
	#Desempenho na base de teste
	score = clf.score(X_test, y_test)
	print("Score: %.2f" % score)

	scrs.append(score)

###Resultados

#Média dos erros das 10 iterações
sumx = 0

for x in scrs:
	sumx += x

mean_scr = sumx/len(scrs)

print("Score médio: %.2f" % mean_scr)

svr = svm.SVC()
parameters = {'kernel':('linear', 'rbf'), 'C':[1, 10, 100]}
grid = GridSearchCV(svr, parameters, cv=10)
grid.fit(new_x, y)
print()
print("Modelo final:")
print("Melhor score alcançado: %.2f" % grid.best_score_)
print("Parametros encontrados: ", grid.best_params_)
print()
