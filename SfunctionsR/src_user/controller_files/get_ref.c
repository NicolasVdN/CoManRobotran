//---------------------------
//
// Nicolas Van der Noot
//
// Creation : 01/11/2013
// Last update : 01/11/2013
//
// Get the position, velocity ant torque references
//
//---------------------------

#include "controller_def.h"

void get_ref(ControllerStruct *cvs)
{
    // ---- Variables ---- //

    int i;
    double k;

    ControllerOutputsStruct *ovs;

    ovs = cvs->Outputs;
    
    // ---- References sent to the controller with limitations ---- //

    k = 0.1;
    
    // loop on all the motors
    for(i=0; i<COMAN_NB_JOINT_ACTUATED; i++)
    {
        // velocity reference
        ovs->qd_ref[i] = 0.0;

        // torque reference
        ovs->Qq_ref[i] = 0.0;

        // position reference for the right shoulder sagittal dof
        if (i == R_SH_SAG_DOF)
        {
        	ovs->q_ref[i] = k * cvs->interact;
        }
        // position reference for the other dofs
        else
        {
        	ovs->q_ref[i]  = 0.0;
        }

        // torque tracking for the left shoulder sagittal dof
        if (i == L_SH_SAG_DOF)
        {
            ovs->imp_ctrl_index[i] = QQ_REF_TRACKING;
        }
        // otherwise: positions tracking
        else
        {
            ovs->imp_ctrl_index[i] = Q_REF_TRACKING;
        }
    }
}
