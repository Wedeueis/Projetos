# coding=utf8
import sys
import re

#regex = r"[-'a-zA-ZÀ-ÖØ-öø-ÿ]+"   # raw string
#regex = r"[-'a-zA-ZÀ-ÖØ-öø-ÿ0-9]+"   # raw string
#regex = r"1. PARA QUE ESTE MEDICAMENTO É INDICADO?"
regex = r"INDICADO\?(?s)(.*?)2\."


if __name__ == '__main__':
    fileName = sys.argv[1]

    document = open(fileName,'r')

    content  = document.read()
    # document.read()       # devolve o conteudo do arquivo 'fileName'
    # document.readline()   # devolve a seguinte linha do arquivo 'fileName'
    # document.readlines()  # devolve uma lista de linhas do arquivo 'fileName'


    #words = re.findall(regex, content)
    words = re.findall(regex, content)
    indicacao = words[0]
    print (indicacao)


    #words = re.finditer(regex, content)
    #for w in words:
    #    print ("{} : {}-{}".format(w.group(), w.start(), w.end()) )


    print ( "\nQuantidade de palavras: {}".format(len(words)) ) 