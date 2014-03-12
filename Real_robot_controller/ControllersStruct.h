//---------------------------
// Nicolas Van der Noot
//
// Creation : 19-Sep-2013
// Last update : Tue Mar 11 16:48:31 2014
//---------------------------

#ifndef ControllerStruct_h
#define ControllerStruct_h


// ---- Structures definitions (typedef) ---- //

// ControllerInputsStruc
typedef struct ControllerInputsStruct
{
    double t;
    double q[23];
    double qd[23];
    double Qq[23];
    double F_Rfoot[3];
    double F_Lfoot[3];
    double T_Rfoot[3];
    double T_Lfoot[3];
    double IMU_Orientation[9];
    double IMU_Angular_Rate[3];

} ControllerInputsStruct;


// ControllerOutputsStruc
typedef struct ControllerOutputsStruct
{
    double q_ref[23];
    double qd_ref[23];
    double Qq_ref[23];
    int imp_ctrl_index[23];

} ControllerOutputsStruct;


// ControllerStruc
typedef struct ControllerStruct
{
    double out1[10];
    double out2[10];
    double interact;
    double test_opti;
    ControllerOutputsStruct *Outputs;
    ControllerInputsStruct *Inputs;

} ControllerStruct;


// ---- Init and free functions: declarations ---- //

ControllerInputsStruct * init_ControllerInputsStruct(void);
void free_ControllerInputsStruct(ControllerInputsStruct *cvs);

ControllerOutputsStruct * init_ControllerOutputsStruct(void);
void free_ControllerOutputsStruct(ControllerOutputsStruct *cvs);

ControllerStruct * init_ControllerStruct(void);
void free_ControllerStruct(ControllerStruct *cvs);

/*--------------------*/
#endif

