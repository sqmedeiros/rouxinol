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



def juntar(file1,file2):
    print('juntando ', file1, ' e ', file2)
    path1 = os.path.join(directory_path, file1)
    path2 = os.path.join(directory_path, file2)
    df1 = pd.read_csv(path1)
    df2 = pd.read_csv(path2)
    df = pd.concat([df1,df2])
    
    #    path = os.path.join(directory_path, f)
    
    return df

def salvar(df,nome,dataset, i):
    nome = nome + '_' + dataset + 'experimento_' + str(i%4) + '.csv'
    print('salvando ', nome)
    df.to_csv('./' + dataset +'/' + nome, index = False)



# Get all entries in the directory
#all_entries = sorted(os.listdir(directory_path))
all_entries = sorted(glob.glob(directory_path + '/*.csv'))



# Iterate and print only the files

i=0
while i < len(all_entries):
    full_path = os.path.join(directory_path, all_entries[i]) # Construct full path
    if os.path.isfile(full_path):
        
        df =  pd.read_csv(full_path) 

        
        salvar(df.head(80),all_entries[i],'training', i)
        salvar(df.tail(20),all_entries[i],'control', i)
        
    i += 1 

        