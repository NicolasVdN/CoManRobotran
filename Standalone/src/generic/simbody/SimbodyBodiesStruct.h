

#ifndef __SIMBODYSTRUCT_H__
#define __SIMBODYSTRUCT_H__

#ifdef SIMBODY

#define S_RFOOTS 15
#define S_LFOOTS 27

// feet external forces
#define RFOOT_FSENS_ID 1
#define LFOOT_FSENS_ID 2

#define NB_CONTACT_BODIES 2

typedef struct SimbodyBodiesStruct
{
	int nb_contact_bodies;

	int F_sensor_Robotran_index[NB_CONTACT_BODIES];
	int S_sensor_Robotran_index[NB_CONTACT_BODIES];
	//int Simbody_index[NB_CONTACT_BODIES]; // N
	//MobilizedBodyIndex Simbody_index[NB_CONTACT_BODIES]; // Z
	int Simbody_index[NB_CONTACT_BODIES];


	double abs_pos_CoM[NB_CONTACT_BODIES][3];
	double rot_matrix[NB_CONTACT_BODIES][9];
	double lin_vel_CoM[NB_CONTACT_BODIES][3];
	double ang_vel_CoM[NB_CONTACT_BODIES][3];

	double force_bodies[NB_CONTACT_BODIES][3];
	double torque_bodies[NB_CONTACT_BODIES][3];
// AP calculated by Simbody	
	double AP[NB_CONTACT_BODIES][3];

} SimbodyBodiesStruct;



#else

typedef struct SimbodyBodiesStruct
{
	int nothing;
} SimbodyBodiesStruct;

#endif

SimbodyBodiesStruct *init_SimbodyBodiesStruct();
void free_SimbodyBodiesStruct(SimbodyBodiesStruct *simbodyBodiesStruct);

#endif
