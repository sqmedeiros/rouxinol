import os.path
import time
import sys
import csv
from datetime import datetime

csv.field_size_limit(sys.maxsize)

NRUNS = 1
perf_flag_prefix = "power/energy-"


# power/energy-cores/, power/energy-gpu/, power/energy-pkg/, power/energy-psys/, power/energy-ram/

# perf power events
power_events = {}
list_events = ['pkg', 'cores', 'ram', 'gpu', 'psys']
list_times = ['duration_time', 'user_time', 'system_time']

def add_power_event (event, flag):
  power_events[event] = flag


def get_supported_flags ():
  cmd = "perf list | grep power"
  out_file = "tmpperflist.txt"
  os.system(f"{cmd} > {out_file}")

  with open(out_file, "r") as f:
     return f.read()


def get_perf_flag ():
  supported_flags = get_supported_flags()
  perf_flags = ""
  
  for e in list_events:
    flag = f"{perf_flag_prefix}{e}/"
    supported = flag in supported_flags
    add_power_event(e, supported)
    if supported:
      if not perf_flags:
        perf_flags = flag
      else:
        perf_flags += "," + flag
  
  assert perf_flags, "No perf power event suppored"

  for x in list_times:
    perf_flags += "," + x

  #using "all_cpus" otherwise perf does not return measurements related to the energy flags
  perf_flags = f"{perf_flags} --all-cpus"
 
  #adding flag_pkg again to indicate the beginning of the measurements
  assert 'pkg' in supported_flags, "PKG is not supported" 
  
  perf_flags = f"{perf_flag_prefix}pkg/,{perf_flags}"
  print(f"perf_flags = {perf_flags}")
  return perf_flags



def make_head_csv (csv_file, events):
  if os.path.isfile(csv_file):
    return
    
  fields = [ "file" ] + events
  entry_data = ','.join(fields)
  with open(csv_file, "a+") as f:
    f.write(entry_data)
    f.write("\n")


# A CSV entry should have 9 columns
# 1 Name ; 2 RAPL Pkg ; 3 RAPL Cores ; 4 RAPL RAM ; 5 RAPL GPU ; 6 RAPL PSYS ; 7 Total Time; 8 User Time; 9 Sys Time
def make_new_csv_entry (csv_file, entry_data):  

  #print(f"Nova medição {', '.join(entry_data)}\n")
  
  with open(csv_file, "a+") as f:
     f.write(", ".join(entry_data))
     f.write("\n")


def is_perf_measurement (l):
  for x in l:
    if perf_flag_prefix in x:
      return True
  return False


def add_measurement (measurements, k, v):
  if not k in measurements:
    measurements[k] = 0

  measurements[k] += v


def get_measurements (reader, measurements):

  # power-relared measurements 
  for e in list_events:
    if power_events[e]:
      row = next(reader)
      v = float(row[0].replace(",", ".")) 
    else:
      v = 0

    add_measurement(measurements, e, v)

  # time-related measurements 
  for x in list_times:
    # system time may not be measured, so "0" is provided as a default value
    # It must be the last event in the list of events
    if x == "system_time":
      row = next(reader, "0")
    else:
      row = next(reader)
       
    v = int(row[0])
    add_measurement(measurements, x, v)

  
def run_test (prog, output, csv_file, test_file, measurements):
  tmp_output = "saida.csv"
  if os.path.isfile(tmp_output):
    os.remove(tmp_output)

  power_flag = get_perf_flag()
  cmd_test = f"perf stat -x ';' -e {power_flag} {prog} {test_file} {output} 2>>{tmp_output}"
  print(f"Executing {cmd_test}")
  os.system(cmd_test)

  with open(tmp_output, newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=';')
    while True:
      row = next(reader)
      #print(f"Row {row} first = {is_perf_measurement(row)}")
      if is_perf_measurement(row):  # begin of perf measurement (extra pkg measurement)
        get_measurements(reader, measurements)
        break

  print(f"Finished test: {measurements}")


#print(sys.argv)
#for v in sys.argv:
#  print(f"v {v}")
#print(len(sys.argv))
#print(sys.argv[0])

exe_prog = sys.argv[1]
output = sys.argv[2]
csv_file = sys.argv[3] + ".csv"
csv_entry = sys.argv[4]

tests = sys.argv[5].strip().split(" ")

make_head_csv(csv_file, list_events + list_times)

for i in range(NRUNS):
  
  # executes only the first test
  tests = tests[:1]
  
  measurements = {}
  for test in tests:
    run_test(exe_prog, output, csv_file, test, measurements)

  entry_data = [ f"{csv_entry:12}" ]
  
  for e in list_events:
    entry_data.append(f"{measurements[e]:5.2f}")
    
  for x in list_times:
    entry_data.append(f"{measurements[x]:10.0f}")

  make_new_csv_entry(csv_file, entry_data)   

