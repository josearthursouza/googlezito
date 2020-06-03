# -*- coding: utf-8 -*-
"""
Created on Sun May 31 20:40:32 2020

@author: carol
"""
import unicodedata

def remove_accents(input_str):
    nfkd_form = unicodedata.normalize('NFKD', input_str)
    return u"".join([c for c in nfkd_form if not unicodedata.combining(c)])

def unique(conjunto):
    listaruim = conjunto.split(" ")
    listaboa = []
    for i_unique in listaruim:
        if i_unique not in listaboa:
            listaboa.append(i_unique)
    return listaboa

def extrair_palavras(poema):
    limpando = remove_accents(poema)
    limpando = limpando.lower()
    alfabeto =[" ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","0","1","2","3","4","5","6","7","8","9"]
    for letra_extrair in limpando:
        if letra_extrair not in alfabeto:
           limpando = limpando.replace(letra_extrair," ")
    palavras_extrair = unique(limpando)
    while True:
        try:
            palavras_extrair.remove('')
        except:
            break
    while True:
        try:
            palavras_extrair.remove(" ")
        except:
            break
    return palavras_extrair

  
dicionario = {}

for indice_conteudos in range(2):
    nome = "conteudinhos_ordem (" + str(indice_conteudos+1) + ").txt"
    arquivo = open(nome, "r")
    textos_dicionario = arquivo.readlines()
    arquivo.close()
    print(" {} no dicionario".format(indice_conteudos))
    for indice_linha in range(len(textos_dicionario)):
        palavras_dicionario = extrair_palavras(textos_dicionario[indice_linha])
        for palavra_d in palavras_dicionario:
            try: 
                dicionario[palavra_d].append(10000*indice_conteudos+indice_linha+1)
            except:
                dicionario[palavra_d] = [10000*indice_conteudos+indice_linha+1]
                
print("Acabou de fazer o dicionário")
"""
lista_palavras = []     
for i in dicionario:
    lista_palavras.append([i,dicionario[i]])
    
print("Acabou de transformar em lista")
    
fracao = len(dicionario) / 100
palavras_escritas = 0
quantos_documentos = 0
while palavras_escritas < len(lista_palavras):
    nome = "palavras_ids (" +str(quantos_documentos + 1) + ")"
    current = open(nome, "a")
    for i in range(fracao*quantos_documentos, fracao*quantos_documentos + fracao):
        current.write(lista_palavras[i][0])
        current.write("\n")
        palavras_escritas += 1
        for ident in lista_palavras[i][1]:
            current.write(str(ident))
            current.write(" ")
        current.write("\n")
    current.close()
    quantos_documentos += 1
    
    """
    
    
    
fracao = len(dicionario)//3
current_escrever = open("palavras_ids (1)", "a")    
palavras_escritas = 0
documentos_escritos = 1
for palavra_escrever in dicionario:
    current_escrever.write(palavra_escrever)
    current_escrever.write("\n")
    for id_escrever in dicionario[palavra_escrever]:
        current_escrever.write(str(id_escrever))
        current_escrever.write(" ")
    current_escrever.write("\n")
    palavras_escritas += 1
    print("escrevendo palavra {} de {}".format(fracao*(documentos_escritos-1)+palavras_escritas, len(dicionario)))
    if palavras_escritas == fracao:
        palavras_escritas = 0
        current_escrever.close()
        documentos_escritos += 1
        nome_escrever = "palavras_ids (" + str(documentos_escritos)+ ")"
        current_escrever = open(nome_escrever, "a")
        
        
current_escrever.close()