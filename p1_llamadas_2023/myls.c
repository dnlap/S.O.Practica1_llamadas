//P1-SSOO-22/23

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <sys/types.h>	// Header file for system calls opendir, readdir y closedir
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int PATH_MAX = 100;

int myls(char* directory)
{
    DIR *a = opendir(directory);
    struct dirent* b = NULL;
    char* dirname;
    while ((b = readdir(a))!= NULL)
    {
        dirname = b->d_name; // dirname <- name of the directory saved in b
        printf("%s\n", dirname);
    }
    int error = closedir(a);
    if (error != 0)
    {
        printf("Error: Cannot close directory");
        return -1;
    }
    return 0;
}


int main(int argc, char *argv[])
{
    if (argc != 1 && argc != 2)
    {
        printf("Incorrect number of arguments\n");
        printf("Usage: ./myls <directory> or ./myls\n");
        return -1;
    }

    char* directory = malloc(PATH_MAX);
    if (argc == 2)
        directory = argv[1];
    else
        getcwd(directory, PATH_MAX);

    int error = myls(directory);
    if (error != 0)
    {
        printf("Error: Fatal\n");
        return -1;
    }
	return 0;
}

