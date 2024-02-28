import os
import sys

path = sys.argv[1]
text = "entry_"

files = os.listdir(path)

for file in files:
  s = path + "/" + file
  entry_pos = s.find(text)
  print(f"file = {s}")
  
  os.rename(s, s[:entry_pos] + s[entry_pos + len(text):])

