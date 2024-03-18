import random
import shutil
import sys
import os

n_training = 80
n_control = 20

control_dir = "control/"
training_dir = "training/"
rand_dir = "rand/"
cpp_file = ".cpp"

path = sys.argv[1]
if not path[len(path)-1] == "/":
  path = path + "/"

files = os.listdir(path + rand_dir)
random.shuffle(files)

i_training = 0
i_control = 0

for file in files:
  if not file[len(file) - 4:] == ".cpp":
    continue
  
  src = path + rand_dir + file
  dst_control = path + control_dir + file
  dst_training = path + training_dir + file
  
  x = random.randint(0, 1)
  if (x == 0 and i_control < n_control) or i_training == n_training:  #file goes to control dir
    print(f"Copying {src} to {dst_control}")
    shutil.copyfile(src, dst_control)
    i_control = i_control + 1  
  else: #file goes to training dir
    print(f"Copying {src} to {dst_training}")
    shutil.copyfile(src, dst_training)
    i_training = i_training + 1
    

