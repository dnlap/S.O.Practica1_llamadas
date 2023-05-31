//P1-SSOO-22/23

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int myenv(char* variable, char* outputFile)
{
    /* We open the file. Error is raised if file cant be opened */
    int inputfd, outputfd = -1;
    inputfd = open("env.txt", O_RDONLY);
    if (inputfd < 0)
    {
        printf("Error: cannot open file\n");
        return -1;
    }

    /* We create/open output file. Error is raised if file cant be created/opened */
    outputfd = creat(outputFile, 0644);
    if (outputfd < 0)
    {
        printf("Error: cannot create/open the output file\n");
        close(outputfd);
        return -1;
    }

    char buffer [1]; // A buffer of size 1 is used to read each character
    int nRead, nWrite = 0; // Number of bytes read; Number of bytes written

    /* If successful, the number of bytes actually read is returned.  Upon reading
     end-of-file, zero is returned.  Otherwise, a -1 is returned and the global
     variable errno is set to indicate the error. */

    while ((nRead = read(inputfd, buffer, 1)) > 0)
    {
        char variableName [40]; // 30 bytes are saved for variableName
        int variableP = 0; // Pointer of the variableName
        do
        {
            variableName[variableP] = *buffer;
            variableP++;
        } while((nRead = read(inputfd, buffer, 1)) > 0 && *buffer != '=');

        /* At this point, the char '=' has been reached
         * Now, variableName is compared with argv[1] = variable */

        /* The strcmp() function returns an integer greater than, equal to, or less than 0,
         * according as the string s1 is greater than, equal to, or less than the string s2 */

        int equal = strcmp(variableName, variable);
        if (equal == 0)
        {
            /* If equal */
            nWrite = write(outputfd, variableName, variableP);
            do
            {
                nWrite = write(outputfd, buffer,nRead);
                nRead = read(inputfd, buffer, 1);
            }
            while ((nRead > 0) && *buffer != '\n' && (nWrite > 0));
            nWrite = write(outputfd, buffer,nRead);
            if (nWrite < 0)
            {
                close(inputfd);
                close(outputfd);
                printf("Error: cannot write");
                return -1;
            }
            /* It keeps going as there may be more than one output */
        }
        else  // If variable not found:
        {
            memset(variableName, 0, sizeof(variableName)); // variableName is set to 0
            do
            {
                nRead = read(inputfd, buffer, 1);
            }
            while ((nRead > 0) && *buffer != '\n');
            /* Buffer keeps reWhen'\n' is found */

        }
    }

    return 0;

}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
    	printf("Too few arguments\n");
        printf("Usage: ./myenv <variableName> <outputFile>\n");
    	return -1;
    }

    char* variableName = NULL;
    char* outputFile = NULL;

    variableName = argv[1];
    outputFile = argv[2];

    int error = myenv(variableName, outputFile);
    if (error != 0)
    {
        printf("Error: Fatal\n");
        return -1;
    }
    return 0;
}
