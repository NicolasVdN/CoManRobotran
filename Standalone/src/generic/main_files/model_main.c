
/*
 * Top-level function of the model.
 * 1. initialization
 * 2. loop
 * 3. end of the simulation
 *
 * author: Nicolas Van der Noot
 */

#ifndef CXX

#include "main_simulation.h"

#ifdef OPTI
#include "opti_def.h"
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
