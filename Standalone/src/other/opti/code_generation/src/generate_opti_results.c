/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Generates the 'opti_result.txt' file
 */

#include "code_generation.h"

void generate_opti_results(char* output_file, double* params_norm, double fitness, int nb_params, int nb_gen, int nb_particles, char* algo)
{

    int i = 0;
    
    // File declaration
    char * fileName = output_file; 
    FILE* fileOut   = NULL;

    //current time to write in output_file 
    time_t t     = time(NULL);
    struct tm tm = *localtime(&t);

    // Creating file
    fileOut = fopen(fileName, "w");
    if(fileOut == NULL)
    {
        printf("error: cannot create file '%s'\n", fileName);
    }


    // Writing file

    fprintf(fileOut,"// %d-%d-%d %d:%d (Date of file automatic generation)\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
    
    fprintf(fileOut, 
        "\nOPTIMIZATION USED : \n"
        "------------------------------\n"
        "Nb params      : %d \n"
        "Nb particles   : %d \n"
        "Nb generations : %d \n"
        "Algorithm      : %s \n"
        ,nb_params, nb_particles, nb_gen, algo
    );


    fprintf(fileOut, 
        "\nOPTIMIZATION RESULTS : \n"
        "------------------------------\n"
        "fitness              : %g \n"
        "function evaluations : %d \n"
        , fitness, nb_particles*nb_gen
    );


    fprintf(fileOut,"\n");

    for(i=0; i<nb_params; i++)
    {
        fprintf(fileOut, "%f\n", params_norm[i]);
    }

    // Closing files
    fclose(fileOut);
}

/*
 * Returns the vector of normalized optimized parameters
 */
double* get_norm_from_opti_results(char *opti_results_file)
{
	int nb_params;
	int i;

	double* params_norm;
	double cur_value;

	char line[MAX_LENGTH];

	// Files declaration
    FILE* fileIn 	= NULL;

    fileIn = fopen(opti_results_file, "r");

    if(fileIn == NULL)
    {
        printf("error: cannot open file '%s'\n", opti_results_file);
    } 

	while(fgets(line, MAX_LENGTH, fileIn) != NULL) // Read input_file
	{
		if((sscanf(line, "Nb params      : %d", &nb_params)) == 1) 
        {
        	break;
        }
	}

	params_norm = (double*) malloc(nb_params*sizeof(double));

	for(i=0; i<nb_params; i++)
	{
		params_norm[i] = 0.0;
	}

	rewind(fileIn);

	i = 0;

	while(fgets(line, MAX_LENGTH, fileIn) != NULL) // Read input_file
	{
		if((sscanf(line, "%lf", &cur_value)) == 1) 
        {
        	params_norm[i] = cur_value;
        	i++;
        }
	}

	// Closing files
    fclose(fileIn);

	return params_norm;
}
