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



def salvar(df,nome):
    print('salvando ', nome)
    df.to_csv('./' + nome,  index = False)


arquivo = '.\diferencas.txt'
df = pd.read_csv(arquivo)
cols = df.columns
lista = []
for c in colunas[1:]:
    mediana = df[c].median()
    print('mediana da coluna ', c, ' ', mediana)
    lista.append(mediana)
    print('maximo da coluna ', c, ' ', df[c].max())
    print('minimo da coluna ', c, ' ', df[c].min())
    
print('maximo e minimo das medianas: ', max(lista), '  ', min(lista), '  ', np.median(lista))