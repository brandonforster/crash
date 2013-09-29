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

	// copy the args from the buffer, skipping over cmd's term character
	*args= malloc((lineLen-cmdLen));
	strcpy(*args, &buffer[(cmdLen+1)]);

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
