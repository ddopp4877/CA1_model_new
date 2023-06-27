from neuron import h
import os, sys
from bmtk.simulator import bionet
import numpy as np
import synapses
import warnings
from bmtk.simulator.core import simulation_config 
import h5py
from bmtk.simulator.bionet import synaptic_weight
import pandas as pd
import json
def run(config_file):
    #warnings.simplefilter(action='ignore', category=FutureWarning)
    synapses.load()
    #from bmtk.simulator.bionet.pyfunction_cache import add_weight_function
    conf = bionet.Config.from_json(config_file, validate=True)



    conf.copy_to_output()
    conf.build_env()

    graph = bionet.BioNetwork.from_config(conf)

    

    # This fixes the morphology error in LFP calculation
    pop = graph._node_populations['biophysical']
    for node in pop.get_nodes():
        node._node._node_type_props['morphology'] = node.model_template[1]
                        #dict_keys(['pop_name', 'mem_potential', 'model_type', 'rotation_angle_zaxis', 'morphology', 'model_template', 'node_type_id'])
        #print(node._node._node_type_props['morphology'])




    sim = bionet.BioSimulator.from_config(conf, network=graph)
    

    sim.add_mod(bionet.modules.save_synapses.SaveSynapses('updated_conns'))


    # This calls insert_mechs() on each cell to use its gid as a seed
    # to the random number generator, so that each cell gets a different
    # random seed for the point-conductance noise
    cells = graph.get_local_cells()
    
    
    
    
    for cell in cells:
        cells[cell].hobj.insert_mechs(cells[cell].gid)

        
    
    # pos_dict = {}
    # prev_gid = 0
    # xs,ys,zs = [],[],[]
     
    # for sec in h.allsec():
    #     num_secs = sec.n3d()

    #     gid = str(sec).split('[')[1].split(']')[0]
    #     cell_name = str(sec).split(']')[0] + ']'
        
    #     if gid != prev_gid:
    #         prev_gid = gid
    #         pos_dict.update({f"cell_{cell_name}xpos": xs, f"cell_{cell_name}ypos":ys, f"cell_{cell_name}zpos":zs})
    #         xs,ys,zs = [],[],[]
            
    #     else:
                
    #         for i in range(num_secs):
    #             xs.append(sec.x3d(i))
    #             ys.append(sec.y3d(i))
    #             zs.append(sec.z3d(i))
        

             

        
    #     print(cell)
    #     pos_dict.update({f"cell_{cell}xpos": xs, f"cell_{cell}ypos":ys, f"cell_{cell}zpos":zs})
            
    
    # with open("cell_positions.json", "w") as file:
    #     json.dump(pos_dict, file)
                



    sim.run()


    
    bionet.nrn.quit_execution()

run('simulation_configLFP.json')
"""
if __name__ == '__main__':
    run('simulation_config.json')
    if __file__ != str(os.path.join(os.getcwd(),sys.argv[-1])):
        run(sys.argv[-1])
    else:
        run('simulation_config.json')
"""