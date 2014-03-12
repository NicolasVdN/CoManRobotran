//---------------------------
// Nicolas Van der Noot
//
// Creation : 24-Jan-2014
// Last update : Tue Mar 11 16:48:31 2014
//---------------------------

#include <stdlib.h>

#include "ControllersStruct.h"


// ---- Controlleres initialization ---- //
 
// ControllerInputsStruc
ControllerInputsStruct * init_ControllerInputsStruct(void)
{
    ControllerInputsStruct *cvs;

    int i;

    cvs = (ControllerInputsStruct*) malloc(sizeof(ControllerInputsStruct));

    cvs->t = 0.0;

    for (i=0;i<23;i++)
    {
		cvs->q[i] = 0.0;
    }

    for (i=0;i<23;i++)
    {
		cvs->qd[i] = 0.0;
    }

    for (i=0;i<23;i++)
    {
		cvs->Qq[i] = 0.0;
    }

    for (i=0;i<3;i++)
    {
		cvs->F_Rfoot[i] = 0.0;
    }

    for (i=0;i<3;i++)
    {
		cvs->F_Lfoot[i] = 0.0;
    }

    for (i=0;i<3;i++)
    {
		cvs->T_Rfoot[i] = 0.0;
    }

    for (i=0;i<3;i++)
    {
		cvs->T_Lfoot[i] = 0.0;
    }

    for (i=0;i<9;i++)
    {
		cvs->IMU_Orientation[i] = 0.0;
    }

    for (i=0;i<3;i++)
    {
		cvs->IMU_Angular_Rate[i] = 0.0;
    }

    return cvs;
}

// ControllerOutputsStruc
ControllerOutputsStruct * init_ControllerOutputsStruct(void)
{
    ControllerOutputsStruct *cvs;

    int i;

    cvs = (ControllerOutputsStruct*) malloc(sizeof(ControllerOutputsStruct));

    for (i=0;i<23;i++)
    {
		cvs->q_ref[i] = 0.0;
    }

    for (i=0;i<23;i++)
    {
		cvs->qd_ref[i] = 0.0;
    }

    for (i=0;i<23;i++)
    {
		cvs->Qq_ref[i] = 0.0;
    }

    for (i=0;i<23;i++)
    {
		cvs->imp_ctrl_index[i] = 0;
    }

    return cvs;
}

// ControllerStruc
ControllerStruct * init_ControllerStruct(void)
{
    ControllerStruct *cvs;

    int i;

    cvs = (ControllerStruct*) malloc(sizeof(ControllerStruct));

    for (i=0;i<10;i++)
    {
		cvs->out1[i] = 0.0;
    }

    for (i=0;i<10;i++)
    {
		cvs->out2[i] = 0.0;
    }

    cvs->interact = 0.0;

    cvs->test_opti = 0.0;

    cvs->Outputs = init_ControllerOutputsStruct();

    cvs->Inputs = init_ControllerInputsStruct();

    return cvs;
}

// ---- Controllers: free ---- //

// ControllerInputsStruc
void free_ControllerInputsStruct(ControllerInputsStruct *cvs)
{
    free(cvs);
}

// ControllerOutputsStruc
void free_ControllerOutputsStruct(ControllerOutputsStruct *cvs)
{
    free(cvs);
}

// ControllerStruc
void free_ControllerStruct(ControllerStruct *cvs)
{
    free_ControllerOutputsStruct(cvs->Outputs);

    free_ControllerInputsStruct(cvs->Inputs);

    free(cvs);
}

