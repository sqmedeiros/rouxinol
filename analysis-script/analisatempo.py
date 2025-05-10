# -*- coding: utf-8 -*-
"""
Created on Sat May 13 09:26:47 2023

@author: Marcelo

cira boxplot com tempo de execucao de varias solucoes
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
dataset = []
dataset2 = []
labels = []
for i in lista:
     vprob[cont]=cont
     df, ncolunas, nlinhas = carregacsv(i)
     tempo = df.loc[:,['duration_time']].values
     tempo = tempo/(10**6)
     dataset.append(tempo[:,0] )
     consumo = df.loc[:,['pkg']].values
     dataset2.append(consumo[:,0] )
     media = tempo.mean()
     vmax[cont] = tempo.max()
     vmin[cont] = tempo.min()
     vm[cont] = media
     desvio = tempo.std()
     vd[cont]=desvio
     cont += 1
     labels.append(i[0:4])
     


#plt.errorbar(vprob,vm, yerr=nsigma*vd,fmt ='.r')
#plt.plot(vprob,vmax,'.b')
#plt.plot(vprob,vmin,'.g')
fig, ax = plt.subplots()
ax.boxplot(dataset, patch_artist=True, positions=vprob,showfliers=False)
plt.xlabel('Problem')
ax.set_xticks(vprob, labels, rotation='vertical') 
plt.title('Wall-Clock Boxplot (-O2 flag)')
plt.ylabel('Wall-Clock Time (ms)')

fig, ax = plt.subplots()
ax.boxplot(dataset2, patch_artist=True, positions=vprob,showfliers=False)
plt.xlabel('Problem')
ax.set_xticks(vprob, labels, rotation='vertical') 
plt.title('pkg Consumption Boxplot (-O2 flag)')

plt.ylabel('Energy Comsumption (J)')

plt.show()
     
