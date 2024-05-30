import os.path
import time
from datetime import datetime

dirs = [
  "1071-Number_Spiral",
  "1082-Sum_of_Divisors",
  "1084-Apartments",
  "1140-Projects",
  "1158-Bookshop",
  "1621-Distinct_Numbers",
  "1632-Movie_Festival_II",
  "1634-Minimizing_Coins",
  "1635-Coin_Combinations_I",
  "1636-Coin_Combinations_II",
  "1639-Edit_Distance",
  "1640-Sum_of_Two_Values",
  "1642-Sum_of_Four_Values",
  "1643-Maximum_Subarray_Sum",
  "2185-Prime_Multiples",
  "1091-Concert_Tickets",
  "1131-Tree_Diameter",
  "1132-Tree_Distances_I",
  "1190-Subarray_Sum_Queries",
  "1192-Counting_Rooms",
  "1195-Flight_Discount",
  "1197-Cycle_Finding",
  "1619-Restaurant_Customers",
  "1628-Meet_in_the_Middle",
  "1666-Building_Roads",
  "1667-Message_Route",
  "1668-Building_Teams",
  "1669-Round_Trip",
  "1671-Shortest_Routes_I",
  "1672-Shortest_Routes_II",
  "1674-Subordinates",
  "2166-Prefix_Sum_Queries"
]

experiments = "Experiments.txt"
toProcess = "ToProcess.txt"
prevDir = "../"
sleepTime = 120 # seconds
beepInterval = 0.3 # seconds
rebootTime = 0 # minutes
cmdKillNet = "ifconfig eno1 down"
cmdKillAnydesk = "service anydesk stop"
logDir = "log/"
logFile = "myLog.txt"


def write_log (msg):
  print(msg)
  with open(logDir + logFile, "a+") as f:
    f.write(f"{datetime.now()}: {msg}\n")


def kill_and_sleep (sleepTime):
  os.system(cmdKillAnydesk)
  time.sleep(sleepTime)
  os.system(cmdKillNet) #antes do sleep nao estava fazendo efeito
  

def make_beep (n):
  time.sleep(beepInterval)
  for i in range(n):
     time.sleep(beepInterval)
     cmd1 = "speaker-test -t sine -f 1000 -l 1"
     cmd2 = " & sleep .5 && kill -9 $!"
     os.system(cmd1 + cmd2)
     
	
def get_index (mydir):
  for i, v in enumerate(dirs):
    if mydir == v:
      return i
  assert(False)
  return 0


def get_next_dir (file):
    return recortaprimeiralinha(file)
  
def turnXon():
  cmd1 = 'systemctl enable graphical.target --force'
  cmd2 = 'systemctl set-default graphical.target'
  os.system(cmd1)
  os.system(cmd2)


def turnXoff():
  cmd1 = 'systemctl enable multi-user.target --force'
  cmd2 = 'systemctl set-default multi-user.target'
  os.system(cmd1)
  os.system(cmd2)

def arquivos_existem():
    check_exp = os.path.isfile(experiments)
    check_tp = os.path.isfile(toProcess)
    if not(check_exp and check_tp):
        return False
    return True

def reinicia():
    print('reboot')
    #os.system(f"shutdown -r +{rebootTime}")

def criaToProcess():
   write_log("Creating file with directories to process...")
   with open(toProcess,"a+") as fapp:
     for mydir in dirs:
       fapp.write(f"{mydir}\n") 

def recorta_primeira_linha(file):
    with open(file, 'r+') as f:
        firstLine = f.readline() # read the first line and throw it out
        data = f.read() # read the rest
        f.seek(0) # set the cursor to the top of the file
        f.write(data) # write the data back
        f.truncate() # set the file size to the current size

        return firstLine.rstrip()

def extrai_params_linha(linha):
    params = linha.split()
    exp = params[0]
    maq = params[1]
    if len(params) == 3:
        perf = params[2]
    else:
        perf = ''
    return exp, maq, perf

def pega_prox_experimento(file):
    linha = recorta_primeira_linha(file)
    exp, maq, perf = extrai_params_linha(linha)
    return exp, maq, perf
    

def gera_makefiles():
  nomeexp, maquina,perf = pega_prox_experimento(experiments)
  print(nomeexp, maquina,perf)
  cmd = 'python3 .\scripts\generate_makefiles.py ' + nomeexp + ' ' + maquina + ' ' + perf
  os.system(cmd)


def prepara_novo_experimento():
    gera_makefiles()
    criaToProcess()
    turnXoff()
    make_beep(1)
    reinicia()

def continua_experimento_atual():
    mydir = get_next_dir(toProcess)
    write_log("Processing files")
    kill_and_sleep(sleepTime)
    indexDir = get_index(mydir) + 1
    msg = f"I'm going to process directory {mydir} {indexDir}"
    write_log(msg)
    os.chdir(mydir)
    os.system("./faztudo.sh")
    os.chdir(prevDir)
    write_log(f"Finished {mydir}")
    make_beep(get_index(mydir))
    reinicia()

def encerra_experimentos():
    write_log('Job done')
    turnXon()
    reinicia()

def pegatamanhoarquivos(experiments,toProcess):
    size_exp = os.stat(experiments).st_size
    size_tp = os.stat(toProcess).st_size
    return size_exp, size_tp

def no_meio_de_experimento(size_tp):
   return size_tp!=0

def tem_experimento_pra_fazer(size_exp):
   return size_exp!=0


#checa se os arquivos experiments e toProcesso existem
if not(arquivos_existem()):
  write_log('Missing experiment files. Aborting.')
  exit()

size_exp, size_tp = pegatamanhoarquivos(experiments,toProcess)

if no_meio_de_experimento(size_tp):
  continua_experimento_atual()
elif tem_experimento_pra_fazer(size_exp):
  prepara_novo_experimento()
else:
  encerra_experimentos()
  