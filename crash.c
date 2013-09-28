// Brandon Forster
// COP 4600- Operating Systems
// Homework 1- Unix Terminal
// 1 October 2013
// crash.c
// A crappy bash shell.

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define LINE_SIZE 256

int main()
{
	while(TRUE)	
	{
		// print the prompt
		printf("# ");
	
		// declare our strings for the two parts of input
		char* cmd= NULL;
		char* args= NULL;
	
		if (getUserCommand(&cmd, &args) != NULL)
		{
			printf("cmd is %s\n",cmd);	
			printf("args is %s\n",args);

			if (strcmp(cmd, "quit") == 0)
			{
				runQuit();
			}

			else if (strcmp(cmd, "run") == 0)
			{
				runRun();
			}
	
			else if (strcmp(cmd, "background") == 0)
			{
				runBackground();
			}
	
			else if (strcmp(cmd, "murder") == 0)
			{
				runMurder();
			}

			else
			{
				printf("no such command: %s", cmd);
			}
		}
		free(cmd);
		free(args);
	}
}

int getUserCommand(char** cmd, char** args)
{
	int retVal= NULL;

	char c= '\0';
	int  i= 0;
	char buffer[LINE_SIZE];

	// read characters until a space or EOF to get the cmd
	do
	{
		c= getchar();
		buffer[i]= c;
		i++;
	}while ((c != ' ') || (c != EOF));
	
	// format what's in buffer to form cmd
	buffer[(i+1)]= '\0'

	//copy buffer into cmd
	*cmd= malloc((i+1));
	*cmd= &buffer;
	
	// store how big c is
	int cmdLen= i; 
	
	// do the same for args, this time read everything until EOF
	do
	{
		c= getchar();
		buffer[i]= c;
		i++;
	}while (c != EOF);

	// format what's in buffer to form args 
	buffer[(i+1)]= '\0'

	//copy buffer into cmd
	*args= malloc(((i+1)-cmdLen));
	*args= &buffer[cmdLen];

	retVal = 1;

	return retVal;
}

int runQuit()
{
	exit(0);
	return 0;
}

int runRun(char* command)
{
	return 0;
}

int runBackground(char* command)
{
	return 0;
}

int runMurder(int pid)
{
	return 0;
}
