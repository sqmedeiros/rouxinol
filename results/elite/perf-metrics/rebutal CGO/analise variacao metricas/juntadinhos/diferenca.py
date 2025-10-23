import pandas as pd
import os
import glob
import sys
import statistics
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

pula = 4

directory_path = '.' # Current directory, or specify your path like '/path/to/your/directory'

colunas = ['file','L1-dcache-load-misses', 'L1-dcache-loads', 'branch-instructions',
                 'branch-load-misses', 'branch-loads', 'branch-misses', 'cache-misses', 
                 'cache-references', 'cpu-cycles', 'dTLB-load-misses', 'dTLB-loads', 
                 'page-faults', 'iTLB-load-misses', 'iTLB-loads', 'instructions']

def carregacsv(arquivo,colunas):

    print('carregando ',arquivo)
    #carrega sem nomes de colunas pra descobrir quantas colunas tem
    df = pd.read_csv(arquivo)
    df = df[colunas]
    ncolunas = len(df.columns)
    print(ncolunas)
    
    return df

def salvar(df,nome):
    print('salvando ', nome)
    df.to_csv('./' + nome,  index = False)

def comparar2arevanche(lista, nome):
    lista_df_diff = []
    prefixo = nome[2:6]
    for i in range(len(lista)):
        for j in range(i+1,len(lista)):
            nome = prefixo + '_' + str(i) + 'x'+ str(j) + '_'
            print('comparando ', nome)
            df_diff = comparaexecucoes(lista[i],lista[j],nome)
            lista_df_diff.append(df_diff)

    return pd.concat(lista_df_diff)
            
            
def comparaexecucoes(df1,df2,nome):
    nlinhas = 100
    ncols = 16
    df_diff = pd.DataFrame(columns=colunas)
    for i in range(1,nlinhas):
        entry = [nome + df1.iloc[i,0]]
        for j in range(1,ncols):
            if df1.iloc[i,j] != '<not counted>' and df2.iloc[i,j] != '<not counted>':
                x1 = int(df1.iloc[i,j])
                x2 = int(df2.iloc[i,j])
                val = np.abs(x1 - x2)/max(x1,x2)
            else:
                val = 0
            entry.append(val)

    
        df_diff.loc[len(df_diff)] = entry
    return df_diff
    

def comparar(listadf, all_entries):
    i = 0
    lista_df_diff = []
    while i < len(listadf):
        lista_df_diff.append(comparar2arevanche(listadf[i:i+pula], all_entries[i]))
        i += pula                 
        

    return pd.concat(lista_df_diff)

# Get all entries in the directory
#all_entries = sorted(os.listdir(directory_path))
all_entries = sorted(glob.glob(directory_path + '/*.csv'))


# Iterate and print only the files

listadf = []
i=0
while i < len(all_entries):
    full_path = os.path.join(directory_path, all_entries[i]) # Construct full path
    if os.path.isfile(full_path):
        
        df = carregacsv(all_entries[i], colunas) 
        #salvar(df,all_entries[i] + '_novo_.csv',i)
        listadf.append(df)
    i += 1 
df_final = comparar(listadf, all_entries)
salvar(df_final,'diferencas.txt')
    
