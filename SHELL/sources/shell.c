/**********************************************************************************************************************
 ********************************************************************************************************************
 ********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  shell.c
 *
 *        \brief  this file contains main code runs when shell is executing 
 *                 and uses functions defined in the other .c files
 *
 *      \details  shell.c 3.0v 
 *                last edit ... 13 OCT 2022
 *                author ...... mohammed rashad
 *                
 *                notes :
 *                
 *                - tab = 8 spaces 
 *                - errors represented using errno and perror function
 *                - the code divides line in semicolons to separate commands 
 *                - built in functions : list , export used for listing and exporting environment vars
 *                  and help for printing help msg
 *                - note that shell is space sensetive x=5 and x = 5 are not equal 
 *                  "don't separate variable name , value and equal operator by spaces"
 *                - define the maximum values in the header file and it will be your responsibility to 
 *                  don't exceed these limits
 *
 *
 *********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************/





//******************* includes ***************************
//********************************************************

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "header.h"        //my header file

//********************************************************
//********************************************************


//******************* global vars ************************
//********************************************************

extern int varcount ;
extern variable varArr[100];
extern int out, in, err, stdi, stde, stdo;

//********************************************************
//********************************************************



/*****************************************************************************
******************************************************************************
************************** _, _  _, _ _, _ ***********************************
************************** |\/| /_\ | |\ | ***********************************
************************** |  | | | | | \| ***********************************
************************** ~  ~ ~ ~ ~ ~  ~ ***********************************
******************************************************************************
*****************************************************************************/                                                


int main()
{
    stdo = fileno(stdout);
    stdi = fileno(stdin) ;
	
	
    while (1) {
				
		//*****************************************************
		char buffer[MAX_LINE_LENGTH]; //buffer to get all data from user **  
		//*****************************************************
		
		
		//********************************************************               
		//********* _  _ _  _ _  _ _|_   _ _  _ _ ****************
		//*********|_)| (_)| | ||_) |   | | |_\(_|****************
		//*********|            |               _|****************
		//********************************************************
		green ();                        //change color to green *
		printf("my amazing shell >> ");  //print msg             *  
		reset ();                        //reset color to white  *
	        //********************************************************
		//********************************************************
		
		
		fgets(buffer, MAX_LINE_LENGTH, stdin);          //get input into the buffer
		
		
		//********************************************
		if (buffer[0] == '\n')      //new line case **
			continue;                           /*
		//*******************************************/
		
		
		buffer[strlen(buffer) - 1] = '\0';  //ignore \n caused by hitting enter and change it to NULL charvter
		
		
		//***** take copy from the buffer to divide it ***********
		char line[strlen(buffer)];         
		strcpy   (line, buffer);
		//********************************************************
		
		
		//******** dividing into sentences ***********************
		//********************************************************
		
		char *sentence[semicount(buffer)];           //semicount counts number of semicolons in the buffer to get number of sentences in the line
		int  sentencesCounter  = 0;                  //initialize counter to count sentences 
		char *sentenceDivider  = strtok(line, ";");  //dividing line into sentences
		 
		while (sentenceDivider != NULL) 
		{
			
			sentence[sentencesCounter] = (char *) malloc(strlen(sentenceDivider) * sizeof(char));  //allocate space for the new sentece 
			if (sentence[sentencesCounter] == NULL)                                                //malloc returned error
			{
				//******** error in malloc *******
				
				red();        
				printf("allocation couldn't work \n");
				perror("the error is ");
				reset();
				exit(1);
				
				//*******************************
			}
			strcpy                       (sentence[sentencesCounter], sentenceDivider);            //copy new sentence
			sentenceDivider            = strtok(NULL,";");                                         //continue
			sentencesCounter++;                                                                     
		
		}
		
		//********************************************************
		//********************************************************
		
		
		
		
		//*********************************************************
		//*********************************************************
		//*********  _        _    _       _|_  .   _    _  *******
		//********* (/_  ><  (/_  (_  |_|   |   |  (_)  | | *******
		//*********                                         *******
		//*********************************************************
		//*********loop on sentences and execute each of them******
		//*********************************************************
		
		for (int sentenceIterator = 0; sentenceIterator < sentencesCounter; sentenceIterator++)
		{
			
			//***** take copy from the buffer to divide it ***********	
			char tmp[strlen(sentence[sentenceIterator])]; 
			strcpy  (tmp,   sentence[sentenceIterator]) ;
			//********************************************************
			
			int  pipeFlag = ispipe(tmp);  //ispipe checks if there is piping in the sentence
			
			
			if (!pipeFlag)                
                        // first condition to be checked  if there is no piping go inside if there is piping skip all this code inside
			{
				
				//*********************** if you are here this means the sentence has no piping in it ! ***************
				//*****************************************************************************************************
			    
				//***** divide sentence on space to count args ***********	
				//********************************************************
				int  argsCounter   = 0;
				char *countDivider = strtok(tmp, " ");
				char *command      = countDivider;
				
				while (countDivider) 
				{
		
					argsCounter++;
					countDivider = strtok(NULL, " ");
				
				}
                                //********************************************************
				
				
				int newVars            = 0;     //new variables counter for variables entered in this sentence
				int exportFlag         = 0;     //export command flag will be raised when user use the command
				int outRedirectionFlag = 0;     //output redirection flag detects if user typed >
				int inRedirectionFlag  = 0;     //input  redirection flag detects if user typed <
                                int cdflag             = 0;     //cd command flag
				
				char *margv[argsCounter + 1];   //array of exec arguments
				char *vars [MAX_VARS_NUMBER];               //array of environment variables stored as strings
				int  argsIterator = 0;          //iterator for margv
		
		
		
		
                                //***** divide sentence on space for checking and using them ***********	
				//**********************************************************************
				
				char *currentArgument = strtok(sentence[sentenceIterator], " "); 		
				
				while (currentArgument != NULL) 
				{
					
					//****************** looping on words separated by spaces until the end of the sentence ***************
					//*****************************************************************************************************
			
					if (currentArgument[0] != '#')     
                                        // check if this is a comment starting by # so it will skip all the sentence if no just go inside 
					{ 
					        //************************ it is not a comment ************************
						//*********************************************************************
						
						if (!isenv(currentArgument))              
                                                // check if this is an environment variable if not continue inside 
						{
							
						       //************************ it is not an environment variable **********
						       //*********************************************************************
							
							if (exportFlag == 0)             
                                                        /*check if this is an argument of export function by checking export flag
                                                          which may be set in the previous word if not just continue inside      */
							{
								
								//****************** it is not export argument ************************
								//*********************************************************************
								
								if (outRedirectionFlag == 0)       
                                                                /*check if this is an argument of output redirection function by checking output 
                                                                  redirection flag which may be set in the previous word if not just continue inside */
								{
									
									//*************** it is not output redirection argument ***************
									//*********************************************************************
									
									if (inRedirectionFlag == 0)         
                                                                        /*check if this is an argument of input redirection function by checking input
                                                                          redirection flag which may be set in the previous word if not just continue inside */
									{
										
										//*************** it is not input redirection argument ****************
										//*********************************************************************
                                                                                
                                                                                if (cdflag == 0)
										/*check if this is an argument of cd function by checking cd flag
                                                                                  which may be set in the previous word if not just continue inside      */
                                                                                {
                                                                                        //****************** it is not cd argument ****************************
                                                                                        //*********************************************************************
                                                                                        
                                                                                        if (currentArgument[0] == '$')      
                                                                                        /*finally check if it is trying to access environment variable if yes 
                                                                                        do the following code if no continue                               */
                                                                                        {
                                                                                                
                                                                                        //*************** access environment variable using $ operator ********
                                                                                        //*********************************************************************
                                                                                                
                                                                                                
                                                                                                // replace $name by name to search for it *****************************
                                                                                                
                                                                                                char searcher[strlen(currentArgument)];
                                                                                                int  searchCounter = 1;
                                                                                                
                                                                                                while (currentArgument[searchCounter] != '\0') 
                                                                                                {
                                                                                                        
                                                                                                        searcher[searchCounter - 1] = currentArgument[searchCounter];
                                                                                                        searchCounter++;
                                                                                                        
                                                                                                }
                                                                                                
                                                                                                searcher[searchCounter - 1] = '\0';
                                                                                                
                                                                                                //*********************************************************************
                                                                                                
                                                                                                if (search(searcher) == -1)    
                                                                                                {
                                                                                                        //******** not found ***********
                                                                                                        
                                                                                                        red();        
                                                                                                        printf("element not found \n");
                                                                                                        reset();
                                                                                                        
                                                                                                        //*******************************
                                                                                                }
                                                                                                else 
                                                                                                // search and put the value of the given name into arguments array
                                                                                                        margv [argsIterator++] = varArr[search(searcher)].value;
                                                                                                
                                                                                                
                                                                                                //*********************************************************************
                                                                                                //*********************************************************************
                                                                                                
                                                                                        }
                                                                                        
                                                                                        else if (strcmp(currentArgument, "export") == 0)
                                                                                        // export word found set the export flag to take the following word as argument
                                                                                                exportFlag = 1;                               
                                                                                        
                                                                                        else if (strcmp(currentArgument, "list"  ) == 0)
                                                                                        // list word found print all the variables 
                                                                                                printvars();                 
                                                                                        
                                                                                        else if (strcmp(currentArgument, "help"  ) == 0)
                                                                                        // help word found print help msg        
                                                                                                printhelp();     
                                                                                        
                                                                                        else if (strcmp(currentArgument, "cd"  ) == 0)
                                                                                        // cd word found take the following input as argument        
                                                                                                cdflag=1;
                                                
                                                                                        else if (strcmp(currentArgument, ">"     ) == 0)
                                                                                        /* > character found set the output redirection flag to take the following 
                                                                                        word as argument */
                                                                                                outRedirectionFlag = 1;                       
                                                
                                                                                        else if (strcmp(currentArgument, "<") == 0)
                                                                                        /* < character found set the input redirection flag to take the following
                                                                                        word as argument	*/
                                                                                                inRedirectionFlag = 1;    
                                                                                                
                                                                                        
                                                                                        else
                                                                                        // no special thing just add the argument to the args array                
                                                                                                margv[argsIterator++] = currentArgument;      
										
                                                                                }
                                                                                else
                                                                                {
                                                                                        //*** cd flag raised change dir to the given path ********
                                                                                        //********************************************************
                                                                                        
                                                                                        if (chdir(currentArgument)==-1)
                                                                                        {
                                                                                        	//******** error in chdir *******
                                                                                        	
                                                                                        	red();        
                                                                                        	printf("can not go to %s \n",currentArgument);
                                                                                        	perror("the error is ");
                                                                                        	reset();
                                                                                        	
                                                                                        	//*******************************
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                //******** dir changed *********
                                                                                                char cwd[100] ;
												getwd(cwd);
                                                                                                cyan();        
                                                                                                printf("new dir : %s \n",cwd);
                                                                                                reset();
                                                                                                
                                                                                                //*******************************
                                                                                        }
                                                                                        cdflag=0;
                                                                                        
                                                                                        //********************************************************
                                                                                        //********************************************************
                                                                               
                                                                                }
                                                                        
                                                                        }
									else 
									{
										//*** input redirection flag raised redirect input to the given path ********
										//***************************************************************************
										
										changeIn(currentArgument);
										inRedirectionFlag = 0;       //reset flag
										
										//***************************************************************************
										//***************************************************************************
									}
									
								} 
								else 
								{
									
									//*** output redirection flag raised redirect output to the given path ********
									//*****************************************************************************
									
									changeOut(currentArgument);
									outRedirectionFlag = 0;     //reset flag
									
									//*****************************************************************************
									//*****************************************************************************
									
								}
							} 
							else 
							{
								//*** export flag raised now find & export the given variable  ****************
			                                        //*****************************************************************************
								if (search(currentArgument) == -1)
								{
									//******** not found ***********
									
									red();        
									printf("element not found \n");
									reset();
									
									//*******************************
								}
								else 
								{
									if (setenv(varArr[search(currentArgument)].name,varArr[search(currentArgument)].value,1)!=0)    
									{
										//******** error in setenv *******
										
										red();        
										printf("not set \n");
										perror("the error is ");
										reset();
										
										//*******************************
									}
								}
								
								exportFlag = 0;          //reset flag
								
								//*****************************************************************************
								//*****************************************************************************
							}
							
						}
						else
						{
							
							//*** this an environment variable not an argument so add it to vars  *********
							//*****************************************************************************
							
							if (vars[newVars]==NULL)
								//allocate space for new variable if it is not already allocated
                                                                vars[newVars] = (char *) malloc(strlen(currentArgument) * sizeof(char)); 
							
							
							if (vars[newVars] == NULL)    
							{
								//******** error in malloc *******
								
								red();        
								printf("allocation couldn't work \n");
								perror("the error is ");
								reset();
								exit(1);
								
								//*******************************
							}
							
							strcpy(vars[newVars], currentArgument); 
							newVars++; 
							
							//*****************************************************************************
                                                        //*****************************************************************************
							
						}
						currentArgument = strtok(NULL, " ");   //continue to the next word >>>>
					} 
					else
						break;               //comment detected just skip everything and go to the next sentence please 
					
				
                                }//end of sentence parsing in while loop
				//**********************************************************************	
				//**********************************************************************
				
				
                                
				//*** add environment variables on array of structs as name and value  *********
                                //******************************************************************************		
				
				for (int newVarsIterator = 0; newVarsIterator < newVars; newVarsIterator++)
					construct(vars[newVarsIterator]);
				
				//*****************************************************************************		
				//*****************************************************************************		

		
				int waitstat = 0;            //wait state of process child
		
				margv[argsIterator] = NULL;  //end array by NULL
				vars [varcount]     = NULL;  //end array by NULL
		
		        
				if (margv[0] != NULL)        //check if there is any command in the margv array
				{
					
					int ret = fork();        //forking ...
					
					//******** parent code *********
					//******************************
					if (ret > 0)      
					{
		
						wait    (&waitstat);  //waiting for child status
						resetOut();           //reset files back to stdout 
						resetIn ();           //reset files back to stdin 
						fflush  (stdout);
						fflush  (stdin);
					
					} 
					//******************************
					//******************************
					
					//******** child code **********
					//******************************
					else if (ret == 0)
					{
		
						execvp(command, margv);   //execution
						
						//******** if code here execute then exec failed *********
						red();                     
						printf("exec failed\n");
						perror("the error is ");
						reset();
						exit (1);
						//********************************************************
						
					} 
					//******************************
					//******************************
					
					//******** error in fork *******
					//******************************
					else
					{
					    red();        
					    printf("fork did not work\n");
					    perror("the error is ");
					    reset();
					    exit (1);
					}
					//******************************
					//******************************
					
				}//end of normal commands execution 
                                //****************************************
                                //****************************************
				
				
			}//end of every thing which is not piping
                        //****************************************
                        //****************************************
	
			
			
			
			
			//****************************************
			//****************************************
			//***********  _ . _ . _  _  *************
			//*********** |_)||_)|| |(_| *************
			//*********** |   |       _| *************
			//****************************************
			//****there is piping in the sentense*****
			//****************************************
			
		
			else 
			{
	
				FILE *pipe_fp, *infile;                        //pointer to input and pipe files
				char readbuf[MAX_PIPE_LENGTH];                 //buffer to pass data
				char arg1   [MAX_PIPE_ARG1];                   //string before |
				char arg2   [MAX_PIPE_ARG2];                   //string after |
                                                                               
				char *currentArgument = strtok(tmp, "|");      
				strcpy(arg1, currentArgument);                 //get data before |
				while (currentArgument != NULL)                
				{
					strcpy(arg2, currentArgument);         //get data after |
					currentArgument = strtok(NULL, "|");
				}
				
				
				//******** Open up input file for reading only *******
				//****************************************************
				if ((infile = popen(arg1, "r")) == NULL) 
				{
					//******** error in popen *******
					
					red();        
					printf("input file couldn't be opened \n");
					perror("the error is ");
					reset();
					exit(1);
					
					//*******************************
				}
				//****************************************************
				//****************************************************
				
				
				//******** Open one line pipe file for writing only **
				//****************************************************
				if ((pipe_fp = popen(arg2, "w")) == NULL) 
				{
					//******** error in popen *******
					
					red();        
					printf("pipe file couldn't be opened \n");
					perror("the error is ");
					reset();
					exit(1);
					
					//*******************************
				}
				//****************************************************
				//****************************************************
				
				//******** move data from infile to pipe file ********
				//****************************************************
				do 
				{
					fgets(readbuf, 80, infile);  //get data
					if (feof(infile))            //end of file
					break;
					fputs(readbuf, pipe_fp);     //put data
				}
				while (!feof(infile));
				
				//****************************************************
				//****************************************************
				
				pclose(infile);   //close infile
				pclose(pipe_fp);  //close pipe file
				fflush(stdin);    
				fflush(stdout);
	
			} // end of piping
                        //****************************************
                        //****************************************
                        

		}//end of sentence in for loop
                //****************************************
                //****************************************
                

        }//end of the infinite loop
        //****************************************
        //****************************************


}//end of main 
//****************************************
//****************************************






/**********************************************************************************************************************
 *  END OF FILE: shell.c
 *********************************************************************************************************************/
