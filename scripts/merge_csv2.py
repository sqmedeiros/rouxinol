import sys
import glob
import os

def check_arguments (args):
  narq = len(args)
  if  narq <= 4: #o primeiro argumento é o nome do proprio script
    print('usage: merge_csv output_dir suffix experiment_1 ... experiment_N')
    exit()  


def get_files (args):
  return args[1], args[2:]


def get_experiment_files (exps):
  files = []
  for exp in exps:
    pattern = f"*{exp}*.csv"
    print(f"Pattern = {pattern}")
    files.extend(glob.glob(pattern))
    
  return files

def get_merge_suffix (exps):
  return "+".join(exps)


def get_prefix (name):
  parts = name.split("-")
  return f"{parts[0]}-{parts[1]}-{parts[2]}-{parts[3]}-"


def merge_file (f, merge_suffix, output_dir, file_suffix):
  prefix = get_prefix(f)
  output_file = prefix + merge_suffix + file_suffix
  print(f"Merging {f} to {output_file}")
  output_file = os.path.join(output_dir, output_file)
  with open(output_file, "ab") as outfile, open(f, "rb") as infile:
    outfile.write(infile.read())
  

def merge_files (files, merge_suffix, output_dir, file_suffix):
   for f in files:
     merge_file(f, merge_suffix, output_dir, file_suffix)
     

args = sys.argv

check_arguments(args)
output_dir = args[1]
file_suffix = args[2]
experiments = args[3:]
print(f"Experiments {experiments}")

merge_suffix = get_merge_suffix(experiments)

files = get_experiment_files(experiments)

merge_files(files, merge_suffix, output_dir, file_suffix)

