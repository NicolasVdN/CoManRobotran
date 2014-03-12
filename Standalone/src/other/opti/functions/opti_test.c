
#if defined(OPTI)

#include "main_simulation.h"
#include "opti_def.h"

int main(int argc, char const *argv[])
{
	int i;

	#ifdef PRINT_REPORT
	double fitness;
	#endif

	double *optiNorms;

	optiNorms = (double*) malloc(NB_PARAMS_TO_OPTIMIZE*sizeof(double));

	for (i=0; i<NB_PARAMS_TO_OPTIMIZE; i++)
	{
		optiNorms[i] = 0.5;
	}

	#ifdef PRINT_REPORT
	fitness = opti_fitness(optiNorms);
	#else
	opti_fitness(optiNorms);
	#endif

	#ifdef PRINT_REPORT
	printf("fitness: %f\n", fitness);
	#endif
	
	free(optiNorms);

	return 0;
}

#endif
