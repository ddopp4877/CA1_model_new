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
from scipy import stats
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


totalCellNum = numAAC_inSO + numPV_inSO + numOLM_inSO + numAAC_inSP + numPV_inSP+  numPyr_inSP+ numAAC_inSR  + numPV_inSR


from scipy.stats import norm

def conn_prob_rule(src, trg, max_dist,pdf_lookup):
    """Referenced by add_edges() and called by build() for every source/target pair. For every given target/source
    pair will connect the two with a probability prob (excludes self-connections)"""
    if src.node_id == trg.node_id:
        return 0

    src_pos = src['positions']
    trg_pos = trg['positions']
    dist = np.sqrt((src_pos[0] - trg_pos[0]) ** 2 + (src_pos[1] - trg_pos[1]) ** 2 + (src_pos[2] - trg_pos[2]) ** 2)
    
    if dist <= max_dist:
        
        test_prob = np.random.uniform()
        if int(dist) not in pdf_lookup.index:
            return 0
        
        dist_conn_prob = np.array(pdf_lookup.iloc[int(dist)])
        
        if test_prob <= dist_conn_prob:
            return 1
        else:
            return 0

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



def setEdges(netObj,src,dest,conn_rule, connection_params,dynamics_name,dist_range,secName,secID,secx):
    conn = netObj.add_edges(source={'pop_name': src}, target={'pop_name': dest},
                     
                     connection_rule=conn_rule,
                     connection_params={'max_dist': connection_params[1], 'pdf_lookup': connection_params[0]},  
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



from scipy.stats import norm

max_distance = 400

def make_lookup(mean,std_dev,pmax ):
    x = np.arange((-1)*max_distance,max_distance)
    pdf_values = norm.pdf(x, loc=mean, scale=std_dev)
    scaled_pdf_values = pdf_values * (pmax / np.max(pdf_values))
    scaled_pdf_values = scaled_pdf_values[max_distance:]
    pdf_lookup = pd.DataFrame(scaled_pdf_values)
    return pdf_lookup

i2e_lookup = make_lookup(0,96.6,0.15)
e2i_lookup = make_lookup(0,99.84,0.12)
i2i_lookup = make_lookup(0,126.77,0.12)

#############        src     dest  conn_rule         pdf_lookup,        maxd             json           dist_range    max_dist     secName secid secloc
conn1 = setEdges(net,'AAC','Pyr',  conn_prob_rule,   [i2e_lookup,  max_distance],     'CHN2PN.json',      [1,             1.1 ], 'axon',     6,    0.5)
conn2 = setEdges(net,'Pyr','AAC',  conn_prob_rule,   [e2i_lookup,  max_distance],     'PN2CHN.json',      [0.0,   max_distance], 'apical',  6,    0.5)
conn3 = setEdges(net,'PV','Pyr',   conn_prob_rule,   [i2e_lookup,  max_distance] ,    'PV2PN.json',       [0.0,   max_distance], 'somatic', 0,    0.5)
conn4 = setEdges(net,'Pyr','PV',   conn_prob_rule,   [e2i_lookup,  max_distance],     'PN2PV.json',       [0.0,   max_distance], 'apical',  6,    0.5)
conn5 = setEdges(net,'PV','AAC',   conn_prob_rule,   [i2i_lookup,  max_distance],     'PV2CHN.json',      [0.0,   max_distance], 'somatic', 0,    0.5)
conn6 = setEdges(net,'PV','PV',    conn_prob_rule,   [i2i_lookup,  max_distance],     'PV2PV.json',       [0.0,   max_distance], 'somatic', 0,    0.5)
conn7 = setEdges(net,'OLM','Pyr',  conn_prob_rule,   [i2e_lookup,  max_distance],     'OLM2PN.json',      [0.0,   max_distance], 'apical',  4,    0.5)
conn8 = setEdges(net,'OLM','AAC',  conn_prob_rule,   [i2i_lookup,  max_distance],     'OLM2CHN.json',     [0.0,   max_distance], 'apical',  4,    0.5)
conn9 = setEdges(net,'OLM','PV',   conn_prob_rule,   [i2i_lookup,  max_distance],     'OLM2PV.json',      [0.0,   max_distance], 'apical',  4,    0.5)
conn10 = setEdges(net,'OLM','OLM', conn_prob_rule,   [i2i_lookup,  max_distance],     'OLM2OLM.json',     [0.0,   max_distance], 'basal',   0,    0.9)
conn11 = setEdges(net,'Pyr','OLM', conn_prob_rule,   [e2i_lookup,  max_distance],     'PN2OLM.json',      [0.0,   max_distance], 'basal',   2,    0.5)





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






