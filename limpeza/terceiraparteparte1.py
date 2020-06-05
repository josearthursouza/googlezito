# -*- coding: utf-8 -*-
"""
Created on Wed Jun  3 23:06:53 2020

@author: carol
"""
import re
import unicodedata

dicionario = {}

for indice_conteudos in range(70):
    nome = "conteudos_ordem (" + str(indice_conteudos+1) + ")"
    arquivo = open(nome, "r")
    print("{} no dicionario".format(indice_conteudos))
    for indice_linha in range(10000):
        if(indice_conteudos == 136 and indice_linha>1):
            break
            
        frase = arquivo.readline()    
        lista = frase.split()
        listaboa = []
        for palavra in lista:
            palavra = palavra.lower()
            if(re.search("áàãâôõóòêéèîíìçñ", palavra) != None):
                continue
            palavra = unicodedata.normalize('NFKD', palavra).encode('ASCII', 'ignore').decode('ASCII')
            palavra = re.sub('[^a-z0-9]', "", palavra)
            if palavra not in listaboa:
                try: 
                    dicionario[palavra].append(10000*indice_conteudos+indice_linha+1)
                except:
                    dicionario[palavra] = [10000*indice_conteudos+indice_linha+1]
            listaboa.append(palavra)
    arquivo.close()



current_escrever = open("palavras_ids_A (1)", "a")    
palavras_escritas = 0
documentos_escritos = 1
palavras_escritas_total = 0
for palavra_escrever in dicionario:
    current_escrever.write(palavra_escrever)
    current_escrever.write("\n")
    for id_escrever in dicionario[palavra_escrever]:
        current_escrever.write(str(id_escrever))
        current_escrever.write(" ")
    current_escrever.write("\n")
    palavras_escritas += 1
    palavras_escritas_total += 1
    print("escrevendo palavra {} de {}".format(palavras_escritas_total, len(dicionario)))
    if palavras_escritas == int(1000*1.1222**documentos_escritos):
        palavras_escritas = 0
        current_escrever.close()
        documentos_escritos += 1
        nome_escrever = "palavras_ids_A (" + str(documentos_escritos)+ ")"
        current_escrever = open(nome_escrever, "a")
        
        
current_escrever.close()
