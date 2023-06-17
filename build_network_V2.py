from bmtk.builder import NetworkBuilder
from bmtk.builder.auxi.node_params import positions_list, xiter_random
from bmtk.utils.sim_setup import build_env_bionet
from bmtk.utils.reports.spike_trains import PoissonSpikeGenerator
from math import exp
import numpy as np
import pandas as pd
import random
import h5py
import synapses
from math import ceil
synapses.load()
syn = synapses.syn_params_dicts()

seed = 999

rng = np.random.default_rng(seed)

net = NetworkBuilder("biophysical")

# amount of cells
NetNo = 20000
#NetNo = 300
IN_num = NetNo*.11#about 11% of all neurons are interneurons in this network (Bezaire 2013). We are only modeling 2, so omit the others, or substitute PV and OLM for all
PN_num = NetNo -  IN_num


numOLM = .043*IN_num # 4% of all INs are OLMs
numPV = .144*IN_num
numPyr = PN_num
numAAC = 0.038*IN_num
totalScale = (1 - (.043 + .144 + 0.038))/3

#scale up so that 11% of cells in the model are INs
numOLM = numOLM + IN_num*totalScale
numPV = numPV + IN_num*totalScale
numAAC = numAAC + IN_num*totalScale
print(numOLM + numAAC + numPV)
# amount of cells per layer
numAAC_inSO = int(ceil(numAAC*0.238))  # sometimes the num will be <1 so always round up so there is at least one.
numPV_inSO = int(ceil(numPV*0.238))
numOLM_inSO = int(ceil(numOLM))

numAAC_inSP = int(ceil(numAAC*0.7))
numPV_inSP = int(ceil(numPV*0.702))
numPyr_inSP = int(ceil(numPyr))

numAAC_inSR = int(ceil(numAAC*0.061))
numPV_inSR = int(ceil(numPV*0.0597))
# arrays for cell location csv
cell_name = []
cell_x = []
cell_y = []
cell_z = []




#not commented out previously
#totalCellNum = numAAC_inSO + numAAC_inSP + numAAC_inSR + numCCK_inSO + numCCK_inSP + numCCK_inSR + numCCK_inSLM + numNGF_inSR + numNGF_inSLM + numPV_inSO + numPV_inSP + numPV_inSR
totalCellNum = numAAC_inSO + numPV_inSO + numOLM_inSO + numAAC_inSP + numPV_inSP+  numPyr_inSP+ numAAC_inSR  + numPV_inSR


def AAC_to_PYR(src, trg, a, x0, sigma, max_dist):
    if src.node_id == trg.node_id:
        return 0

    sid = src.node_id
    tid = trg.node_id

    src_pos = src['positions']
    trg_pos = trg['positions']

    dist = np.sqrt((src_pos[0] - trg_pos[0]) ** 2 + (src_pos[1] - trg_pos[1]) ** 2 + (src_pos[2] - trg_pos[2]) ** 2)
    prob = a * exp(-((dist - x0) ** 2) / (2 * sigma ** 2))
    #print(dist)
    #prob = (prob/100)
    #print(prob)

    if dist <= max_dist:
        global count
        count = count + 1
    if dist <= max_dist and np.random.uniform() < prob:
        connection = 1
        #print("creating {} synapse(s) between cell {} and {}".format(1,sid,tid))
    else:
        connection = 0
    return connection

def n_connections(src, trg, max_dist, prob=0.1):
    """Referenced by add_edges() and called by build() for every source/target pair. For every given target/source
    pair will connect the two with a probability prob (excludes self-connections)"""
    if src.node_id == trg.node_id:
        return 0

    src_pos = src['positions']
    trg_pos = trg['positions']
    dist = np.sqrt((src_pos[0] - trg_pos[0]) ** 2 + (src_pos[1] - trg_pos[1]) ** 2 + (src_pos[2] - trg_pos[2]) ** 2)
    if dist <= max_dist:
        if np.random.uniform() > prob:
            return 0
        else:
            return 1
# total 400x1000x450
# Order from top to bottom is SO,SP,SR,SLM total


def make_layer_grid(xstart,ystart,zstart,x_length,y_length,z_length,min_dist):
    x_grid = np.arange(xstart, x_length+min_dist, min_dist)
    y_grid = np.arange(ystart, y_length+min_dist, min_dist)
    z_grid = np.arange(zstart, z_length+min_dist, min_dist)
    xx, yy, zz = np.meshgrid(x_grid, y_grid, z_grid)
    return np.vstack([xx.ravel(), yy.ravel(), zz.ravel()]).T


#wrapper function for adding nodes to net, since there are not many params to change each time
def setNodes(netObj,Number,posList,popName,mTemplate):
    inds = rng.choice(np.arange(0, posList.shape[0]), Number, replace=False)

    # Place cell
    netObj.add_nodes(N=Number, pop_name=popName,
                positions=positions_list(positions=posList[inds, :]),
                mem_potential='e',
                model_type='biophysical',
                model_template=mTemplate,
                rotation_angle_zaxis=(np.pi/2), #90 degrees
                morphology=None)

    return np.delete(posList, inds, 0)



def setEdges(netObj,src,dest,conParams,dynamics_name,dist_range,secName,secID,secx):
    conn = netObj.add_edges(source={'pop_name': src}, target={'pop_name': dest},
                     
                     connection_rule=n_connections,
                     connection_params={'prob': conParams[0], 'max_dist': conParams[1]},  
                     delay=0.8,
                     syn_weight = syn[dynamics_name]['initW_lognormal_mean'],
                     dynamics_params=dynamics_name,
                     model_template=syn[dynamics_name]['level_of_detail'],
                     distance_range=dist_range,
                     target_sections=[secName],
                     sec_id = secID,  # check and is working putting syn on right location
                     sec_x = secx)
    return conn

############################## x,y,z,     xlen,ylen,zlen, space
pos_list_SO = make_layer_grid( 0,0,320,   400,1000,450,  20)
pos_list_SP = make_layer_grid( 0,0,290,   400,1000,320,   8)
pos_list_SR = make_layer_grid( 0,0, 80,   400,1000,290,  20)


########## add cells and connections to the network

pos_list_SO = setNodes(net,numAAC_inSO,pos_list_SO,'AAC','hoc:axoaxoniccell')
pos_list_SO = setNodes(net,numOLM_inSO,pos_list_SO,'OLM','hoc:olmcell')
pos_list_SO = setNodes(net,numPV_inSO,pos_list_SO,'PV','hoc:pvbasketcell')

pos_list_SP = setNodes(net,numPyr_inSP,pos_list_SP,'Pyr','hoc:pyramidalcell')
pos_list_SP = setNodes(net,numAAC_inSP,pos_list_SP,'AAC','hoc:axoaxoniccell')
pos_list_SP = setNodes(net,numPV_inSP,pos_list_SP,'PV','hoc:pvbasketcell')

pos_list_SR = setNodes(net,numAAC_inSR,pos_list_SR,'AAC','hoc:axoaxoniccell')
pos_list_SR = setNodes(net,numPV_inSR,pos_list_SR,'PV','hoc:pvbasketcell')

#############        src     dest   prob      maxd     json              dist_range    secName sid secloc
conn1 = setEdges(net,'AAC','Pyr', [ 0.0168,  400],'CHN2PN.json', [1,            1.1 ],'axon',  6, 0.5)
conn2 = setEdges(net,'Pyr','AAC', [ 0.0121,  400],'PN2CHN.json', [0.0,        400.0],'apical', 6, 0.5)
conn3 = setEdges(net,'PV','Pyr',  [ 0.0350,  400],'PV2PN.json',  [0.0,        400.0],'somatic',0, 0.5)
conn4 = setEdges(net,'Pyr','PV',  [ 0.0119,  400],'PN2PV.json',  [0.0,        400.0],'apical', 6, 0.5)
conn5 = setEdges(net,'PV','AAC',  [ 0.0212,  400],'PV2CHN.json', [0.0,        400.0],'somatic',0, 0.5)
conn6 = setEdges(net,'PV','PV',   [ 0.02087, 400],'PV2PV.json',  [0.0,        400.0],'somatic',0, 0.5)
conn7 = setEdges(net,'OLM','Pyr', [ 0.02242, 400],'OLM2PN.json', [0.0,        400.0],'apical', 4, 0.5)
conn8 = setEdges(net,'OLM','AAC', [ 0.0231,  400],'OLM2CHN.json',[0.0,        400.0],'apical', 4, 0.5)
conn9 = setEdges(net,'OLM','PV',  [ 0.02276, 400],'OLM2PV.json', [0.0,        400.0],'apical', 4, 0.5)
conn10 = setEdges(net,'OLM','OLM',[ 0.0222,  400],'OLM2OLM.json',[0.0,        400.0],'basal',  0, 0.9)
conn11 = setEdges(net,'Pyr','OLM',[ 0.0122,  400],'PN2OLM.json', [0.0,        400.0],'basal',  2, 0.5)





def lognormal(source, target,m,s):

    mean = np.log(m) - 0.5 * np.log((s / m) ** 2 + 1)
    std = np.sqrt(np.log((s / m) ** 2 + 1))
    synaptic_weight = np.random.lognormal(mean, std, 1)
    
    if source['pop_name'] == 'AAC':
        
        synaptic_weight = float(np.random.lognormal(m, s, 1)-np.mean(np.random.lognormal(m,s,1000)))
        if synaptic_weight >= float(m*1.2):
            synaptic_weight = float(m*1.2)
        if synaptic_weight < 0:
            synaptic_weight = 0.1*m

    
    return synaptic_weight


connList = [conn1,conn2,conn3,conn4,conn5,conn6,conn7,conn8,conn9,conn10,conn11]
for conn in connList:
    conn.add_properties('syn_weight', rule=lognormal,rule_params={'m': syn[conn._edge_type_properties['dynamics_params']]["initW_lognormal_mean"],
    's': syn[conn._edge_type_properties['dynamics_params']]["initW_lognormal_std"]},  dtypes=np.float64)

net.build()
net.save(output_dir='network')

"""
t_sim = 300
build_env_bionet(base_dir='./',
                network_dir='network',
                config_file='config.json',
                tstop=t_sim, dt=0.1,
                report_vars=['v'],
                clamp_reports=['se'],
                se_voltage_clamp={
                      "amps":[[-70, -70, -70]],
                     "durations": [[t_sim, t_sim, t_sim]],
                     'gids': [0],
                     'rs': [0.01],
                },
                components_dir='biophys_components',

                v_init=-63,
                compile_mechanisms=False)



tstop=t_sim, dt = 0.1,
report_vars = ['v'],
clamp_reports=['se'],#Records se clamp currents.
                se_voltage_clamp={
                     "amps":[[-70, -70, -70]],
                     "durations": [[t_sim, t_sim, t_sim]],
                     'gids': [5142],
                     'rs': [0.01],
                }

#use the below on the first build, then add mechanisms directory to the circuit config manually and comment out what is below

build_env_bionet(base_dir='./',
                network_dir='./network',
                config_file='config.json',
                tstop=t_stim, dt=0.1,
                report_vars=['v'],
                components_dir='biophys_components',
                
                spikes_inputs=[('bgpn', 'CA1_inputs/bg_pn_spikes.h5')],

                v_init=-70,
                compile_mechanisms=False)
"""



#print('Number of background spikes to PN cells: {}'.format(psg.n_spikes()))




