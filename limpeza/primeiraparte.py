# -*- coding: utf-8 -*-
"""
Created on Sat May 30 13:22:31 2020

@author: carol
"""

def achatitulo(poema):
    inicio = poema.find('title') + 7
    fim = poema[inicio:].find('"') + inicio
    return poema[inicio:fim]

def achaconteudo(poema):
    inicio = poema.find('>') + 1
    resultado = poema[inicio:]
    resultado.replace("\n", " ")
    return resultado

current = open("conteudos_desordem (1)", "a")
titulos = open("titulos_desordem", "a")
quantidade_no_current = 0
indice_do_current = 1

for i in range(1,155):
    k = 0
    nome = "amigavel (" + str(i) + ")"
    arquivo = open(nome,"r")
    integro = arquivo.read()
    arquivo.close()

    integro = integro.replace("ENDOFARTICLE", " ")
    integro = integro.replace("\n", " ")
    textos =  integro.split("</doc>")
    tam_do_curr = len(textos)
    escritos_dos_textos = 0
    
    while escritos_dos_textos<tam_do_curr:
        if quantidade_no_current < 10000:
            current.write(achaconteudo(textos[escritos_dos_textos]))
            current.write("\n")
            titulos.write(achatitulo(textos[escritos_dos_textos]))
            titulos.write("\n")
            escritos_dos_textos+=1
            quantidade_no_current+=1
        else:
            current.close()
            indice_do_current +=1
            outronome = "conteudos_desordem (" + str(indice_do_current) + ")"
            current = open(outronome, "a")
            quantidade_no_current = 0
            
current.close()
titulos.close()
            