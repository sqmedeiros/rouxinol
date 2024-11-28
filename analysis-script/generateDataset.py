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


        
def listaarquivos(arquivos):
    lista = glob.glob(arquivos)
    return lista


def criarelatorio(arquivoscurtos):
    try:
        os.mkdir('analysis_results')
        print('cirando diretorio de resultados')
    except OSError as error:
        print('diretorio de resultados ja existe') 
    file = open("analysis_results/relatorio" + ''.join(arquivoscurtos[0:]) + ".txt", "w")
    return file


def carregacsv(arquivo, flags, nexec):

    print('carregando ',arquivo)
    #carrega sem nomes de colunas pra descobrir quantas colunas tem
    dfsemnomes = pandas.read_csv(arquivo)
    ncolunas = len(dfsemnomes. columns)
    if ncolunas == 6:
        df = pandas.read_csv(arquivo,names=['codigo', 'pkg','cpu', 'n1','n2','tempo'])
    else:
        df = pandas.read_csv(arquivo,names=['codigo', 'pkg','cpu', 'n1','n2','tempo','tuser','tsys'])
        print('mais colunas de tempo detectadas')

    df, nexec = OrderbynameandComputenexec(df,flags['computenexec'],nexec)

    #calcular a média e variancia das nexec execucoes de cada codigo
    nlinhas = len(df)
    if flags['usensolutions']:
            checknumberofexecutionsandsolutions(nlinhas,nexec,flags['nsolutions'])

    return df, ncolunas, nlinhas, nexec

def salvaresumo(arquivo,vnome, vmconsumo, vdconsumo, vmtempo,vdtempo, vmtsoma, vdtsoma):

    print('salvando resumo de  ',arquivo)
    slopeindividual = vmconsumo/vmtempo
    
    d = {'nome': vnome, 'consumo_medio': vmconsumo, 'desvio_consumo':vdconsumo, 'tempo_medio':vmtempo, 'desvio_tempo':vdtempo, 'temposoma_medio':vmtsoma, 'desvio_temposoma':vdtsoma, 'slope_individual': slopeindividual}
    ds = pandas.DataFrame(data=d)
    ds = ds.sort_values('nome')
    ds.to_csv('analysis_results/resumo' + arquivo)

    return ds, d

def cabecalho(lista):
    texto = "@relation problema\n"
    #le a primeira linha do primeiro arquivo pra pegar o nome dos atributos

    #descobre quantos programas tem no diretorio
    listanumeroprogramas = ''
    for i in range(len(lista)):
        listanumeroprogramas += str(i) 
        if i<len(lista)-1:
            listanumeroprogramas += ','
    texto += "@attribute 'class' {" + listanumeroprogramas + "}\n"
    texto += "@data\n"
    return texto
#@attribute 'preg' real



def escrevearquivo(texto, arquivodataset):
    with open(arquivodataset,"w") as f:
        f.write(texto) # write the data back
        f.truncate() # set the file size to the current size
        f.close()
   

########   main   ##################
arquivodataset = "dataset.arff"
sistemaoperacional = platform.system()
print('Executing on ', sistemaoperacional)

arquivos = sys.argv

print(arquivos)

lista = listaarquivos(arquivos[1])

#texto do cabecalho do arquivo dataset.arff
texto = cabecalho(lista)

for i in lista:
     experimentNumber = i[0:4]
     #abre o arquivo
     #df = carregacsv(arquivos[i], flags, nexec)
    

escrevearquivo(texto, arquivodataset)