import sys

def check_arguments (args):
  narq = len(args)
  if  narq < 3: #o primeiro argumento é o nome do proprio script
    print('usage: merge_csv output_file file_1 ... file_N')
    exit()  


def get_files (args):
  return args[1], args[2:]


args = sys.argv

check_arguments(args)

output_file, files_to_merge = get_files(args)

with open(output_file, "wb") as outfile:
  for f in files_to_merge:
    with open(f, "rb") as infile:
      outfile.write(infile.read())
  

