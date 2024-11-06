import os.path
import time
import sys
import csv
from datetime import datetime

# time sudo perf stat -a -o temp.txt -x ';' -e power/energy-pkg/,cpu-cycles,user_time,system_time ./a.out < ../test/entry01.txt > /dev/null 

csv.field_size_limit(sys.maxsize)

NRUNS = 1
perf_flag_prefix = "power/energy-"


def make_head_csv (csv_file, events):
  if os.path.isfile(csv_file):
    return
    
  fields = [ "file" ] + events
  entry_data = ','.join(fields)
  with open(csv_file, "a+") as f:
    f.write(entry_data)
    f.write("\n")
      

def make_new_csv_entry (csv_file, values):   
  entry_data = ','.join(map(str, values))
  print(f"Nova medição {entry_data}\n")
  
  with open(csv_file, "a+") as f:
     f.write(entry_data)
     f.write("\n")


def is_perf_measurement (l):
  for x in l:
    if perf_flag_prefix in x:
      return True
  return False


def is_valid_value (x):
  return x != "<not supported>"


def get_measurement (row):
  value = row[0]
  
  value = value.replace(",", ".")
  
  if is_valid_value(value):
    if '.' in value:
      value = float(value)
    else:
      value = int(value)
    
  return value


def get_measurements (reader, measurements):
  for x in measurements.keys():
    value = get_measurement(next(reader))
    if is_valid_value(value):
       measurements[x] += value
    else:
       measurements[x] = value


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
    # Information about date/time
    row = next(reader)
    # Empty row
    row = next(reader)
    get_measurements(reader, measurements)
 

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


make_head_csv(csv_file, events_list)
	
for i in range(NRUNS):
  measurements = {}
  for x in events_list:
    measurements[x] = 0

  for test in tests:
    run_test(exe_prog, output, csv_file, test, measurements)

  make_new_csv_entry(csv_file, [csv_entry] + list(measurements.values()))   

