import sys
import re
import os
import numpy
import scipy.spatial

#Classe que armazena os conteúdos extraídos das Bulas e mantém uma lista 
#de medicamentos similares appós o cáculo de similaridade
class BULA:
    def __init__(self, fileName=None):
        self.regexIndicacao = r"INDICADO\?(?s)(.*?)2\."
        self.regexComposicao = r"COMPOSIÇÃO(?s)(.*?)1\."
        self.regexPalavra = r"[-'a-zA-ZÀ-ÖØ-öø-ÿ0-9]+"
        self.name = ""
        self.indicacaoTxt = ""
        self.composicaoTxt = ""
        self.indicacao = []
        self.composicao = []
        self.similares = []
        if fileName is not None:
            self.loadData(fileName)

    def loadData(self, fileName):
        document = open("BULAS/" + fileName,'r')
        content  = document.read()

        stopwordsPTfile = open("stopwords-pt.txt",'r')
        stopwords       = set([]) 
        for s in stopwordsPTfile.readlines():
            stopwords.add(s.strip().lower())

        self.name = fileName[:len(fileName)-4]

        rawIndicacao = re.findall(self.regexIndicacao, content)
        self.indicacaoTxt = rawIndicacao[0]
        rawwords = re.findall(self.regexPalavra, self.indicacaoTxt)
        for w in rawwords:
            if w not in stopwords:
                self.indicacao.append(w)
        
        rawComposicao = re.findall(self.regexComposicao, content)
        self.composicaoTxt = rawComposicao[0]
        rawwords = re.findall(self.regexPalavra, self.composicaoTxt)
        for w in rawwords:
            if w not in stopwords:
                self.composicao.append(w)

    def inserirSimilar(self, tupla):
        def getKey(item):
            return item[1]
        self.similares.append(tupla)
        self.similares.sort(key=getKey, reverse=True)

#Classe que mantém a lista de todas as bulas geradas bem como o vocabulários para a seção de composição e indicações
class Medicamentos:
    def __init__(self, path):
        self.Names = []
        self.Composicao = dict([])
        self.CompVocabulary = set([])
        self.Indicacao = dict([])
        self.IndVocabulary = set([])
        self.BULAS = dict([])
        self.N = 0
        if path is not None:
            self.loadData(path)
            self.N = len(self.Composicao)
            self.Names = list(self.Composicao.keys())

    def loadData(self, path):
        for fileName in os.listdir(path):
            bula = BULA(fileName)
            self.BULAS[fileName[:len(fileName)-4]] = bula
            self.Composicao[fileName[:len(fileName)-4]] = bula.composicao
            self.CompVocabulary.update(bula.composicao)
            self.Indicacao[fileName[:len(fileName)-4]] = bula.indicacao
            self.IndVocabulary.update(bula.indicacao)

#Classe responsável pelo cáculo de similaridade, criação do grafo e da busca
class GrafoSimilaridade:
    def __init__(self, medicamentos, alpha):
        self.similaridade = []
        self.alpha = alpha
        self.medicamentos = medicamentos
        self.grafo = ""
        if medicamentos is not None:
            self.calc()

    def calc(self):
        MatrizComp = self.matrizTermoDoc(self.medicamentos.Composicao, self.medicamentos.CompVocabulary)
        MatrizInd = self.matrizTermoDoc(self.medicamentos.Indicacao, self.medicamentos.IndVocabulary)
        distComp = self.distDoc(MatrizComp, self.medicamentos.N)
        distInd = self.distDoc(MatrizInd, self.medicamentos.N)
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
                #dist[d1,d2] = numpy.linalg.norm(matriz[:,d1]-matriz[:,d2])
                dist[d1,d2] = scipy.spatial.distance.cosine(matriz[:,d1], matriz[:,d2])
        return dist

    def criarGrafo(self, documents, dist, n):
        txtGraph = "\ngraph{"
        for d1 in range(0, n-1): 
            for d2 in range(d1+1, n): 
                if dist[d1,d2]!=numpy.nan and dist[d1,d2]>=0.4:
                    txtGraph += '\n "{0}" -- "{1}"[label="{2:.2f}", penwidth={2:.2f}]'. format(documents[d1], documents[d2], dist[d1,d2] )
                    self.medicamentos.BULAS[documents[d1]].inserirSimilar((documents[d2], dist[d1,d2]))
                    self.medicamentos.BULAS[documents[d2]].inserirSimilar((documents[d1], dist[d1,d2]))
        txtGraph += "\n}"
        return txtGraph

    def busca(self, name):
        if name in self.medicamentos.BULAS:
            print("\nComposição:")
            print(self.medicamentos.BULAS[name].composicaoTxt)
            print("Indicação:")
            print(self.medicamentos.BULAS[name].indicacaoTxt)
            print("Medicamentos Similares")
            for b in self.medicamentos.BULAS[name].similares:
                print("Nome: " + b[0] + " Similaridade: " + "{0:.2f}".format(b[1]) )
            print("\n")
        else:
            print("\nNão encontrado.\nDigite apenas com a primeira letra maiúscula.\n")

if __name__ == '__main__':    
    alpha = 0.5 #variável entre 0 e 1 que controla a importancia dada para informações das seções
                #valores maiores que 0.5 dão mais importância para composição, menores dão mais 
                #importância para indicações
    
    if len(sys.argv)>1:
        alpha = float(sys.argv[1])
    
    grafo = GrafoSimilaridade(Medicamentos("BULAS/"), alpha)

    while(True):
        userInput = input("Digite a Opção: \n\tbusca\n\tgrafo\n\tsair\n")
        if userInput == "busca":
            opcao = input("\nDigite o nome do medicamento\n")
            grafo.busca(opcao)
        elif userInput == "grafo":
            print(grafo.grafo)
        elif userInput == "sair":
            break
        else:
            print("Não entendi.")