// Brandon Forster
// COP 4600- Operating Systems
// Homework 1- Unix Terminal
// 1 October 2013
// crash.c
// A crappy bash shell.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/signal.h>

#define TRUE 1
#define FALSE 0

#define LINE_SIZE 512
#define ARG_SIZE 32

int main()
{
	// declare our strings for the two parts of input
	char* cmd= NULL;
	char* args[ARG_SIZE];

	int i= 0;
	for (i= 0; i< ARG_SIZE; i++)
		args[i]= NULL;
	
	while(TRUE)	
	{
		// print the prompt
		printf("# ");
	
		if (getUserCommand(&cmd, &args) != 0)
		{
			if (strcmp(cmd, "quit") == 0)
			{
				runQuit();
			}

			else if (strcmp(cmd, "run") == 0)
			{
				runRun(args);
			}
	
			else if (strcmp(cmd, "background") == 0)
			{
				runBackground(args);
			}
	
			else if (strcmp(cmd, "murder") == 0)
			{
				if (args[0] == NULL)
				{
					printf("you need an argument to murder\n");
					continue;
				}

				pid_t target;
				if (sscanf(args[0], "%d", &target) == EOF)
				{
					printf("%s is not a valid argument to murder\n",args[0]);
					continue;
				}
				else
				{
					if (kill(target, SIGKILL) == 0)
						printf("it is done. %s is dead.\n", args[0]);
					else
						printf("there were... complications. %s is not dead.\n", args[0]);
				}
			}

			else
			{
				printf("no such command: %s\n", cmd);
			}
		}
		free(cmd);
		for (i= 0; i< ARG_SIZE; i++)
			free(args[i]);
	}
}

int getUserCommand(char** cmd, char** args)
{
	char c= '\0';
	int  i= 0;
	char buffer[LINE_SIZE];

	// read characters into a buffer until EOF
	do
	{
		c= getchar();
		buffer[i]= c;
		i++;
	}while ((c != EOF) && (c != '\n'));

	// add term char
	int lineLen= i;
	buffer[lineLen]='\0';
	
	// find the first space, whatever's here is our cmd
	for (i= 0; i< lineLen; i++)
	{
		if ((buffer[i] == ' ') || (buffer[i] == '\n'))
			break;
	}

	int cmdLen = i;
	
	// add a term character for cmd and copy cmd from buffer
	*cmd= malloc(cmdLen);
	buffer[cmdLen]= '\0';
	strcpy(*cmd, buffer);
	// there are no args
	if (cmdLen == lineLen)
		return 1;

	// copy the args from the buffer, skipping over cmd's term character
	// find the first space, whatever's here is nex arg
	int j= 0;
	int stringStart= (cmdLen+ 1);
	for (i= cmdLen; i< lineLen; i++)
	{
		if ((buffer[i] == ' ') || (buffer[i] == '\n'))
		{
			// put a term where we found this space
			args[j]= malloc(((i- stringStart)+1));
			buffer[i]= '\0';
			strcpy(args[j], &buffer[stringStart]);
			j++;
			stringStart= i+1;
		}
	}

	// make sure we actually did something
	if ((*cmd == NULL) && (*args == NULL))
		return 0;
	else
		return 1;
}

int runQuit()
{
	exit(0);
	return 0;
}

int runRun(char** args)
{
	return 0;
}

int runBackground(char** args)
{
	return 0;
}

