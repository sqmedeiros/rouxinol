from signal import signal
import sys
import pandas
import matplotlib.pyplot as plt
import numpy as np
import os
from scipy import stats

def carregacsvs(arq1, arq2):
    df1 = pandas.read_csv(arq1)
    nomes1 = df1['nome'].to_numpy()
    slopes1 = df1['slopes'].to_numpy()

    df2 = pandas.read_csv(arq2)
    nomes2 = df2['nome'].to_numpy()
    slopes2 = df2['slopes'].to_numpy()

    if not((nomes1 == nomes2).all):
        print('arquivos com nomes diferentes')
        exit()
    return slopes1, slopes2, nomes1


def classificaGeral(slopes1, slopes2):
    n = slopes1.size
    nacertos = np.zeros(n)
    vacertos = np.zeros((n, n))
    for i in range(0,n):
        nacertos[i], vacertos[i,:] = classificaN(slopes1, slopes2, i)
    return nacertos, vacertos

def classificaN(slopes1, slopes2, N):
    n = slopes1.size
    acertou = np.zeros(n)
    for i in range(n):
        p = slopes1[i]
        diff = np.abs(slopes2 - p)
        acertou[i] = nmenor(diff, N, i)
    nacertos = np.sum(acertou)
    return nacertos, acertou
   
def nmenor(diff, N, indiceproblema):
    for i in range(N):
        index = np.argmin(diff)
        if index == indiceproblema:
            return 1
        else:
            diff[index] = 999
    return 0
    

def grafico(nacertos):
    n = nacertos.size
    x = range(0,n)
    plt.plot(x,nacertos)
    plt.show()

arquivos = sys.argv
narq = len(arquivos)

arq1 = arquivos[1]
arq2 = arquivos[2]

slopes1, slopes2, nomes = carregacsvs(arq1, arq2)
nacertos, vacertos = classificaGeral(slopes1, slopes2)
print(nacertos)
grafico(nacertos)
np.set_printoptions(threshold=np.inf)
print(vacertos)