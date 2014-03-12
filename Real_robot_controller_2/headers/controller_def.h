//---------------------------
// Creation : 29/10/2013
// Last update : 29/10/2013
//
// Controller main header file
//
//---------------------------

#ifndef controller_def_h
#define controller_def_h
//--------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Uncomment the ' #include "simstruc.h" ' line to have access
 * to the ' printf ' function in the controller files in Matlab
 * (the results of the printf will be available in the 'Command Window' of Matlab)
 *
 * This line must be commented before transfering the controller to the real robot
 */
//#include "simstruc.h"

#include "ControllersStruct.h"

// ---- Constants & Macros ---- //


// -- Motors numbering -- //


// right leg
#define R_HIP_SAG_DOF 3
#define R_HIP_LAT_DOF 5
#define R_HIP_YAW_DOF 6
#define R_KNEE_SAG_DOF 7
#define R_ANK_LAT_DOF 9
#define R_ANK_SAG_DOF 8

// left leg
#define L_HIP_SAG_DOF 4
#define L_HIP_LAT_DOF 10
#define L_HIP_YAW_DOF 11
#define L_KNEE_SAG_DOF 12
#define L_ANK_LAT_DOF 14
#define L_ANK_SAG_DOF 13

// waist
#define WAIST_LAT_DOF 2
#define WAIST_SAG_DOF 1
#define WAIST_YAW_DOF 0

// right arm
#define R_SH_SAG_DOF 15
#define R_SH_LAT_DOF 16
#define R_SH_YAW_DOF 17
#define R_ELB_DOF 18

// left arm
#define L_SH_SAG_DOF 19
#define L_SH_LAT_DOF 20
#define L_SH_YAW_DOF 21
#define L_ELB_DOF 22

// number of joints
#define COMAN_NB_JOINT_ACTUATED	 23

// tracking: position, velocity or torque
#define Q_REF_TRACKING 1
#define QD_REF_TRACKING 2
#define QQ_REF_TRACKING 3

// pi
#define PI 3.14159265359
#define PI_2 (PI/2.0)
#define DEG_TO_RAD (PI/180.0)



// ---- Custom Functions ---- //

// initialization and main loop
void controller_init(ControllerStruct *cvs);
void controller_loop(ControllerStruct *cvs);


void get_ref(ControllerStruct *cvs);

void opti_parameters_init_controller(ControllerStruct *cvs);


/*--------------------*/
#endif
