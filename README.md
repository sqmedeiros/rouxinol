# Dataset and Code Supporting the paper *A Source Code Independent Approach to Classify
Programs Based on Energy Consumption and Running Time*


## Running a experiment

To execute an experiment, it is necessary a native Linux environment with
the `perf` tool installed. The Linux user should also have the necessary
credentials/permissions to run some commands via `sudo`.

1. Clone the repository `rouxinol`.

2. In file `run-experiment-script/myscript`, change line `cd ~/rouxinol`
to point to your local copy of the repository `rouxinol`. 

3. Copy `run-experiment-script/myscript` to `/etc/init.d/`

4. Update init jobs: `sudo update-rc.d myscript defaults`

5. Create blank file `ToProcess.txt` in the root of your local `rouxinol`
repository.


6. Create `Experiments.txt` in the root of your local `rouxinol` repository
with experiments you want to run.
 
7. Examples of experiments:
control-01 mymachine -perf
training-01 mymachine -perf
control-01 mymachine -perf
training-01 mymachine -perf

8. Restart the computer.

9. The experiment will disable the network interface. The experiment emits
several beeps after processing a given problem (e.g., 1084-Apartments) and
then restarts the computer to process the next problem (e.g., 1091-Concert_Tickets).


## Processing the data

Marcelo, escreva aqui...
