#ifdef SIMBODY

#ifndef _SIMBODY_CPP_FUNCTIONS_H_
#define _SIMBODY_CPP_FUNCTIONS_H_


#include "Simbody.h"

#include <cstdio>
#include <exception>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "SimTKcommon/internal/Mat.h"
#include "SimTKcommon/internal/Rotation.h"
#include "SimTKcommon/internal/Quaternion.h"
#include "simbody/internal/ElasticFoundationForce.h"
#include "simbody/internal/CompliantContactSubsystem.h"
#include "simmath/internal/Contact.h"

extern "C" 
{
  #include "SimbodyBodiesStruct.h"
}


using namespace SimTK;

typedef struct SimbodyVariables SimbodyVariables;
struct SimbodyVariables
{
 // Z: now we don't need it - we store it in the SimbodyBodiesStruct	MobilizedBodyIndex BodyInd;  // it should be changed on an array of indexes if we want more than one body in simulation. I don't know how to do it yet
	MultibodySystem *p_system;
	SimbodyMatterSubsystem *p_matter;
	ContactTrackerSubsystem  *p_tracker; 
    CompliantContactSubsystem *p_contactForces;
	State *p_state;

};
 
/* typedef struct CinematicParameters   CinematicParameters;
 struct CinematicParameters
 {
   double absolute_position_CoM[3];
   double linear_vel_CoM[3];
   double angular_vel_CoM[3];
   double rotation_matrix_CoM[3][3];
 };
  
typedef struct Wrench Wrench;
struct Wrench
 {
   bool filled;
   MobilizedBodyIndex BodyInd;
   double Force[3];
   double Torque[3]; // Application point is always center of mass of the body
 };
*/


//int init_Simbody(SimbodyVariables *p_simbodyVariables); // Z
 int init_Simbody(SimbodyVariables *p_simbodyVariables, SimbodyBodiesStruct *p_simbodyBodiesStruct);
 // old : Wrench loop_Simbody (SimbodyVariables *p_simbodyVariables, SimbodyBodiesStruct* simbodyBodiesStruct, int index);
 int loop_Simbody (SimbodyVariables *p_simbodyVariables, SimbodyBodiesStruct* simbodyBodiesStruct);


#endif
#endif
