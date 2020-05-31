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

titulos = open("titulos_desordem","r")
teste1 = titulos.readlines()
titulos.close()