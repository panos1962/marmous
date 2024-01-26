#include <stdio.h>      // printf, scanf...
#include <stdlib.h>     // exit...
#include <unistd.h>     // contains execvp
#include <sys/types.h>  // gid_t, pid_t...
#include <sys/wait.h>   // wait ...
#include <unistd.h>     // contains execvp
#include <fcntl.h>      // wait
#include <stdbool.h>    // true - false
#include <string.h>
#define SIZE 2048
#define MAX 16

int main(void)
{
    // i entoli mpainei sto buffer kai xorizetai se entoli (command) kai ouput file
    char buffer[SIZE];
    char *infile;
    char *outfile;
    char *argv[MAX];
    char *command[MAX];     // * giati oi pinakes periexoun dieuthinseis pou periexoyn entoles
    bool trunk = false;
    bool append = false;
    bool input_file = false;

    printf("------Type 'quit' to exit OurShell------\n");
    while (true)
    {
        printf("Our_Shell$ : ");

        memset(buffer, 0, SIZE);
        fgets(buffer, SIZE, stdin);
        buffer[strlen(buffer) -1] = '\0';

        if (strcmp(buffer, "quit") == 0)
        {
            break;
        }

        int counter = 0;
        argv[counter] = strtok(buffer, " ");
        while (argv[counter] != NULL)
        {
            counter++;
            argv[counter] = strtok(NULL, " ");
        }

        int i=0;
        while (i<counter)
        {
            if (strcmp(argv[i], ">") ==0)   // trunk = true - kanei overwrite sto txt
            {
                command[i]=NULL;
                trunk = true;
                append = false;
                input_file = false;
                if (argv[i+2] != NULL)
                {
                    if (strcmp(argv[i+2], "<") ==0)
                    {   command[i]=NULL;
                        trunk =true;
                        append = false;
                        input_file = true;
                        break;
                    }
                    break;
                }
                break;
            }
            else if (strcmp(argv[i], "<") ==0)      // stin periptosi pou exw input file
            {
                command[i]=NULL;
                trunk = false;
                append = false;
                input_file = true;
                if (argv[i+2] != NULL)
                {
                    if (strcmp(argv[i+2], ">") ==0)
                    {   command[i]=NULL;
                        trunk =true;
                        append = false;
                        input_file = true;
                        break;
                    }
                    else if (strcmp(argv[i+2], ">>") ==0)
                    {   command[i]=NULL;
                        trunk =false;
                        append = true;
                        input_file = true;
                        break;
                    }
                    break;
                }
                break;
            }
            else if (strcmp(argv[i], ">>") ==0)     // append = true - grafei kato apo to yparxon txt
            {
                command[i]=NULL;
                trunk = false;
                append = true;
                input_file = false;
                if (argv[i+2] != NULL)
                {
                    if (strcmp(argv[i+2], "<") ==0)
                    {   command[i]=NULL;
                        trunk =false;
                        append = true;
                        input_file = true;
                        break;
                    }
                    break;
                }
                break;
            }
            else
            {
                command[i] = argv[i];       // sygkrinei deiktes
                i=i+1;
            }
        }
        if (trunk == true || append == true)    // if trunkade or append is true
        {
            outfile = argv[i+1];                // to outut file is in the next position
            if (strcmp(argv[i+2], "<") ==0)
                infile = argv[i+3];
                printf("Input file is %s\n", infile);
        }
        else if (input_file == true)            // if input_file is true
        {
            infile = argv[i+1];                 // the input file is in the next position
            if ((strcmp(argv[i+2], ">") ==0) || (strcmp(argv[i+2], ">>") ==0))
                outfile = argv[i+3];
                printf("Output file is %s\n", outfile);
        }
        else
        {
            command[i] = NULL;
        }

        pid_t newgen = fork();
        if (newgen == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if (newgen == 0)       // newgen code
        {
            int fd;
            if (trunk == true)
            {
                fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
                dup2(fd, 1);        // redirection sto output file
            }
            else if (append == true)
            {
                fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0777);
                dup2(fd, 1);        // redirection sto output file
            }
            else if (input_file == true)
            {
                fd = open(infile, O_RDONLY);        // To arxeio prepei na yparxei
                dup2(fd, 0);        // input redirection            
            }
            execvp(command[0], command);
            perror("execvp failed to operate\n");
            exit(EXIT_FAILURE);
        }
        else if (newgen >0)
        {
            wait(NULL);
        }
    }
    exit(EXIT_SUCCESS);
}
