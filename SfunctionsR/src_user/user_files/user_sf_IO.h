/*===========================================================================*
 *
 *  user_sf_IO.h
 * 
 *  Generation date: Tue Mar 11 17:36:27 2014

 * 
 *  (c) Universite catholique de Louvain
 *      Departement de Mecanique 
 *      Unite de Production Mecanique et Machines 
 *      2, Place du Levant 
 *      1348 Louvain-la-Neuve 
 *  http://www.robotran.be// 
 *  
/*===========================================================================*/

#ifndef UsersfIO_h
#define UsersfIO_h
/*--------------------*/
 
#include "userDef.h"
#include "ControllersStruct.h"
 
typedef struct UserIOStruct 
{
    double Voltage[23+1];
    double Control[23+1];
    double Actuator_KKs[31+1];
    double Actuator_DDs[31+1];
    double Actuator_Jdrives;
    double Actuator_Ddrives;
    double Actuator_VTgain;
    int actuated2real[23+1];
    double joint_limits_min[31+1];
    double joint_limits_max[31+1];
    double GRF_r[3+1];
    double GRF_l[3+1];
    double GRM_r[3+1];
    double GRM_l[3+1];
    double GRF_r_dist[3+1];
    double GRF_l_dist[3+1];
    double GRM_r_dist[3+1];
    double GRM_l_dist[3+1];
    double mu_grf;
    double F_left_leg;
    double F_right_leg;
    int Msize_GCM;
    int Msize_GCM_prox;
    int Msize_GCM_dist;
    double rn_left_x[200+1];
    double rn_left_y[200+1];
    double rn_left_z[200+1];
    double rn_right_x[200+1];
    double rn_right_y[200+1];
    double rn_right_z[200+1];
    double temp_grfx_left[200+1];
    double temp_grfy_left[200+1];
    double temp_grfx_right[200+1];
    double temp_grfy_right[200+1];
    int flag_grfx_left[200+1];
    int flag_grfy_left[200+1];
    int flag_grfx_right[200+1];
    int flag_grfy_right[200+1];
    double rn_left_prox_x[150+1];
    double rn_left_prox_y[150+1];
    double rn_left_prox_z[150+1];
    double rn_right_prox_x[150+1];
    double rn_right_prox_y[150+1];
    double rn_right_prox_z[150+1];
    double temp_grfx_left_prox[150+1];
    double temp_grfy_left_prox[150+1];
    double temp_grfx_right_prox[150+1];
    double temp_grfy_right_prox[150+1];
    int flag_grfx_left_prox[150+1];
    int flag_grfy_left_prox[150+1];
    int flag_grfx_right_prox[150+1];
    int flag_grfy_right_prox[150+1];
    double rn_left_dist_x[60+1];
    double rn_left_dist_y[60+1];
    double rn_left_dist_z[60+1];
    double rn_right_dist_x[60+1];
    double rn_right_dist_y[60+1];
    double rn_right_dist_z[60+1];
    double temp_grfx_left_dist[60+1];
    double temp_grfy_left_dist[60+1];
    double temp_grfx_right_dist[60+1];
    double temp_grfy_right_dist[60+1];
    int flag_grfx_left_dist[60+1];
    int flag_grfy_left_dist[60+1];
    int flag_grfx_right_dist[60+1];
    int flag_grfy_right_dist[60+1];
    double last_tsim_int_tau;
    double last_err_tau[23+1];
    double last_int_err_tau[23+1];
    double real_theta_3_waist;
    double real_omega_3_waist;
    double waist_relative_ground;
    double last_t_ctrl;
    double Qq_out[23+1];
    double tsim_out;
    double q_ref[23+1];
    double qd_ref[23+1];
    double Qq_ref[23+1];
    int imp_ctrl_index[23+1];
    int stop_out;
    double out1[10+1];
    double out2[10+1];
    double out3[10+1];
    double out4[10+1];
    double out5[10+1];
    double fitness_opti;
    ControllerStruct *cvs;
    SimbodyBodiesStruct *simbodyBodies;

} UserIOStruct;

/*--------------------*/
#endif
