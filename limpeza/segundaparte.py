# -*- coding: utf-8 -*-
"""
Created on Sat May 30 23:12:55 2020

@author: carol

"""
def merge_sort(A):
    if len(A)<=1:
        return A
    left = A[:int(len(A)/2)]
    right = A[int(len(A)/2):]
    return merge(merge_sort(left),merge_sort(right))

def merge(C, B):
    result = []
    while len(C)>0 and len(B)>0:
        if C[0][0]<B[0][0]:
            result.append(C[0])
            C.pop(0)
        else:
            result.append(B[0])
            B.pop(0)
    result += C+B
    return result

arquivo = open("titulos_desordem","r")
titulos = arquivo.readlines()
arquivo.close()
titulos_id = []
for i in range(len(titulos)):
    par = (titulos[i], i)
    titulos_id.append(par)
    
t_ordenados = merge_sort(titulos_id)
"""
lista_de_textos = [None for i in range(137)]
for i in range(137):
    nome = "conteudos_desordem (" + str(i+1) + ")"
    arquivo = open(nome, "r")
    lista_de_textos[i] = arquivo.readlines()
    arquivo.close()
    
re_titulos = open("titulos_ordem", "a")
re_current = open("conteudos_ordem (1)", "a")

quantidade_no_current = 0
indice_do_current = 1

for i in range(len(t_ordenados)):
    re_titulos.write(t_ordenados[i][0])
    
    if quantidade_no_current == 10000:
        re_current.close()
        indice_do_current += 1
        nome = "conteudos_ordem ("+ str(indice_do_current) + ")"
        re_current = open(nome,"a")
        quantidade_no_current = 0
        
        
    indice = t_ordenados[i][1]
    linha = indice // 10000
    coluna = indice % 10000
    
    re_current.write(lista_de_textos[linha][coluna])
    quantidade_no_current += 1
     
    
re_titulos.close()
re_current.close()

"""