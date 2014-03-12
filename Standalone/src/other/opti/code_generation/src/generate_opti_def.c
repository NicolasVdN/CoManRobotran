/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Generates the header file 'opti_def.h'
 */

#include "code_generation.h"

void generate_opti_def(char* output_file, int nb_params_to_opt, int nb_optimizations)
{
	// Files declaration
    FILE* fileOut 	= NULL;

    //current time to write in output_file 
    time_t t     = time(NULL);
    struct tm tm = *localtime(&t);

    // Opening/Creating file
    fileOut = fopen(output_file, "w");

    if(fileOut == NULL)
    {
        printf("error: cannot open file '%s'\n", output_file);
    }

    //beginning of file
    fprintf(fileOut,"/*\n");
    fprintf(fileOut," * Header file used for the optimization\n");
    fprintf(fileOut," */\n\n");
    fprintf(fileOut,"// %d-%d-%d %d:%d (Date of file automatic generation)\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

    fprintf(fileOut,"#ifndef _OPTI_DEF_H_\n");
	fprintf(fileOut,"#define _OPTI_DEF_H_\n\n");

	fprintf(fileOut,"#ifdef OPTI\n\n");

	fprintf(fileOut,"#include <stdio.h>\n");
	fprintf(fileOut,"#include <stdlib.h>\n");
	fprintf(fileOut,"#include \"MBSdataStruct.h\"\n\n");

	fprintf(fileOut,"// number of parameters to optimize\n");
	fprintf(fileOut,"#define NB_PARAMS_TO_OPTIMIZE %d\n\n", nb_params_to_opt);

	fprintf(fileOut,"#define OPTI_RUNS %d\n\n", nb_optimizations);

	fprintf(fileOut,"double opti_fitness(double* optiNorms);\n");
	fprintf(fileOut,"void erase_for_opti(double *optiParams, MBSdataStruct *MBSdata);\n");
	fprintf(fileOut,"void get_real_params_to_opt(double *optiNorms, double *optiParams);\n\n");

	fprintf(fileOut,"#endif\n\n");

	fprintf(fileOut,"#endif\n\n");

    // Closing files
    fclose(fileOut);
}
