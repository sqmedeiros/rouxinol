# -*- coding: utf-8 -*-
"""
Created on Sat May 13 09:26:47 2023

@author: Marcelo

Lists all files in a directory and creat a dataset for weka with all the dataset
The atributes of the dataset will be the given by the metrics in the first line of the csv of each file (they must be equal in every file)
cpu-cycles,instructions,cache-references,cache-misses,branch-instructions,branch-misses,page-faults,branch-loads,branch-load-misses,L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-icache-load-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses,dTLB-loads,dTLB-load-misses,dTLB-stores,dTLB-store-misses,iTLB-loads,iTLB-load-misses,user_time,system_time
The class will be the number of the problem
1071, 1082,...
"""

from signal import signal
import sys
import pandas
import matplotlib.pyplot as plt
import numpy as np
import os
from scipy import stats
import platform
import glob

nsigma=1
        
def listaarquivos(arquivos):
    lista = glob.glob(arquivos)
    return lista


def carregacsv(arquivo):

    print('carregando ',arquivo)
    #carrega sem nomes de colunas pra descobrir quantas colunas tem
    df = pandas.read_csv(arquivo)
    ncolunas = len(df.columns)  
    nlinhas = len(df)
    return df, ncolunas, nlinhas


########   main   ##################


sistemaoperacional = platform.system()
print('Executing on ', sistemaoperacional)

arquivos = sys.argv

if sistemaoperacional=='Linux':
     lista = arquivos[1:]
else:
	   lista = listaarquivos(arquivos[1])

cont = 0
vprob = np.zeros(len(lista))
vm = np.zeros(len(lista))
vd = np.zeros(len(lista))
vmax = np.zeros(len(lista))
vmin = np.zeros(len(lista))
for i in lista:
     vprob[cont]=cont
     df, ncolunas, nlinhas = carregacsv(i)
     tempo = df.loc[:,['duration_time']].values
     media = tempo.mean()
     vmax[cont] = tempo.max()
     vmin[cont] = tempo.min()
     vm[cont] = media
     desvio = tempo.std()
     vd[cont]=desvio
     cont += 1
     

plt.errorbar(vprob,vm, yerr=nsigma*vd,fmt ='.r')
plt.plot(vprob,vmax,'.b')
plt.plot(vprob,vmin,'.g')
plt.show()
     
