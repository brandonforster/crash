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
#include <stdint.h> // allows intmax_t as recommended by
                    // http://stackoverflow.com/questions/7600304/how-to-add-a-pid-t-to-a-string-in-c

#define TRUE 1
#define FALSE 0

#define LINE_SIZE 512
#define ARG_SIZE 32

int main()
{
	// declare our strings for the two parts of input
	char* cmd= NULL;
	char* args[ARG_SIZE]= {NULL};

	int i= 0;

	while(TRUE)	
	{
		// print the prompt
		printf("# ");
	
		if (getUserCommand(&cmd, &args) != 0)
		{
			if (strcmp(cmd, "quit") == 0)
			{
				free(cmd);
				for (i= 0; i< ARG_SIZE; i++)	
					free(args[i]);

				exit(0);
			}

			else if (strcmp(cmd, "run") == 0)
			{
				runRun(args);
			}
	
			else if (strcmp(cmd, "background") == 0)
			{
				pid_t pid;
				pid= runBackground(args);
				if (pid > 0)
					printf("process backgrounded, id is: %jd\n",(intmax_t) pid);
				else
					printf("error: process not backgrounded\n");
			}
	
			else if (strcmp(cmd, "murder") == 0)
			{
				runMurder(args);
			}

			else if (strcmp(cmd, "for") == 0)
			{
				runFor(args);
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
	int lineLen= (i- 1);
	buffer[lineLen]='\0';
	
	i= 0;

	// find the first space, whatever's here is our cmd
	while (i < lineLen)
	{
		if ((buffer[i] == ' ') || (buffer[i] == '\n'))
			break;

		i++;
	}

	int cmdLen = i;
	
	// add a term character for cmd and copy cmd from buffer
	*cmd= malloc(cmdLen);
	buffer[cmdLen]= '\0';
	strcpy(*cmd, buffer);
	// there are no args
	if (cmdLen == lineLen)
		return 1;

	// increment i so it's at stringStart
	i++;

	// copy the args from the buffer, skipping over cmd's term character
	// find the first space, whatever's here is nex arg
	int j= 0;
	int stringStart= (cmdLen+ 1);
	while(i<= lineLen)
	{
		if ((buffer[i] == ' ') || (buffer[i] == '\n') || (buffer[i]== '\0'))
		{
			// put a term where we found this space
			args[j]= malloc(((i- stringStart)+1));
			buffer[i]= '\0';
			strcpy(args[j], &buffer[stringStart]);
			j++;
			stringStart= i+1;
		}
		i++;
	}

	// make sure we actually did something
	if ((*cmd == NULL) && (*args == NULL))
		return 0;
	else
		return 1;
}

int runRun(char** args)
{
	pid_t pid;
	int status;

	// fork the process
	pid= fork();
	
	// check for failure. main will handle the error
	if (pid < 0)
		return 0;

	// for the child
	else if (pid == 0)
	{
		// if execution doesn't return an error call
		if (execvp(*args, args) < 0)
			return 0;
	}

	// for the parent
	else
	{
		// hurry up and wait
		while (wait(&status) != pid);
	}
}

pid_t runBackground(char** args)
{
	pid_t pid;

	// fork the process
	pid= fork();
	
	// check for failure. main will handle the error
	if (pid < 0)
		return 0;

	// for the child
	else if (pid == 0)
	{
		// if the execution call doesn't return an error code
		if (execvp(*args, args) < 0)
			return 0;
	}

	return pid;
}

int runMurder(char** args)
{
	if (args[0] == NULL)	
	{
		printf("you need an argument to murder\n");		
		return 0;
	}

	pid_t target;
	if (sscanf(args[0], "%d", &target) == EOF)
	{
		printf("%s is not a valid argument to murder\n",args[0]);
		return 0;
	}
	else
	{
		if (kill(target, SIGKILL) == 0)
		{
			printf("it is done. %s is dead.\n", args[0]);
			return 1;
		}
		else
		{
			printf("there were... complications. %s is not dead.\n", args[0]);
			return 0;
		}
	}
}

int runFor(char** args)
{
	if (args[0] == NULL)
	{
		printf("you need an initializer for your for loop\n");		
		return 0;
	}
	
	if (args[1] == NULL)
	{
		printf("you need a limit for your for loop\n");		
		return 0;
	}
		
	if (args[2] == NULL)
	{
		printf("you need an increment for your for loop\n");		
		return 0;
	}

	int init= 0;
	int limit= 0;
	int inc= 0;

	if (sscanf(args[0], "%d", &init) == EOF)
	{
		printf("%s is not a valid initializer\n",args[0]);
		return 0;
	}
	
	if (sscanf(args[1], "%d", &limit) == EOF)
	{
		printf("%s is not a valid limit\n",args[1]);
		return 0;
	}

	if (sscanf(args[2], "%d", &inc) == EOF)
	{
		printf("%s is not a valid increment\n",args[2]);
		return 0;
	}

	int i= 0;
	if (inc == 0)
	{
		printf("infinite loop detected, aborting...\n");
		return 0;
	}

	else
	{	
		// copy the run command into 2 so we can store i in 3
		strcpy(args[2], args[3]);

		// counting up for loop
		if (init < limit)
		{
			for (i= init; i< limit; i+= inc)
			{
				sprintf(args[3], "%d", i);
				runRun(&args[2]);
			}
		}

		// counting down for loop
		else if (init > limit)
		{
			for (i= init; i> limit; i+= inc)
			{
				sprintf(args[3], "%d", i);
				runRun(&args[2]);
			}
		}
	}	
	return 1;
}

