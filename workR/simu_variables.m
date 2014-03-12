function [simu_vars_none, simu_vars_in, simu_vars_out, simu_vars_struct] = simu_variables()

% Definition of the simulation variables and I/O ports
% For each line: varname , type , size/str_type
% 4 types of simulation variables (simu_vars_none,...)
%       . none = internal variable (type: 'int'/'double')
%       . in = input (type: 'int'/'double')
%       . out = output (type: 'int'/'double')
%       . struct = structure variable (type: structure name with '')
%   - varname = name of the port or of the variable (with '')
%   - size = number of elements in the vector
%               (put '1' for 'simu_vars_struct')
%           (1: simple varibale,  >1: vector -> do not use the 0 index)

simu_vars_none = {
    'Voltage','double',23
    'Control','double',23
    'Actuator_KKs','double',29
    'Actuator_DDs','double',29
    'Actuator_Jdrives','double',1
    'Actuator_Ddrives','double',1
    'Actuator_VTgain','double',1
    'actuated2real','int',23
    'joint_limits_min','double',29
    'joint_limits_max','double',29
    'GRF_r','double',3
    'GRF_l','double',3
    'GRM_r','double',3
    'GRM_l','double',3
    'F_left_leg','double',1
    'F_right_leg','double',1
    'rn_left_x','double',200
    'rn_left_y','double',200
    'rn_left_z','double',200
    'rn_right_x','double',200
    'rn_right_y','double',200
    'rn_right_z','double',200
    'Msize_GCM','int',1
    'mu_grf','double',1
    'temp_grfx_left','double',200
    'temp_grfy_left','double',200
    'temp_grfx_right','double',200
    'temp_grfy_right','double',200
    'flag_grfx_left','int',200
    'flag_grfy_left','int',200
    'flag_grfx_right','int',200
    'flag_grfy_right','int',200
    'num_x_l_cop','double',1
    'num_y_l_cop','double',1
    'num_x_r_cop','double',1
    'num_y_r_cop','double',1
    'x_COP','double',1
    'y_COP','double',1
    'last_tsim_int_tau','double',1
    'last_err_tau','double',23
    'last_int_err_tau','double',23
    'real_theta_3_waist','double',1
    'real_omega_3_waist','double',1
    'activation_opti','double',1
    'velocity_opti','double',1
    'time_opti','double',1
    'dist_x_opti','double',1
    'velocity_opti_x_start','double',1
    'velocity_opti_started','double',1
    'dist_x_before_fall','double',1
    'waist_relative_ground','double',1
    'metabolic_energy_init','double',1
    'metabolic_energy_end','double',1
    'metabolic_energy_init_flag','int',1
    'metabolic_energy_end_flag','int',1
    'last_t_ctrl','double',1
};

simu_vars_in = {
};

simu_vars_out = {
    'Qq_out','double',23
    'tsim_out','double',1
    'q_ref','double',23
    'qd_ref','double',23
    'Qq_ref','double',23
    'imp_ctrl_index','int',23
    'stop_out','int',1
    'out1','double',10
    'out2','double',10
    'out3','double',10
    'out4','double',10
    'out5','double',10
    'fitness_opti','double',1
    'GCM_forces_right','double',6
    'GCM_forces_left','double',6
};

simu_vars_struct = {
    'cvs','Controller',1
};

end
