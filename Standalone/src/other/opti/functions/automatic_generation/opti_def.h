/*
 * Header file used for the optimization
 */

// 2014-3-11 16:43 (Date of file automatic generation)

#ifndef _OPTI_DEF_H_
#define _OPTI_DEF_H_

#ifdef OPTI

#include <stdio.h>
#include <stdlib.h>
#include "MBSdataStruct.h"

// number of parameters to optimize
#define NB_PARAMS_TO_OPTIMIZE 1

#define OPTI_RUNS 3

double opti_fitness(double* optiNorms);
void erase_for_opti(double *optiParams, MBSdataStruct *MBSdata);
void get_real_params_to_opt(double *optiNorms, double *optiParams);

#endif

#endif

