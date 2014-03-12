/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Main file of the code generation
 */

#include "code_generation.h"

int file_exist (char *filename)
{
	return (!access (filename, F_OK));
}

int main(int argc, char const *argv[])
{
	// -- Variables declaration -- //

	int nb_params_to_opt;

	double* params_norm;


	// -- Files definitions (along with absolute paths) -- //

	char* input_file = OPTI_PROJECT_ABS_PATH"/OptiParams/OptiParam.txt";

	char* get_real_par_file = PREPARE_OPTI_PATH"/get_real_params_to_opt.c";

	char* erase_opti_file = PREPARE_OPTI_PATH"/erase_for_opti.c";

	char* opti_def_file = PREPARE_OPTI_PATH"/opti_def.h";

	char* opti_results_file = BINARY_MAIN_BUILD_PATH"/Results/opti_result.txt";

	char* init_opti_file_ctrl = BINARY_MAIN_BUILD_PATH"/Results/init_opti_ctrl.c";

	char* init_opti_file_simu = BINARY_MAIN_BUILD_PATH"/Results/init_opti_simu.c";


	// -- Prepare the optimization -- //

	nb_params_to_opt = get_nb_params(input_file);

	generate_get_real_params(input_file, get_real_par_file);	

	generate_erase_opti(input_file, erase_opti_file);	

	generate_opti_def(opti_def_file, nb_params_to_opt, NB_OPTI_RUNS);

	
	// -- Extract the optimized results and produce the corresponding outputs -- //


	if (!file_exist(opti_results_file))
	{
		printf("\n  >> Optimization ready\n\n");
		return 0;
	}
	else
	{
		printf("\n  >> Extracting final results...\n\n");
	}

	get_norm_from_opti_results(opti_results_file);

	params_norm = get_norm_from_opti_results(opti_results_file);

	// init_opti for the controller
	generate_init_opti(input_file, init_opti_file_ctrl, params_norm, nb_params_to_opt, 1);

	// init_opti for the simulation
	generate_init_opti(input_file, init_opti_file_simu, params_norm, nb_params_to_opt, 0);

	free (params_norm);

	return 0;
}
