import sys
import re
import os
import numpy

class MED:
    def __init__(self, fileName=None):
        self.regexIndicacao = r"INDICADO\?(?s)(.*?)2\."
        self.regexComposicao = r"COMPOSIÇÃO(?s)(.*?)1\."
        self.name = ""
        self.indicacao = ""
        self.composicao = ""
        if fileName is not None:
            self.loadData(fileName)

    def loadData(self, fileName):
        document = open("BULAS/" + fileName,'r')
        content  = document.read()
        self.name = fileName[:len(fileName)-4]
        words = re.findall(self.regexIndicacao, content)
        self.indicacao = words[0]
        words = re.findall(self.regexComposicao, content)
        self.composicao = words[0]

class Medicamentos:
    def __init__(self, path):
        self.regex = r"[-'a-zA-ZÀ-ÖØ-öø-ÿ0-9]+"   # portuguese words
        self.Names = []
        self.Composicao = dict([])
        self.CompVocabulary = set([])
        self.Indicacao = dict([])
        self.IndVocabulary = set([])
        self.MEDS = dict([])
        self.N = 0
        if path is not None:
            self.loadData(path)
            self.N = len(self.Composicao)
            self.Names = list(self.Composicao.keys())

    def loadData(self, path):
        for fileName in os.listdir(path):
            self.MEDS[fileName[:len(fileName)-4]] = MED(fileName)
            words = re.findall(self.regex, self.MEDS[fileName[:len(fileName)-4]].composicao)
            self.Composicao[fileName[:len(fileName)-4]] = words
            self.CompVocabulary.update(words)
            words = re.findall(self.regex, self.MEDS[fileName[:len(fileName)-4]].indicacao)
            self.Indicacao[fileName[:len(fileName)-4]] = words
            self.IndVocabulary.update(words)

class GrafoSimilaridade:
    def __init__(self, medicamentos, alpha):
        self.similaridade = []
        self.alpha = alpha
        self.medicamentos = medicamentos
        self.grafo = ""
        if medicamentos is not None:
            self.calc()

    def calc(self):
        MatrizComp = matrizTermoDoc(self.medicamentos.Composicao, self.medicamentos.CompVocabulary)
        MatrizInd = matrizTermoDoc(self.medicamentos.Indicacao, self.medicamentos.IndVocabulary)
        distComp = distDoc(MatrizComp, self.medicamentos.N)
        distInd = distDoc(MatrizInd, self.medicamentos.N)
        distTotal = self.alpha*distComp + (1-self.alpha)*distInd
        self.similaridade = 1 - (distTotal-numpy.nanmin(distTotal))/(numpy.nanmax(distTotal)-numpy.nanmin(distTotal))
        self.grafo = self.criarGrafo(self.medicamentos.Names, self.similaridade, self.medicamentos.N)

    def matrizTermoDoc(self, document, vocabulary):
        D = len(document)
        V = len(vocabulary)
        M          = numpy.zeros((V, D))
        documents  = list(document.keys())
        vocabulary = list(vocabulary)
        for j in range(0, D):
            d = documents[j]       
            for i in range(0, V):
                w      = vocabulary[i]       
                M[i,j] = document[d].count(w)

        return M

    def distDoc(self, matriz, n):
        # distancia entre documentos
        dist = numpy.ones((n,n))*numpy.nan
        for d1 in range(0, n-1): 
            for d2 in range(d1+1, n): 
                dist[d1,d2] = numpy.linalg.norm(matriz[:,d1]-matriz[:,d2])
        return dist

    def criarGrafo(self, documents, dist, n):
        txtGraph = "\ngraph{"
        for d1 in range(0, n-1): 
            for d2 in range(d1+1, n): 
                if dist[d1,d2]!=numpy.nan and dist[d1,d2]>=0.5:
                    txtGraph += '\n "{0}" -- "{1}"[label="{2:.2f}", penwidth={2:.2f}]'. format(documents[d1], documents[d2], dist[d1,d2] )
        txtGraph += "\n}"
    
        return txtGraph


def matrizTermoDoc(document, vocabulary):
    D = len(document)
    V = len(vocabulary)
    M          = numpy.zeros((V, D))
    documents  = list(document.keys())
    vocabulary = list(vocabulary)
    for j in range(0, D):
        d = documents[j]       
        for i in range(0, V):
            w      = vocabulary[i]       
            M[i,j] = document[d].count(w)

    return M

def distDoc(matriz, n):
    # distancia entre documentos
    dist = numpy.ones((n,n))*numpy.nan
    for d1 in range(0, n-1): 
        for d2 in range(d1+1, n): 
            dist[d1,d2] = numpy.linalg.norm(matriz[:,d1]-matriz[:,d2])
    return dist

def criarGrafo(documents, dist, n):
    txtGraph = "\ngraph{"
    for d1 in range(0, n-1): 
        for d2 in range(d1+1, n): 
          if dist[d1,d2]!=numpy.nan and dist[d1,d2]>=0.5:
              txtGraph += '\n "{0}" -- "{1}"[label="{2:.2f}", penwidth={2:.2f}]'. format(documents[d1], documents[d2], dist[d1,d2] )
    txtGraph += "\n}"
   
    return txtGraph

if __name__ == '__main__':    
    alpha = float(sys.argv[1])

    grafo = GrafoSimilaridade(Medicamentos("BULAS/"), alpha)
    print(grafo.grafo)