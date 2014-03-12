/*
 * Erase and replace the hard-coded values of the simulation
 * by the ones coming from the optimization algorithm'
 */

// 2014-3-11 16:43 (Date of file automatic generation)
#ifdef OPTI

#include "opti_def.h"

void erase_for_opti(double *optiParams, MBSdataStruct *MBSdata) 
{
    int i;

    UserIOStruct *uvs;
    ControllerStruct *cvs;

    uvs = MBSdata->user_IO;
    cvs = uvs->cvs;

    //***************************************************************************************************
    //			TEST OPTIMIZATION 
    //***************************************************************************************************
    // simple test for the optimization
    cvs->test_opti = optiParams[0];

}

#endif
