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
    try:
        lincoeff1 = df1['lincoeff'].to_numpy()
    except:
        lincoeff1 = np.zeros(len(slopes1))

    df2 = pandas.read_csv(arq2)
    nomes2 = df2['nome'].to_numpy()
    slopes2 = df2['slopes'].to_numpy()
    try:
        lincoeff2 = df2['lincoeff'].to_numpy()
    except:
        lincoeff2 = np.zeros(len(slopes2))

    if not((nomes1 == nomes2).all):
        print('arquivos com nomes diferentes')
        exit()
    return slopes1, slopes2, lincoeff1, lincoeff2, nomes1


def classificaGeral(slopes1, slopes2, lincoeff1, lincoeff2):
    n = slopes1.size
    nacertos = np.zeros(n)
    vacertos = np.zeros((n, n))
    for i in range(n):
        nacertos[i], vacertos[i,:] = classificaN(slopes1, slopes2, lincoeff1, lincoeff2, i)
    return nacertos, vacertos

def distancia(s, l, slopes, lincoeff):
    diffs = (slopes - s)**2
    diffl = (lincoeff - l)**2
    difft = (diffs + diffl)**(1/2)
    return difft


def classificaN(slopes1, slopes2, lincoeff1, lincoeff2, N):
    n = slopes1.size
    acertou = np.zeros(n)
    for i in range(n):
        s = slopes1[i]
        l = lincoeff1[i]
        diff = distancia(s,l,slopes2,lincoeff2)
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
    plt.grid()
    plt.yticks(np.arange(0, n+1, 1))
    plt.show()

def imprimeaceretoproblemas(vacertos, nomes, ax):
    print('numero de acertos em funcao de n e probelmas classificados corretamente a partir deste passo')

    total_acertos = 0
    for i in range(1, len(nomes)):
        #np.set_printoptions(threshold=np.inf)
        classified = nomes[np.logical_and(vacertos[i,:]==1, vacertos[i,:]!= vacertos[i-1,:])]
        total_acertos += len(classified)
        percent_n = (100*total_acertos) / len(nomes)
        print(f"{i}: {nacertos[i]:.0f} {classified}  Total = {total_acertos} ({percent_n:.0f}%)")
        if i > 15 and classified.size > 0   :
            ax.text(i,nacertos[i], str(classified))

########### main ##########

arquivos = sys.argv
narq = len(arquivos)

arq1 = arquivos[1]
arq2 = arquivos[2]

slopes1, slopes2, lincoeff1, lincoeff2,  nomes = carregacsvs(arq1, arq2)
nacertos, vacertos = classificaGeral(slopes1, slopes2, lincoeff1, lincoeff2)

fig = plt.figure()
ax = fig.add_subplot()

imprimeaceretoproblemas(vacertos, nomes, ax)
grafico(nacertos)

