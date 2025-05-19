import pandas as pd
import os
import sys
import statistics
import matplotlib.pyplot as plt


def show_diffs (xs):
    for x in xs:
        y = (1 - x) * 100
        print(f"{x:.2f}", end=", ")

def calc_time_diff (df1, df2):
    diffs = []
    for index, row in df1.iterrows():
      x = row['perf_time'] / row['duration_time']
      diffs.append(x)
    for index, row in df2.iterrows():
      x = row['perf_time'] / row['duration_time']
      diffs.append(x)

    return diffs

arquivos = sys.argv

directory = os.path.join(".",arquivos[1])
diffstudo = []
medianaProblema = []
labels = []
vprob =[]
for root,dirs,files in os.walk(directory):
    #for file in sorted(files):
    for i in range(0, len(files),2):
       file = files[i]
       print(file)
       path = os.path.join(directory, file)
       df1 = pd.read_csv(path)
       file = files[i+1]
       print(file)
       path = os.path.join(directory, file)
       df2 = pd.read_csv(path)
       diffs = calc_time_diff(df1, df2)
       diffstudo = diffstudo + diffs
       show_diffs(diffs)
       print()
       print(f"Mediana = {statistics.median(diffs)}")
       medianaProblema.append(statistics.median(diffs))
       labels.append(file[0:4])
       vprob.append(i/2)


print(f"Mediana Total = {statistics.median(diffstudo)}")
print(f"Maximo Total = {max(diffstudo)}")
print(f"Minimo Total = {min(diffstudo)}")
print(f"Media Total = {statistics.mean(diffstudo)}")


fig, ax = plt.subplots()
plt.bar(vprob,medianaProblema)
plt.xlabel('Problem')
ax.set_xticks(vprob, labels, rotation='vertical') 
plt.title('Median Overhead by problem (-'+ arquivos[1][-3:-1] + ' flag)')
plt.ylabel('Median Overhead (percentage)')
plt.show()
