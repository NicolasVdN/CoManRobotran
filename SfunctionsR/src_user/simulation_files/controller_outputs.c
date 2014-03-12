//---------------------------
// Nicolas Van der Noot
//
// Creation : 29/10/2013
// Last update : 29/10/2013
//
// Outputs of the controller
//
//---------------------------

#include "simu_def.h"

void controller_outputs(MBSdataStruct *MBSdata)
{
    int i;

    UserIOStruct *uvs;

    uvs = MBSdata->user_IO;

    // impedance controller
    impedance_controller(MBSdata);

    // convert voltage in torque form 
    //      uvs->Control[i] is the torque form (in [Nm])
    //      uvs->Voltage[i] is the voltage (in [V])
    // i is the index in the motor indexes list
    for(i=1; i<=COMAN_NB_JOINT_ACTUATED; i++)
    {
        uvs->Control[i] = uvs->Voltage[i]*(uvs->Actuator_VTgain);
    }
    
}

