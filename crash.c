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

int main(int argc, char *argv[])
{
	char  line[32];

	while(TRUE)	
	{
		// print the prompt
		printf("# ");
	
		if (fgets(line, sizeof line, stdin) != NULL)
		{
			char* cmd;
			int   arg;
			sscanf(line, "%s %d", cmd, &arg);
				
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
				printf("no such command: %s", line);
			}
		}
	}
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
