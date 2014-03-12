/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Header file of the functions related to the code generation
 */

#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_

// -- Include headers -- //

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "cmake_config_opti.h"
#include "cmake_config.h"

// -- Macros -- //

// string max length
#define MAX_LENGTH 500

// optimization parameters
#define NB_PARTICLES   200
#define NB_GENERATIONS 100
#define NB_OPTI_RUNS   3

// files paths
#define BINARY_MAIN_BUILD_PATH BINARY_ABS_PATH
#define PREPARE_OPTI_PATH OPTI_PROJECT_ABS_PATH"/../functions/automatic_generation"


// -- Functions prototypes -- //

int get_nb_params(char* input_file);
int get_nb_cvs_uvs_params(char* input_file, int cvs_flag);
void generate_biorob_xml(char* output_file, int nb_params_to_opt, int priority, int nb_iter, int population_size, char *token, char *dispatcher);
void generate_get_real_params(char* input_file, char* output_file);
void generate_erase_opti(char* input_file, char* output_file);
void generate_opti_def(char* output_file, int nb_params_to_opt, int nb_optimizations);
void generate_init_opti(char* input_file, char* output_file, double* params_norm, int nb_params_to_opt, int ctrl_flag);
void generate_opti_results(char* output_file, double* params_norm, double fitness, int nb_params, int nb_gen, int nb_particles, char* algo);
double* get_norm_from_opti_results(char *opti_results_file);
int file_exist (char *filename);


#endif 
