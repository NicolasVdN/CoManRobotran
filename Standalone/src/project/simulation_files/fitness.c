//---------------------------
//
// Nicolas Van der Noot
//
// Creation : 01/11/2013
// Last update : 01/11/2013
//
// Computes the objective function fr the optimization process
//
//---------------------------

#include "simu_def.h"
#include "project_info.h"

void fitness(MBSdataStruct *MBSdata)
{
	// --- Declarations --- //
    
	UserIOStruct *uvs;
    
    uvs = MBSdata->user_IO;
    
    uvs->fitness_opti = 0.0;
   
}
