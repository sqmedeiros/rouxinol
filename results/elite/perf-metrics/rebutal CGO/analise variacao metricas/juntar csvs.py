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

def salvar(df,all_entries,i):
    nome = all_entries[2:6] + '-' + f'{i:02d}' + '.csv'
    df = df.sort_values('file')
    print('salvando ', nome)
    df.to_csv('./' + nome)



# Get all entries in the directory
#all_entries = sorted(os.listdir(directory_path))
all_entries = sorted(glob.glob(directory_path + '/*.csv'))

cont = 1

# Iterate and print only the files
print(f"Files in '{directory_path}':")
i=0
while i < len(all_entries):
    full_path = os.path.join(directory_path, all_entries[i]) # Construct full path
    if os.path.isfile(full_path):
        
        df = juntar(all_entries[i],all_entries[i+4]) 
        #df = seleciona_colunas(df,lista_colunas);
        salvar(df,all_entries[i],cont)
        
        if (i+1)%pula == 0:
            i +=pula
    i += 1 
    cont += 1 
        