//---------------------------
// Nicolas Van der Noot
//
// Creation : 29/10/2013
// Last update : 29/10/2013
//
// Main loop of the controller and user simulation files
//
//---------------------------

#include "simu_def.h"

void simu_controller_loop(MBSdataStruct *MBSdata)
{
    double tsim;

    ControllerStruct *cvs;
    UserIOStruct *uvs;

    uvs = MBSdata->user_IO;
	cvs = uvs->cvs;

    tsim = MBSdata->tsim;
    
    // controller
    if (tsim >= uvs->last_t_ctrl + PERIOD_CTRL - TIME_EPSILON)
    {
        uvs->last_t_ctrl = tsim;
        
        controller_inputs(MBSdata);
        controller_loop(cvs);
        controller_outputs(MBSdata);
    }

    // simulation outputs
    simu_outputs(MBSdata);
    
    // objective function
    fitness(MBSdata);

	// stopping the simulation if needed
	stop_simu(MBSdata);
}
