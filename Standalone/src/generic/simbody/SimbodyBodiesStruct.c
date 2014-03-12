
#include "SimbodyBodiesStruct.h"
#include "useful_functions.h"

#ifdef SIMBODY

SimbodyBodiesStruct *init_SimbodyBodiesStruct()
{
	int i, j;


	SimbodyBodiesStruct *simbodyBodiesStruct;

	simbodyBodiesStruct = (SimbodyBodiesStruct*) malloc(sizeof(SimbodyBodiesStruct));

	simbodyBodiesStruct->nb_contact_bodies = NB_CONTACT_BODIES;

	
	simbodyBodiesStruct->S_sensor_Robotran_index[0] = S_LFOOTS;
	simbodyBodiesStruct->F_sensor_Robotran_index[0] = LFOOT_FSENS_ID;
	simbodyBodiesStruct->Simbody_index[0]           = 1;

	simbodyBodiesStruct->S_sensor_Robotran_index[1] = S_RFOOTS;
	simbodyBodiesStruct->F_sensor_Robotran_index[1] = RFOOT_FSENS_ID;
	simbodyBodiesStruct->Simbody_index[1]           = 2;


	for(i=0; i<NB_CONTACT_BODIES; i++)
	{
		for(j=0; j<3; j++)
		{
			simbodyBodiesStruct->abs_pos_CoM[i][j]   = 0.0;
			simbodyBodiesStruct->lin_vel_CoM[i][j]   = 0.0;
			simbodyBodiesStruct->ang_vel_CoM[i][j]   = 0.0;
			simbodyBodiesStruct->force_bodies[i][j]  = 0.0;
			simbodyBodiesStruct->torque_bodies[i][j] = 0.0;
//  AP calculated by Simbody				
			simbodyBodiesStruct->AP[i][j] = 0.0;
		}

		for(j=0; j<9; j++)
		{
			simbodyBodiesStruct->rot_matrix[i][j] = 0.0;
		}

		simbodyBodiesStruct->rot_matrix[i][0] = 1.0; simbodyBodiesStruct->rot_matrix[i][4] = 1.0; simbodyBodiesStruct->rot_matrix[i][8] = 1.0; // Z: to have identical rotation - not a singular one

	}

	return simbodyBodiesStruct;

}


void free_SimbodyBodiesStruct(SimbodyBodiesStruct *simbodyBodiesStruct)
{
	free(simbodyBodiesStruct);
}

#else

SimbodyBodiesStruct *init_SimbodyBodiesStruct()
{
	return NULL;
}

void free_SimbodyBodiesStruct(SimbodyBodiesStruct *simbodyBodiesStruct)
{
}

#endif
