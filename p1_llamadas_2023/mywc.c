//P1-SSOO-22/23

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{ /* argv[0] = main argv[1] = directory */

	//If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
	if(argc < 2)
	{
		printf("Too few arguments\n");
		return -1;
	}

    int fd1 = -1; // File id, default -1 for error detection
    char buffer[1];
    int nread = 0;

    fd1 = open(argv[1], O_RDONLY);

    if (fd1 < 0)
    {
        printf("Error: file cannot be opened\n");
        return -1;
    }

    /* Here we have the file opened */
    int wc = 0; // word counter
    int bc = 0; // byte counter
    int lc = 0; // line counter

    while ((nread = read(fd1, buffer, 1)) > 0 )
    {
        bc++;
        if (*buffer == '\n')
            lc++;
        if (*buffer == '\n' || *buffer == '\t' || *buffer == ' ')
            wc++;
    }

    if (nread < 0)
    {
        close(fd1);
        printf("Error: Cannot read from file");
        return -1;
    }

    /* We must add a word to the word counter if the file is not empty */
    if (bc > 0)
        wc++;

    printf("%d %d %d %s\n", lc, wc, bc, argv[1]);

    close(fd1);

	return 0;
}