import os.path
import time
import sys
import csv
from datetime import datetime

# time sudo perf stat -a -o temp.txt -x ';' -e power/energy-pkg/,cpu-cycles,user_time,system_time ./a.out < ../test/entry01.txt > /dev/null 

csv.field_size_limit(sys.maxsize)

NRUNS = 1
perf_flag_prefix = "power/energy-"


def make_new_csv_entry (csv_file, entry_data):  

  print(f"Nova medição {', '.join(entry_data)}\n")
  
  with open(csv_file, "a+") as f:
     f.write(", ".join(entry_data))
     f.write("\n")


def is_perf_measurement (l):
  for x in l:
    if perf_flag_prefix in x:
      return True
  return False


def get_measurements (reader, measurements):
  row = next(reader)
  pkg = float(row[0].replace(",", "."))
  measurements["pkg"] += pkg

  # uses the time associated with the first measure as the clock time
  clock_time = int(row[3])
  measurements["clock_time"] += clock_time

  row = next(reader)
  ram = float(row[0].replace(",", "."))
  measurements["ram"] += ram

  row = next(reader)
  user_time = int(row[0])
  measurements["user_time"] += user_time

  row = next(reader, "0")
  sys_time = int(row[0])
  measurements["sys_time"] += sys_time


def run_test (prog, output, csv_file, test_file, measurements):
  tmp_output = "saida.csv"
  dev_null = "/dev/null"
  if os.path.isfile(tmp_output):
    os.remove(tmp_output)

  str_events = ','.join(events_list)
  cmd_test = f"perf stat -a -o {tmp_output} -x ';' -e {str_events} {prog} {test_file} {output} 2>>{dev_null}"
  print(f"Executing {cmd_test}")
  os.system(cmd_test)

  with open(tmp_output, newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=';')
    while True:
      row = next(reader)
      print(f"Row {row} first = {is_perf_measurement(row)}")
      if is_perf_measurement(row):  # begin of perf measurement (extra pkg measurement)
        get_measurements(reader, measurements)
        break

  print(f"Finished test: {measurements}")


print(sys.argv)
for v in sys.argv:
  print(f"v {v}")
print(len(sys.argv))
print(sys.argv[0])

exe_prog = sys.argv[1]
output = sys.argv[2]
csv_file = sys.argv[3] + ".csv"
csv_entry = sys.argv[4]

tests = sys.argv[5].strip().split(" ")
               #pkg, ram, cpu_time  


with open("events.txt", 'r') as event_file:
  events_list = event_file.read().strip().split('\n')

	
for i in range(NRUNS):
  measurements = {"pkg": 0, "ram": 0, "clock_time" : 0, "user_time" : 0, "sys_time" : 0 }
  for test in tests:
    run_test(exe_prog, output, csv_file, test, measurements)

  pkg = measurements["pkg"]
  ram = measurements["ram"]
  clock_time = measurements["clock_time"]  # time in nanoseconds (10^9)
  user_time = measurements["user_time"]  # time in nanoseconds (10^9)
  sys_time = measurements["sys_time"]  # time in nanoseconds (10^9)

  clock_time = clock_time / pow(10, 6)  # Nanosecons -> Miliseconds
  user_time = user_time / pow(10, 6)  # Nanosecons -> Miliseconds
  sys_time = sys_time / pow(10, 6)  # Nanosecons -> Miliseconds

  #name   #pkg  #core #ram  #gpu #time
  entry_data = [ csv_entry, f"{pkg:7.2f}", "", f"{ram:6.2f}", "", f"{clock_time:5.0f}", f"{user_time:5.0f}", f"{sys_time:5.0f}" ]
  make_new_csv_entry(csv_file, entry_data)   

