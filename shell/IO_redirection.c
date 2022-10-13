/**********************************************************************************************************************
 ********************************************************************************************************************
 ********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IO_redirection.c
 *
 *        \brief  this file contains functions to control input output redirection
 *
 *      \details  IO_redirection.c 2.0v 
 *                last edit ... 13 OCT 2022
 *                author ...... mohammed rashad
 *                
 *                notes :
 *                
 *                - tab = 8 spaces 
 *                - errors represented using errno and perror function
 *
 *
 *********************************************************************************************************************
 *********************************************************************************************************************
 *********************************************************************************************************************/


//******************* includes ***************************
//********************************************************

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "header.h"      //my header file

//********************************************************
//********************************************************




//*************** global vars ****************************
//********************************************************

int out, in, err, stdi, stde, stdo;   //variable to contain fds of redirection files and original files too

//********************************************************
//********************************************************







//*********output redirection function *******************
//********************************************************

void changeOut(char *path)
{

    out = open(path, O_CREAT | O_WRONLY, 0755);  //open output file or creat it if it is not found in write only mode
    if (out == -1 )
    {
            //******** error in open *******
            
            red();        
            printf("failed to open the file %s \n",path);
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }
    stdo = dup(fileno(stdout));                  //save the original stdout
    if (stdo == -1 )
    {
            //******** error in dup *******
            
            red();        
            printf("failed to creat copy of stdout \n");
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }
                       
    if (dup2(out, fileno(stdout)) == -1 )        //redirect the output
    {
            //******** error in dup2 *******
            
            red();        
            printf("failed to redirect the output \n");
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }

}

//********************************************************
//********************************************************






//*********input redirection function ********************
//********************************************************
void changeIn(char *path)                               
{

    in = open(path, O_CREAT | O_RDONLY, 0755);                //open input file or creat it if it is not found in read only mode
    if (in == -1 )
    {
            //******** error in open *******
            
            red();        
            printf("failed to open the file %s \n",path);
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }
    stdi = dup(fileno(stdin));                                //save the original stdin
    if (stdin == -1 )
    {
            //******** error in dup *******
            
            red();        
            printf("failed to creat copy of stdin \n");
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }
    
    if (dup2(in, fileno(stdin)) == -1 )                       //redirect the input
    {
            //******** error in dup2 *******
            
            red();        
            printf("failed to redirect the input \n");
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }                                 
}
//********************************************************
//********************************************************





//*********reset output to stdout function ********************
//*************************************************************
void resetOut()
{
    fflush(stdin);
    fflush(stdout);
    
    if (dup2(stdo, fileno(stdout)) == -1 )                       //redirect the output
    {
            //******** error in dup2 *******
            
            red();        
            printf("failed to redirect the output to stdout \n");
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }                                 
}
//*************************************************************
//*************************************************************




//*********reset input to stdin function ********************
//*************************************************************
void resetIn()
{
    fflush(stdout);
    fflush(stdin);
    
    
    if (dup2(stdi, fileno(stdin)) == -1 )                       //redirect the input
    {
            //******** error in dup2 *******
            
            red();        
            printf("failed to redirect the input to stdin \n");
            perror("the error is ");
            reset();
            exit(1);
            
            //*******************************
            
    }                          
}
//*************************************************************
//*************************************************************




/**********************************************************************************************************************
 *  END OF FILE: IO_redirection.c
 *********************************************************************************************************************/
