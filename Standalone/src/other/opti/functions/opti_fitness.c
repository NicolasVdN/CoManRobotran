
#ifdef OPTI

#include "opti_def.h"
#include "useful_functions.h"
#include "main_simulation.h"

double opti_fitness(double* optiNorms)
{
	double cur_fitness;
    double mean_fitness;
    int i;
    
    mean_fitness = 0.0;
    
    // Runs the model
    for (i=0; i<OPTI_RUNS; i++)
    {
        cur_fitness = model_eval(optiNorms);
        mean_fitness += cur_fitness;
    }

    mean_fitness = mean_fitness / OPTI_RUNS;
    
    return mean_fitness;
}

#endif
