#ifdef SIMBODY

#ifndef __SIMBODY_FUNCTIONS_H__
#define __SIMBODY_FUNCTIONS_H__


#include "SimbodyBodiesStruct.h"
#include "MBSdataStruct.h"


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


 void update_simbody_kinematics(SimbodyBodiesStruct* simbodyBodiesStruct, MBSdataStruct *MBSdata);


#endif
#endif
