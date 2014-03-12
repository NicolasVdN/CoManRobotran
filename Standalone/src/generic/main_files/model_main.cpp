
/*
 * Top-level function of the model.
 * 1. initialization
 * 2. loop
 * 3. end of the simulation
 *
 * author: Nicolas Van der Noot
 */

#ifdef CXX

extern "C" 
{
    #include "main_simulation.h"

    #ifdef OPTI
    #include "opti_def.h"
    #endif
}

#ifdef SIMBODY
#include "simbody_cpp_functions.hpp"
#endif

#ifdef SIMBODY
SimbodyVariables *p_simbodyVariables;
#endif


/*
 * Main function
 */
#ifndef OPTI

int main(int argc, char const *argv[])
{
    main_simulation();
    
    return 0;
}
#endif

/*
 * Main loop
 */
#ifdef OPTI
double model_eval(double *optiNorms)
#else
void main_simulation()
#endif
{
    // inputs
    double fitness;

    #ifdef OPTI
    double *optiParams;
    #endif

    Loop_inputs *loop_inputs;

    // initialization
	loop_inputs = init_simulation();

    // optimization init
    #ifdef OPTI

    optiParams = (double*) malloc(NB_PARAMS_TO_OPTIMIZE*sizeof(double));

    get_real_params_to_opt(optiNorms, optiParams);

    erase_for_opti(optiParams, loop_inputs->MBSdata);

    free(optiParams);

    #endif
    
    // -- Simbody -- //

    #ifdef SIMBODY

    // / Create the system. Define all "system" objects - system, matterm forces, tracker, contactForces.
    MultibodySystem           system;
    SimbodyMatterSubsystem    matter(system);
    ContactTrackerSubsystem   tracker(system); 
    CompliantContactSubsystem contactForces(system, tracker);
    system.setUpDirection(+ZAxis); // that is for visualization only. The default direction is +X


    SimbodyVariables simbodyVariables;

    // set all the mechanical parameters of the contact
    
    simbodyVariables.p_system        = &system;
    simbodyVariables.p_matter        = &matter;
    simbodyVariables.p_tracker       = &tracker;
    simbodyVariables.p_contactForces = &contactForces;

    //  cout<<"BoxInd in Main = "<<BoxInd<<" -- should be default \n";
    
    //init_Simbody(&simbodyVariables);

    init_Simbody(&simbodyVariables, loop_inputs->MBSdata->user_IO->simbodyBodies);
    
    //it is "system" commands. We cannot avoid them.    
    system.realizeTopology();
    State state = system.getDefaultState();

    simbodyVariables.p_state = &state;

    //it is "system" command. We cannot avoid them. 
    system.realizeModel(state);

    p_simbodyVariables = &simbodyVariables;

    #endif

	// loop
    fitness = loop_simulation(loop_inputs);

    // end of the simulation
    finish_simulation(loop_inputs);

    #ifdef OPTI

    return fitness;

    #else

    #if defined(PRINT_REPORT)
    printf("fitness: %f\n", fitness);
    #endif

    #endif
}


#endif

