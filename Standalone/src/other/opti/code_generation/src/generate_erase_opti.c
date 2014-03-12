/*
 * authors: Timothee Habra and Nicolas Van der Noot
 * 
 * Genrates the 'erase_for_opti' file
 */

#include "code_generation.h"

void generate_erase_opti(char* input_file, char* output_file)
{
	// Files declaration
    FILE* fileOut 	= NULL;
    FILE* fileIn 	= NULL;

    //current time to write in output_file 
    time_t t     = time(NULL);
    struct tm tm = *localtime(&t);

    int nb_printed = 0;

    const char *keys[5]; // strings for sscanf 

    //Data read in input_file
    char line[MAX_LENGTH];
    char comment[MAX_LENGTH];
    char name[MAX_LENGTH];
    char access[MAX_LENGTH];
    int  size = 0;

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
    fprintf(fileOut," * Erase and replace the hard-coded values of the simulation\n");
    fprintf(fileOut," * by the ones coming from the optimization algorithm'\n");
    fprintf(fileOut," */\n\n");
    fprintf(fileOut,"// %d-%d-%d %d:%d (Date of file automatic generation)\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

    fprintf(fileOut, 
        "#ifdef OPTI\n"
        "\n"
		"#include \"opti_def.h\"\n"
		"\n"
		"void erase_for_opti(double *optiParams, MBSdataStruct *MBSdata) \n"
		"{\n"
    	"    int i;\n\n"
        "    UserIOStruct *uvs;\n"
        "    ControllerStruct *cvs;\n\n"
        "    uvs = MBSdata->user_IO;\n"
        "    cvs = uvs->cvs;\n\n"  
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
            fprintf(fileOut, "    %s", line);
        }
		
		// initialize structure
        if((sscanf(line, keys[1], &name)) == 1) 
        {
            if((fgets(line, MAX_LENGTH, fileIn) != NULL) && (sscanf(line, keys[2], &access)) == 1)  // if line after NAME is SIZE
            {
                if((fgets(line, MAX_LENGTH, fileIn) != NULL) && (sscanf(line, keys[3], &size)) == 1)  // if line after NAME is SIZE
                {
                	if (size < 1)
                    {
                        printf("ERROR : size is less than 1 \n");
                        break ;
                    }
                    else
                    {
                        if (size == 1)
                        {
                            fprintf(fileOut, "    %s->%s = optiParams[%d];\n", access, name, nb_printed);
                        }
                        else
                        {
                            fprintf(fileOut, "    for (i=0; i<%d; i++)\n", size);
                            fprintf(fileOut, "    {\n");
                            fprintf(fileOut, "        %s->%s[i] = optiParams[%d+i];\n", access, name, nb_printed);
                            fprintf(fileOut, "    }\n");
                        }

                        fprintf(fileOut, "\n");

                        nb_printed += size;
                    }
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
    fprintf(fileOut,
    	"}\n"
		"\n"    	
		"#endif\n"
    );

    // Closing files
    fclose(fileOut);
    fclose(fileIn);
}
