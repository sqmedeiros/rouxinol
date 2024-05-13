import os.path
import time
import sys
import csv
from datetime import datetime

NRUNS = 10
idx_pkg = 0
idx_core = 1
idx_ram = 2
idx_gpu = 3
perf_flag_prefix = "power/energy-"

# perf power options
# power/energy-cores/, power/energy-gpu/, power/energy-pkg/, power/energy-psys/, power/energy-ram/

#edit True/False according to the machine                    
perf_measurement = [ True,   # Pkg
                     False,  # Core
                     True,   # DRAM
                     False,  # GPU
]

perf_flags = [ "power/energy-pkg/",
               "power/energy-cores/",
               "power/energy-ram/",
               "power/energy-gpu/"
]
               

def set_perf_power ():
  perf_power = []
  for i, value in enumerate(perf_measurement):
    if value:
      perf_power.append(perf_flags[i])

  return ",".join(perf_power)


# A CSV entry should have 6 columns
# 1 Name ; 2 RAPL Pkg ; 3 RAPL Cores ; 4 RAPL RAM ; 5 RAPL GPU ; 6 CPU Time
def make_new_csv_entry (csv_file, entry_data):  
    
  print("Nova medição")
  print(', '.join(entry_data))
  
  with open(csv_file, "a+") as f:
     f.write(", ".join(entry_data))
     f.write("\n")


def is_perf_measurement (l):
  return len(l) == 7 and perf_flag_prefix in l[2]


def run_test (prog, output, csv_file, test_file, measurements):
  tmp_output = "saida.csv"
  if os.path.isfile(tmp_output):
    os.remove(tmp_output)

  power_flag = set_perf_power()
  cmd_test = f"perf stat -x ';' -e {power_flag} {prog} {test_file} {output} 2>>{tmp_output}"
  print(f"Executing {cmd_test}")
  os.system(cmd_test)

  with open(tmp_output, newline='') as csvfile: 
    print("Li csv")
    reader = csv.reader(csvfile, delimiter=';')
    i = 0
    for row in reader:
      if is_perf_measurement(row):
        measurements[i] += float(row[0].replace(",", "."))
        if i == 0:
          measurements[2] += int(row[3])
        i = i + 1
  
  print(f"End measurement {measurements}")
    

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

for i in range(NRUNS):
  measurements = [  0,    0,   0]
  for test in tests:
    print(f"Testing with {test}")
    run_test(exe_prog, output, csv_file, test, measurements)
  pkg_measure = measurements[0]
  ram_measure = measurements[1]
  time_measure = measurements[2]  # time in nanoseconds (10^9)

  time_measure = time_measure / pow(10, 6)  # Nanosecons -> Miliseconds
  pkg_measure = pkg_measure / (time_measure / pow(10, 3)) # From Joules to Watts
  ram_measure = ram_measure / (time_measure / pow(10, 3)) # From Joules to Watts

  #name   #pkg  #core #ram  #gpu #time
  entry_data = [ csv_entry, f"{pkg_measure:7.3f}", "", f"{ram_measure:6.3f}", "", f"{time_measure:5.0f}" ]
  make_new_csv_entry(csv_file, entry_data)   

