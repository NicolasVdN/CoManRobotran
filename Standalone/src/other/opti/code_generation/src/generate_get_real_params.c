/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Genrates the 'get_real_params_to_opt' file
 */

#include "code_generation.h"

void generate_get_real_params(char* input_file, char* output_file)
{
	int i 		= 0;
	int index 	= 0;

	// Files declaration
    FILE* fileOut 	= NULL;
    FILE* fileIn 	= NULL;

    //current time to write in output_file 
    time_t t     = time(NULL);
    struct tm tm = *localtime(&t);

    const char *keys[5]; // strings for sscanf 

    //Data read in input_file
    char line[MAX_LENGTH];
    char comment[MAX_LENGTH];
    char name[MAX_LENGTH];
    int  size = 0;
    double bound_min = 0;
    double bound_max = 0; 

    keys[0] = "//%s";
    keys[1] = "NAME : %s";
    keys[2] = "ACCESS : %s";
    keys[3] = "SIZE : %d";
    keys[4] = "BOUNDS : [%lf : %lf]";

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


    //beginning of file
    fprintf(fileOut,"/*\n");
    fprintf(fileOut," * The bounded parameters in 'optiNorms' [0 ; 1]\n");
    fprintf(fileOut," * are de-bounded in 'optiParams'\n");
    fprintf(fileOut," */\n\n");
    fprintf(fileOut,"// %d-%d-%d %d:%d (Date of file automatic generation)\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

    fprintf(fileOut, 
        "#ifdef OPTI\n"
        "\n"
		"void get_real_params_to_opt(double *optiNorms, double *optiParams) \n"
		"{\n"
    	"	int i;\n"
    );

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
		
		// initialize structure
        if((sscanf(line, keys[1], &name)) == 1) 
        {
            if(fgets(line, MAX_LENGTH, fileIn) == NULL)
            {
                printf("ERROR : no line after NAME \n");
                break ;
            }

            if((fgets(line, MAX_LENGTH, fileIn) != NULL) && (sscanf(line, keys[3], &size)) == 1)  // if line after NAME is SIZE
            {
            	//Declare bounds array
            	fprintf(fileOut, "\n      double %s_bounds[%d][2]; // {min, max}\n\n", name, size);

            	//initialize bounds array
            	for(i=0; i<size; i++)
            	{
            		if((fgets(line, MAX_LENGTH, fileIn) != NULL) && (sscanf(line, keys[4], &bound_min, &bound_max) == 2)) // if lines after SIZE are BOUNDS
            		{
            			fprintf(fileOut, "      %s_bounds[%d][0]  = %lf;    %s_bounds[%d][1]  = %lf;\n", name, i, bound_min, name, i, bound_max);
            		}
            		else
            		{
                		printf("ERROR : not enough bounds \n");
                		return ;
            		} 

            	}

            	//unbound parameters
            	fprintf(fileOut,
            	    "\n"
            	    "	for(i=0; i<%d; i++) \n"
    				"	{ \n"
       				"		optiParams[i+%d] = optiNorms[i+%d]*(%s_bounds[i][1] - %s_bounds[i][0]) + %s_bounds[i][0]; \n"
    				"	} \n"
    			,size, index, index, name, name, name);

    			index = index + size;

            	fprintf(fileOut, "\n");

            }
            else 
            {
                printf("ERROR : detect a NAME but no SIZE \n");
                break ;
            }   
        } 
    }

    //end of file
    fprintf(fileOut,
    	"}\n"
		"\n"    	
		"#endif\n"
    );

    // Closing files
    fclose(fileOut);
    fclose(fileIn);
}
