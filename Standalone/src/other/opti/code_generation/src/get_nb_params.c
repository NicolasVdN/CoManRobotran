/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Returns the number of optimized parameters from a 'OptiParam.txt' file
 */

#include "code_generation.h"

int get_nb_params(char* input_file)
{
	// File declaration
    FILE* fileIn = NULL;

    const char *key_size;

    //Data read in input_file
    char line[MAX_LENGTH];

    // count
    int cur_nb_var;
    int total_nb_var;

    key_size = "SIZE : %d";

    // open the input file
    fileIn = fopen(input_file, "r");
    if(fileIn == NULL)
    {
        printf("error: cannot open file '%s'\n", input_file);
    } 

    total_nb_var = 0;

    while(fgets(line, MAX_LENGTH, fileIn) != NULL) // Read input_file
    {
    	if (line[0] == '#') 
    	{
    		continue; // skip line
    	}
    	
    	if((sscanf(line, key_size, &cur_nb_var)) == 1) // write comment
        {
            total_nb_var += cur_nb_var;
        }
    }

    fclose(fileIn);

    return total_nb_var;
}

/*
 * Number of parameters accessed via ControllerStruct *cvs or UserIOStruct *uvs
 */
int get_nb_cvs_uvs_params(char* input_file, int cvs_flag)
{
    // File declaration
    FILE* fileIn = NULL;

    const char *key_size, *key_access;

    //Data read in input_file
    char line[MAX_LENGTH];
    char access[MAX_LENGTH];

    // count
    int cur_nb_var;
    int total_nb_var;

    int cvs_diff;
    int uvs_diff;
    int good_access;

    key_size   = "SIZE : %d";
    key_access = "ACCESS : %s";

    // open the input file
    fileIn = fopen(input_file, "r");
    if(fileIn == NULL)
    {
        printf("error: cannot open file '%s'\n", input_file);
    } 

    total_nb_var = 0;

    good_access = 0;

    while(fgets(line, MAX_LENGTH, fileIn) != NULL) // Read input_file
    {
        if (line[0] == '#') 
        {
            continue; // skip line
        }

        if((sscanf(line, key_access, &access)) == 1) // write comment
        {
            cvs_diff = strncmp(access, "cvs", 3);
            uvs_diff = strncmp(access, "uvs", 3);

            if ( (cvs_flag && cvs_diff) || ((!cvs_flag) && uvs_diff) ) // not taken into account
            {
                good_access = 0;
            }
            else
            {
                good_access = 1;
            }
        }

        if(good_access && ((sscanf(line, key_size, &cur_nb_var)) == 1)) // write comment
        {
            total_nb_var += cur_nb_var;
        }
    }

    fclose(fileIn);

    return total_nb_var;
}