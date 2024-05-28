import csv

def aux (row):
  print("aux")
  print(row)
  print(next(row))

with open("saida.csv", newline='') as csvfile:
  row = next(csvfile)
  while row:
     print(row)
     row = next(csvfile, False)
     
     
with open("saida.csv", newline='') as csvfile:
  reader = csv.reader(csvfile, delimiter=';')
  row = next(reader)
  while row:
    print(row)
    print(f"{row[0]} {row[1]}")
    row = next(reader, False)


