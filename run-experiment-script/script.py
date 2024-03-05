import os.path
import time
from datetime import datetime

dirs = [
  "cses-1071_Number_Spiral",
  "cses-1082_Sum_of_Divisors",
  "cses-1084_Apartments",
 # "cses-1140_Projects",
 # "cses-1158_Bookshop",
 # "cses-1621_Distinct_Numbers",
 # "cses-1632_Movie_Festival_II",
 # "cses-1634_Minimizing_Coins",
 # "cses-1635_Coin_Combinations_I",
 # "cses-1636_Coin_Combinations_II",
 # "cses-1639_Edit_Distance",
 # "cses-1640_Sum_of_Two_Values",
 # "cses-1642_Sum_of_Four_Values",
 # "cses-1643_Maximum_Subarray_Sum",
 # "cses-2185_Prime_Multiples"
]


toProcess = "ToProcess.txt"
prevDir = "../"
sleepTime = 120 # seconds
beepInterval = 0.3 # seconds
rebootTime = 0 # minutes
cmdKillNet = "ifconfig eno1 down"
logDir = "log/"
logFile = "myLog.txt"


def write_log (msg):
  print(msg)
  with open(logDir + logFile, "a+") as f:
    f.write(f"{datetime.now()}: {msg}\n")


def kill_and_sleep (sleepTime):
  os.system(cmdKillNet) 
  time.sleep(sleepTime)
  

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
  with open(file, 'r+') as f:
    firstLine = f.readline() # read the first line and throw it out
    data = f.read() # read the rest
    f.seek(0) # set the cursor to the top of the file
    f.write(data) # write the data back
    f.truncate() # set the file size to the current size
    return firstLine.rstrip()

#checa se o arquivo ja existe
check_file = os.path.isfile(toProcess)

if check_file == False:
   write_log("Creating file with directories to process...")
   with open(toProcess,"a+") as fapp:
     for mydir in dirs:
       fapp.write(f"{mydir}\n")
   make_beep(1)
   os.system('shutdown -r now')
elif os.stat(toProcess).st_size == 0:
  msg = "Job done."
  write_log(msg)
else:
  write_log("Processing files")
  kill_and_sleep(sleepTime)
  mydir = get_next_dir(toProcess)
  indexDir = get_index(mydir) + 1
  msg = f"I'm going to process directory {mydir} {indexDir}"
  write_log(msg)
  os.chdir(mydir)
  os.system("./faztudo.sh")
  os.chdir(prevDir)
  write_log(f"Finished {mydir}")
  make_beep(get_index(mydir))
  os.system(f"shutdown -r +{rebootTime}")

