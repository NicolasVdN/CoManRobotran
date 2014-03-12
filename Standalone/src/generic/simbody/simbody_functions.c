#ifdef SIMBODY

#include "simbody_functions.h"
#include "project_info.h"

#include "simu_def.h"

void update_simbody_kinematics(SimbodyBodiesStruct* simbodyBodiesStruct, MBSdataStruct *MBSdata)
{
	int i, j;
	MBSsensorStruct CoM_sensor;

	allocate_sensor(&CoM_sensor,NB_JOINTS);
    init_sensor(&CoM_sensor,NB_JOINTS);
    

	for(i=0; i<simbodyBodiesStruct->nb_contact_bodies; i++)
	{
		sensor(&CoM_sensor, MBSdata, simbodyBodiesStruct->S_sensor_Robotran_index[i]);

		for(j=0; j<3; j++)
		{
			simbodyBodiesStruct->abs_pos_CoM[i][j] = CoM_sensor.P[j+1];
			simbodyBodiesStruct->lin_vel_CoM[i][j] = CoM_sensor.V[j+1];
			simbodyBodiesStruct->ang_vel_CoM[i][j] = CoM_sensor.OM[j+1];
		}
        		
		simbodyBodiesStruct->rot_matrix[i][0] = CoM_sensor.R[1][1];
		simbodyBodiesStruct->rot_matrix[i][1] = CoM_sensor.R[1][2];
		simbodyBodiesStruct->rot_matrix[i][2] = CoM_sensor.R[1][3];
		simbodyBodiesStruct->rot_matrix[i][3] = CoM_sensor.R[2][1];
		simbodyBodiesStruct->rot_matrix[i][4] = CoM_sensor.R[2][2];
		simbodyBodiesStruct->rot_matrix[i][5] = CoM_sensor.R[2][3];
     	simbodyBodiesStruct->rot_matrix[i][6] = CoM_sensor.R[3][1];
		simbodyBodiesStruct->rot_matrix[i][7] = CoM_sensor.R[3][2];
		simbodyBodiesStruct->rot_matrix[i][8] = CoM_sensor.R[3][3];

	}

	free_sensor(&CoM_sensor);
}

#endif


