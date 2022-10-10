#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "header.h"

extern int varcount ;
extern variable vararr[100];
extern int out, in, err, stdi, stde, stdo;




int main()
{
    stdo = fileno(stdout);
    stdi = fileno(stdin) ;
	
	
    while (1) {
		
		
		
		char buffer[100];
		
		green ();
		printf("my amazing shell >> ");
		reset ();
	
		fgets(buffer, 100, stdin);
		
		
		if (buffer[0] == '\n')
			continue;
		
		
		buffer[strlen(buffer) - 1] = '\0';
		
		
		char line[strlen(buffer)];
		strcpy   (line, buffer);
		
		char *sentence[simicount(buffer)];
		
		char *sentenceDivider  = strtok(line, ";");
		
		int  sentencesCounter  = 0;
		
		while (sentenceDivider != NULL) 
		{
			
			sentence[sentencesCounter] = (char *) malloc(strlen(sentenceDivider) * sizeof(char));
			strcpy                       (sentence[sentencesCounter], sentenceDivider);
			sentenceDivider            = strtok(NULL,";");
			sentencesCounter++;
		
		}
		
		
		
		for (int sentenceIterator = 0; sentenceIterator < sentencesCounter; sentenceIterator++)
		{
				
			char tmp[strlen(sentence[sentenceIterator])];
			strcpy  (tmp,   sentence[sentenceIterator]) ;
			int  pipeFlag = ispipe(tmp);
			
			
			if (!pipeFlag) 
			{
	
				int  argsCounter  = 0;
				char *countDivider = strtok(tmp, " ");
				char *command     = countDivider;
				
				while (countDivider) 
				{
		
					argsCounter++;
					countDivider = strtok(NULL, " ");
				
				}
		
				char *margv[argsCounter + 1];
				char *vars [100];
				
				int argsIterator = 0;
		
				char *currentArgument = strtok(sentence[sentenceIterator], " ");
				
		
				int newVars            = 0;
				int exportFlag         = 0;
				int outRedirectionFlag = 0;
				int inRedirectionFlag  = 0;
				
				
				while (currentArgument != NULL) 
				{
			
					if (currentArgument[0] != '#') 
					{
						if (!isenv(currentArgument)) 
						{
							
							if (exportFlag == 0) 
							{
								
								if (outRedirectionFlag == 0) 
								{
									
									if (inRedirectionFlag == 0) 
									{
										
										if (currentArgument[0] == '$')
										{
											
											char searcher[strlen(currentArgument)];
											int  searchCounter = 1;
											
											while (currentArgument[searchCounter] != '\0') 
											{
												
												searcher[searchCounter - 1] = currentArgument[searchCounter];
												searchCounter++;
												
											}
											
											searcher[searchCounter - 1] = '\0';
											margv   [argsIterator++]               = vararr[search(searcher)].value;
											
										}
										
										else if (strcmp(currentArgument, "export") == 0)
											exportFlag = 1;
										
										else if (strcmp(currentArgument, "list"  ) == 0)
											printvars();
					
										else if (strcmp(currentArgument, ">"     ) == 0)
											outRedirectionFlag = 1;
					
										else if (strcmp(currentArgument, "<") == 0)
											inRedirectionFlag = 1;
										
										else
											margv[argsIterator++] = currentArgument;
										
									}
									else 
									{
										
										changeIn(currentArgument);
										inRedirectionFlag = 0;
									
									}
									
								} 
								else 
								{
				
									changeOut(currentArgument);
									outRedirectionFlag = 0;
									
								}
							} 
							else 
							{
			
								if (setenv(vararr[search(currentArgument)].name,vararr[search(currentArgument)].value, 1) != 0)
									perror("not set :");
								exportFlag = 0;
								
							}
							
						}
						else
						{
							
							//char template[strlen(currentArgument)];
							//strcpy(template, currentArgument);
							if (vars[newVars]==NULL)
								vars[newVars] = (char *) malloc(strlen(currentArgument) * sizeof(char));
							
							strcpy(vars[newVars], currentArgument);
							newVars++; 
			
						}
						currentArgument = strtok(NULL, " ");
					} 
					else
						break;
					
				}
		
				for (int newVarsIterator = 0; newVarsIterator < newVars; newVarsIterator++)
					construct(vars[newVarsIterator]);
				
		
				int waitstat = 0;
		
				margv[argsIterator] = NULL;
				vars [varcount]     = NULL;
		
		
				if (margv[0] != NULL) 
				{
					
					int ret = fork();
					
					if (ret > 0)
					{
		
						wait(&waitstat);
						resetOut();
						resetIn();
						fflush(stdout);
						fflush(stdin);
					
					} 
					else if (ret == 0)
					{
		
						execvp(command, margv);
						red();
			
						printf("exec failed\n");
						perror("the error is : ");
						reset();
						return -1;
						
					} 
					else
						printf("not forked\n");
					
				}
			}
	
			else {
	
			FILE *pipe_fp, *infile;
			char readbuf[80];
			char arg1[50];
			char arg2[50];
			char *currentArgument = strtok(tmp, "|");
			strcpy(arg1, currentArgument);
			while (currentArgument != NULL) {
	
				strcpy(arg2, currentArgument);
				currentArgument = strtok(NULL, "|");
			}
			/* Open up input file */
	
			if ((infile = popen(arg1, "r")) == NULL) {
				perror("popen1");
				exit(1);
			}
	
			/* Create one way pipe line with call to popen() */
			if ((pipe_fp = popen(arg2, "w")) == NULL) {
				perror("popen2");
				exit(1);
			}
	
			/* Processing loop */
			do {
				fgets(readbuf, 80, infile);
				if (feof(infile))
				break;
	
				fputs(readbuf, pipe_fp);
			} while (!feof(infile));
	
			pclose(infile);
			pclose(pipe_fp);
			fflush(stdin);
			fflush(stdout);
	
			}
		}
    }
}
