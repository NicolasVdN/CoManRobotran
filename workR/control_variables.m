function [controllers_struct] = control_variables()

% Definition of the control variables
% For each line: varname , type , size/str_type
%  - varname: name of the variable (with '')
%  - type: 'int' / 'double' / 'structure'
%      if type == 'int' / 'double'
%          - size/str_type: number of elements in the vector
%               1    :  simple variable
%               n    :  vector of n (n>1) elements
%               [m n]:  tabular of 2 entries with a size m*n 
%      if type == 'structure' 
%          - size/str_type: the type of the structure (its name with '')

%% controller_1

controller_1_name = 'ControllerInputs';
controller_1_vars = {
    't','double',1
    'q','double',23
    'qd','double',23
    'Qq','double',23
    'F_Rfoot','double',3
    'F_Lfoot','double',3
    'T_Rfoot','double',3
    'T_Lfoot','double',3
    'IMU_Orientation','double',9
    'IMU_Angular_Rate','double',3
};


%% controller_2

controller_2_name = 'ControllerOutputs';
controller_2_vars = {
    'q_ref','double',23
    'qd_ref','double',23
    'Qq_ref','double',23
    'imp_ctrl_index','int',23
};


%% controller_3

controller_3_name = 'MuscleProperties';
controller_3_vars = {
    'muscle_id','int',1
    'l_mtu','double',1
    'l_ce','double',1
    'l_se','double',1
    'v_ce','double',1
    'f_v','double',1
    'f_l','double',1
    'F_se','double',1
    'F_be','double',1
    'F_pe_star','double',1
    'F_ce','double',1
    'F_m','double',1
    'l_opt','double',1
    'l_slack','double',1
    'l_min','double',1
    'F_max','double',1
    'v_max','double',1
    'A','double',1
    'Stim','double',1
    'Stim_new','double',1
    'noise_activation','double',1
    'noise_last_random','double',1
    'noise_new_random','double',1
    'm_mtu','double',1
    't_I','double',1
};


%% controller_4

controller_4_name = 'SagMuscles';
controller_4_vars = {
    'r_m','double',9
    'r0','double',9
    'phi_max','double',9
    'phi_ref','double',9
    'rho','double',9
    'phi_hip','double',1
    'phi_hip_point','double',1
    'phi_knee','double',1
    'phi_knee_point','double',1
    'phi_ankle','double',1
    'phi_ankle_point','double',1
    'SOL_muscle','structure','MuscleProperties'
    'TA_muscle','structure','MuscleProperties'
    'GAS_muscle','structure','MuscleProperties'
    'VAS_muscle','structure','MuscleProperties'
    'HAM_muscle','structure','MuscleProperties'
    'GLU_muscle','structure','MuscleProperties'
    'HFL_muscle','structure','MuscleProperties'
};


%% controller_5

controller_5_name = 'Controller';
controller_5_vars = {
    't','double',1
    'q_coman','double',23
    'qd_coman','double',23
    'Qq_coman','double',23
    'F_Rfoot','double',1
    'F_Lfoot','double',1
    'theta_1_waist','double',1
    'theta_2_waist','double',1
    'theta_3_waist','double',1
    'omega_1_waist','double',1
    'omega_2_waist','double',1
    'omega_3_waist','double',1
    'Inputs','structure','ControllerInputs'
    'q_ref','double',23
    'qd_ref','double',23
    'Qq_ref','double',23
    'imp_ctrl_index','int',23
    'Outputs','structure','ControllerOutputs'
    'out1','double',10
    'out2','double',10
    'theta_1_torso','double',1
    'theta_2_torso','double',1
    'theta_3_torso','double',1
    'omega_1_torso','double',1
    'omega_2_torso','double',1
    'omega_3_torso','double',1
    'pos_sh_lat_right','double',1
    'pos_sh_sag_right','double',1
    'pos_sh_yaw_right','double',1
    'pos_elb_right','double',1
    'pos_sh_lat_left','double',1
    'pos_sh_sag_left','double',1
    'pos_sh_yaw_left','double',1
    'pos_elb_left','double',1
    'pos_trunk_yaw','double',1
    'tau_hip_right_sag','double',1
    'tau_knee_right_sag','double',1
    'tau_ankle_right_sag','double',1
    'tau_hip_left_sag','double',1
    'tau_knee_left_sag','double',1
    'tau_ankle_left_sag','double',1
    'tau_hip_right_lat','double',1
    'tau_ank_right_lat','double',1
    'tau_hip_left_lat','double',1
    'tau_ank_left_lat','double',1
    'tau_hip_right_yaw','double',1
    'tau_hip_left_yaw','double',1
    'force_vec_index','int',1
    'mean_right_force','double',1
    'mean_left_force','double',1
    'right_force_vec','double',50
    'left_force_vec','double',50
    'first_tsim_right_stance','double',1
    'first_tsim_left_stance','double',1
    'last_tsim_right_stance','double',1
    'last_tsim_left_stance','double',1
    'flag_right_step','int',1
    'flag_left_step','int',1
    't_flag_right_step','double',1
    't_flag_left_step','double',1
    'steps_achieved','int',1
    'nb_strikes','int',1
    'stance_step','int',1
    'swing_right','int',1
    'swing_left','int',1
    'last_right_in_swing','int',1
    'right_leg_ref_stance','int',1
    'left_first_swing','int',1
    'trailing_leg_right','int',1
    'trailing_leg_left','int',1
    'coman_states','int',1
    'HG_init_state','int',1
    'last_t_ref_stance','double',1
    'arm_trunk_opti','double',5
    'init_ankle_pos','double',1
    'RightSagLeg','structure','SagMuscles'
    'LeftSagLeg','structure','SagMuscles'
    'Tau_soft_stim','double',6
    'Tau_soft_filter','double',6
    'last_HG_tsim','double',1
    'HG_virtual_tsim','double',1
    'last_HG_virtual_tsim','double',1
    'full_HG_time_control','int',1
    'theta_trunk','double',1
    'theta_point_trunk','double',1
    'theta_take_off','double',1
    'HG_request_input','double',25
    'F_SOL_right_delay','double',64
    'F_SOL_left_delay','double',64
    'F_GAS_right_delay','double',64
    'F_GAS_left_delay','double',64
    'F_VAS_right_delay','double',64
    'F_VAS_left_delay','double',64
    'F_HAM_right_delay','double',64
    'F_HAM_left_delay','double',64
    'F_GLU_right_delay','double',64
    'F_GLU_left_delay','double',64
    'F_right_leg_delay','double',64
    'F_left_leg_delay','double',64
    'l_CE_TA_right_delay','double',64
    'l_CE_TA_left_delay','double',64
    'l_CE_HFL_right_delay','double',64
    'l_CE_HFL_left_delay','double',64
    'l_CE_HAM_right_delay','double',64
    'l_CE_HAM_left_delay','double',64
    'phi_k_right_delay','double',64
    'phi_k_left_delay','double',64
    'phi_k_point_right_delay','double',64
    'phi_k_point_left_delay','double',64
    'theta_trunk_delay','double',64
    'theta_point_trunk_delay','double',64
    'theta_trunk_PTO_delay','double',64
    'S_0_HG','double',7
    'G_HG','double',9
    'OFF_HG','double',4
    'k_HG','double',5
    'theta_ref','double',1
    'delta_S','double',1
    'delta_I_TA_SW','double',1
    'delta_I_TA_ST','double',1
    'delta_I_HFL_SW','double',1
    'delta_I_HFL_ST','double',1
    'last_tsim_noise_activation','double',1
    'metabolic_energy','double',1
    'A_dot_left','double',1
    'M_dot_left','double',1
    'S_dot_left','double',1
    'B_dot_left','double',1
    'W_dot_left','double',1
    'A_dot_right','double',1
    'M_dot_right','double',1
    'S_dot_right','double',1
    'B_dot_right','double',1
    'W_dot_right','double',1
    'opti_flag','int',1
    'last_t_Hill','double',1
};


%% controllers_vars

controllers_struct = {
    controller_1_name, controller_1_vars;
    controller_2_name, controller_2_vars;
    controller_3_name, controller_3_vars;
    controller_4_name, controller_4_vars;
    controller_5_name, controller_5_vars;
};

end
