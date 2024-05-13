import os.path
import time
from datetime import datetime
import sys
from os import listdir
from os.path import isfile, join

dirs = [
  "1071-Number_Spiral",
  "1082-Sum_of_Divisors",
  "1084-Apartments",
  "1091-Concert_Tickets",
  "1131-Tree_Diameter",
  "1132-Tree_Distances_I",
  "1140-Projects",
  "1158-Bookshop",
  "1190-Subarray_Sum_Queries",
  "1192-Counting_Rooms",
  "1195-Flight_Discount",
  "1197-Cycle_Finding",
  "1619-Restaurant_Customers",
  "1621-Distinct_Numbers",
  "1628-Meet_in_the_Middle",
  "1632-Movie_Festival_II",
  "1634-Minimizing_Coins",
  "1635-Coin_Combinations_I",
  "1636-Coin_Combinations_II",
  "1639-Edit_Distance",
  "1640-Sum_of_Two_Values",
  "1642-Sum_of_Four_Values",
  "1643-Maximum_Subarray_Sum",
  "1666-Building_Roads",
  "1667-Message_Route",
  "1668-Building_Teams",
  "1669-Round_Trip",
  "1671-Shortest_Routes_I",
  "1672-Shortest_Routes_II",
  "1674-Subordinates",
  "2166-Prefix_Sum_Queries",
  "2185-Prime_Multiples"
] 

logDir = "log/"
logFile = "myLog.txt"
prevDir = "../"
makefileDir = 'scripts/'

def write_log (msg):
  print(msg)
  with open(logDir + logFile, "a+") as f:
    f.write(f"{datetime.now()}: {msg}\n")

def getEntries():
  entries = [f for f in listdir("./test") if isfile(join("./test", f))]
  return entries

def generateEntryline(entries):
  line = "export TEST = "
  for ent in entries:
    line = line + "../test/" + ent + " "
  line = line + "\n"
  return line

def generateMakefileText(mydir,experiment,dataFormatada,machine):
  texto = "export PROBLEM = " + mydir + "-" + experiment + "-" + dataFormatada + machine +  "\n"
  texto  = texto + "export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2\n"
  texto = texto + "export OUTPUT = 2>&1 > /dev/null\n"
  entries = getEntries()
  entryline  = generateEntryline(entries)
  texto = texto + entryline
  texto = texto + "all:\n\t+$(MAKE) -C " + experiment + "\n"
  texto = texto + "clean:\n\trm rand/*.exe training/*.exe control/*.exe\n"
  return texto

def createMakefile(mydir,experiment,dataFormatada, machine):
  texto = generateMakefileText(mydir,experiment,dataFormatada,machine)
  with open("Makefile","w") as f:
    f.write(texto) # write the data back
    f.truncate() # set the file size to the current size

def checkArguments(arquivos):
  narq = len(arquivos)
  if  narq < 2: #o primeiro argumento é o nome do proprio script
    print('usage: generate_makefile experiment <machine>')
    exit()  

def  getnames(arquivos):
  narq = len(arquivos)
  experiment = arquivos[1]
  machine = ''
  if narq == 3:
    machine = "-" + arquivos[2]
  return experiment, machine

def copyMakefilesubdir(experiment, mydir):
  os.system('cp ' + makefileDir + 'Makefile-perf ' + mydir + '/' + experiment + '/Makefile')

arquivos = sys.argv

checkArguments(arquivos)

experiment, machine = getnames(arquivos)

dataAtual = datetime.now()
dataFormatada = dataAtual.strftime("%d-%m-%Y-%H-%M")

write_log("Generating Makefiles")
for mydir in dirs:
  write_log("Working on " + mydir)
  os.chdir(mydir)
  createMakefile(mydir,experiment,dataFormatada,machine)
  os.chdir(prevDir)
  copyMakefilesubdir(experiment, mydir)
write_log("Makefiles Complete")
