#after bash eServerRun.sh, read spikes.h5
#if there are no spikes besides in the cell you stimulated,
#then search in the upper half, if there are still spikes, then search in the lower half
#since this is essentially a binary search algorithm, do this for log_2(N) iterations, where N is the super high value chosen manually which gives spikes.
#now this is for AAC onto Pyr. to do this for the rest, you would need to do this one by one in a user-defined order of precedence.
#one could also maybe perhaps probably do this with the full parameter set all at once, where N is the euclidean distance of the parameters which give spikes
#and you need some function which translates half the euclidean distance into the amount of increase or decrease on each parameter.
#a generalist way to do this may be to use like a million or something ridiculous for all the weights, and then reduce this way, but
# i don't think this can be done with out specialized knowledge regarding what cells are the most important to optimize
import h5py
import numpy as np
import pandas as pd
import json

f = h5py.File(os.path.join("output",'spikes.h5'), 'r')
res = f['spikes/biophysical/node_ids'][()]
f.close()

pass_num = res.shape[0]

filename = os.path.join("biophys_components","synaptic_models","CHN2PN.json")
with open(filename) as file:
    myDict = json.load(file)
file.close()

weight = myDict['initW_lognormal_mean']
if pass_num > 1:
    weight -= weight/2
if pass_num ==1:
    weight+= weight/2

myDict['initW_lognormal_mean'] = weight
with open(filename,"w") as file:
    json.dump(myDict,file)
file.close()

#############################################################
filename = os.path.join("biophys_components","synaptic_models","CHN2PN.json")
with open(filename) as file:
    myDict = json.load(file)
file.close()

weight = myDict['initW_lognormal_mean']
if pass_num > 1:
    weight -= weight/2
if pass_num ==1:
    weight+= weight/2

myDict['initW_lognormal_mean'] = weight
with open(filename,"w") as file:
    json.dump(myDict,file)
file.close()