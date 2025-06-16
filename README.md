# Dataset and Code Supporting the paper *A Source Code Independent Approach to Classify Programs Based on Energy Consumption and Running Time*

## Directory Structure

- 32 subfolders, one for each CSES problem, with 100 C++ solutions each.
- `results`: has the .csv files with the results for machines `elite` and `think`
- `scripts`: auxiliary Pytyhon scripts to generate makefiles and to pick problems for the dataset.
- `run-experiment-script`: Python scripts used to run an experiment.
- `analysis-script`: Python scripts used when processing the result of an experiment.
- 


## Running a experiment

To execute an experiment, it is necessary a native Linux environment with
the `perf` tool installed. The Linux user should also have the necessary
credentials/permissions to run some commands via `sudo`.

1. Clone the repository `rouxinol`.

2. In file `run-experiment-script/myscript`, change line `cd ~/rouxinol`
to point to your local copy of the repository `rouxinol`. 

3. Copy `run-experiment-script/myscript` to `/etc/init.d/`

4. Update init jobs: `sudo update-rc.d myscript defaults`

5. Optinal: edit `Experiments.txt` in the root of your local `rouxinol` repository
and replace 'mymachine' with the name of your machine. You can also use the optimization
flag -O0 instead of -O2. Below find the default configuration of `Experiments.txt` when
cloning the repository:

```
control-01 mymachine -O2 -perf
training-01 mymachine -O2 -perf
control-02 mymachine -O2 -perf
training-02 mymachine -O2 -perf
```
 
6. Restart the computer. Do not interect with the computer to avoid interfering with
the energy measurements. 

7. The experiment will disable the network and graphical interfaces. The experiment emits
several beeps after processing a given problem (e.g., 1084-Apartments) and
then restarts the computer to process the next problem (e.g., 1091-Concert_Tickets). 

8. The experiment will take aproximatelly 9 hours. When the experiment is over, the computer
will restart one last time and you will see the graphical login screen.

## Processing the data

1. Once all the experiments are complete, the files `Experiments.txt` and `ToProcess.txt`
(in the root of your local `rouxinol` repository) will be empty, and a folder
named `results\<mymachine>` will be created. Inside this folder there will be four
subfolders (named `control-01`, `control-02`, `training-01` and `training-02`) each representing an 
experiment with the corresponding measurement results, for each problem, in separated .csv files.

2. To generate the dataset files needed for classification for each experiment you need to execute
the python script located at rouxinol\analysis-script\generateDataset.py and pass as 
argument the name of the .csv files for a given experiment. For example, after entering the 
`training-01` folder you can execute: 

`python ..\..\..\analysis-script\generateDataset.py *.csv`

This will generate, in the local folder, a file named `dataset.arff`  (an Attribute-Relation
 File Format used by Weka).  

3. After generating the dataset files for a given training and respective control experiments, 
you can use Weka Explorer to open the training file. Select `RandomForest` as the classifier 
(with default values), select the control file as a test set, train and analyse 
classification results.


