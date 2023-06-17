# Model of CA1 section of Hippocampus
### Goal is to show SPWR in CA1
```
to make an environment where everything will run:
python3 -m venv CA1_model_env
source CA1_model_env/bin/activate
pip install -r requirements.txt
```

### Building network
```
python3 build_network_V2.py

```

### Running network
```
mpiexec -np 50 nrniv -mpi -python run_network.py
if there is an issue with output folder then do:

rm -rf output
mkdir output


alternatively can do all this with:
bash eServerRun.sh
```
### Changing parameters
```
biophys_components/synaptic_models
has json files that are used to select the parameters for each synapse in the model
initW_lognormal_mean and std are the parameters to change to remove connections.
use a small nonzero number like 0.00001 to effectively remove the synapse

simulation_configLFP.json is the simulation config that the run script uses.

```

currently three AACs are stimulated
background noise is currently not used.

