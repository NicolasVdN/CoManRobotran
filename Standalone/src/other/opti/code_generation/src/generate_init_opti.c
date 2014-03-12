/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Generates the 'opti_parameters_init_controller' file
 */

#include "code_generation.h"

// function prototype
void get_real_params_to_opt(double *optiNorms, double *optiParams);

void generate_init_opti(char* input_file, char* output_file, double* params_norm, int nb_params_to_opt, int ctrl_flag)
{

    double *real_params;
    int i_param;
    int i;
    int cvs_diff;

    //current time to write in output_file 
    time_t t     = time(NULL);
    struct tm tm = *localtime(&t);

    //Data read in input_file
    char line[MAX_LENGTH];
    char comment[MAX_LENGTH];
    char name[MAX_LENGTH];
    char access[MAX_LENGTH];
    int  size = 0; 

    int declaration_flag;

    const char *keys[4]; // strings for sscanf 

    real_params = (double*) malloc(nb_params_to_opt*sizeof(double));

    // -- Files declaration -- //
    FILE* fileOut = NULL;
    FILE* fileIn = NULL;

    keys[0] = "//%s";
    keys[1] = "NAME : %s";
    keys[2] = "ACCESS : %s";
    keys[3] = "SIZE : %d"; 

	if (get_nb_cvs_uvs_params(input_file, ctrl_flag))
	{
		declaration_flag = 1;
	}
	else
	{
		declaration_flag = 0;
	}
  
    get_real_params_to_opt(params_norm, real_params);

    // Opening/Creating file
    fileOut = fopen(output_file, "w");
    if(fileOut == NULL)
    {
        printf("error: cannot open file '%s'\n", output_file);
    }

    fileIn = fopen(input_file, "r");
    if(fileIn == NULL)
    {
        printf("error: cannot open file '%s'\n", input_file);
    }       

	// -- Writing file -- //

    //beginning of file
    fprintf(fileOut,"// %d-%d-%d %d:%d (Date of file automatic generation)\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

	fprintf(fileOut, 
        "//---------------------------\n"
        "//\n"
        "// Nicolas Van der Noot & Timothee Habra\n"
        "//\n"
        "// Creation : 01/11/2013\n"
        "// Last update : 07/03/2014\n"
        "//\n");

    if (ctrl_flag)
    {
        fprintf(fileOut, 
            "// Initialize the optimization parameters for the controller\n"
            "//\n"
            "//---------------------------\n"
            "\n"       
            "#include \"controller_def.h\" \n"
            "\n"
            "// Initializes optimized controller parameters\n"
            "void opti_parameters_init_controller(ControllerStruct *cvs)\n"
            "{\n"
        );
    }
    else
    {
        fprintf(fileOut, 
            "// Initialize the optimization parameters for the simulation\n"
            "//\n"
            "//---------------------------\n"
            "\n"       
            "#include \"MBSdataStruct.h\" \n"
            "\n"
            "// Initializes optimized simulation parameters\n"
            "void opti_parameters_init_simu(MBSdataStruct *MBSdata)\n"
            "{\n"
        );

        if (declaration_flag)
        {
        	fprintf(fileOut, 
	            "\n      UserIOStruct *uvs;\n\n"
	            "      uvs = MBSdata->user_IO;\n\n"
	        );
        }
    } 

    i_param = 0;

    //core of file
    while(fgets(line, MAX_LENGTH, fileIn) != NULL) // Read input_file
    {
        if (line[0] == '#')
        {
            continue; // skip line
        }   

        if((sscanf(line, keys[0], &comment)) == 1) // write comment
        {
            fprintf(fileOut, "      %s", line);
        } 

        if((sscanf(line, keys[1], &name)) == 1) // initialize structure
        {
            if((fgets(line, MAX_LENGTH, fileIn) != NULL) && (sscanf(line, keys[2], &access)) == 1)  // if line after NAME is SIZE
            {

                cvs_diff = strncmp(access, "cvs", 3);

                if ( (ctrl_flag && cvs_diff) || ((!ctrl_flag) && (!cvs_diff)) )
                {
                    continue; // skip line
                }


                if((fgets(line, MAX_LENGTH, fileIn) != NULL) && (sscanf(line, keys[3], &size)) == 1)  // if line after NAME is SIZE
                {
                    if(size == 1) 
                    {
                        fprintf(fileOut, "      %s->%s = %f; \n", access, name, real_params[i_param]);
                        i_param++;
                    }
                    else if(size > 1)
                    {
                        for(i=0; i<size; i++)
                        {
                            fprintf(fileOut, "      %s->%s[%d] = %f; \n", access, name, i, real_params[i_param]);
                            i_param++;
                        }
                    }
                    else 
                    {
                        printf("ERROR : detect a SIZE < 1 \n");
                        break ;
                    }

                    fprintf(fileOut, "\n");
                }
                else 
                {
                    printf("ERROR : detect a NAME and ACCESS but no SIZE \n");
                    break ;
                }   
            }
            else 
            {
                printf("ERROR : detect a NAME but no ACCESS \n");
                break ;
            }                   
        } 
    }

   //end of file
    fprintf(fileOut,"}\n\n");

    // Closing files
    fclose(fileOut);
    fclose(fileIn);

    free(real_params);
}
