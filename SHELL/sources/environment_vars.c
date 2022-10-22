/**********************************************************************************************************************
 ********************************************************************************************************************
 ********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  environment_vars.c
 *
 *        \brief  this file contains functions to control and store the environment variable
 *
 *      \details  environment_vars.c 2.0v 
 *                last edit ... 13 OCT 2022
 *                author ...... mohammed rashad
 *                
 *                notes :
 *                
 *                - tab = 8 spaces 
 *                - errors represented using errno and perror function
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"    //my header file

//********************************************************
//********************************************************




//*************** global vars ****************************
//********************************************************

int      varcount = 0;
variable varArr[MAX_VARS_NUMBER];

//********************************************************
//********************************************************



//********** function to search in the variables array for given name**********
//*****************************************************************************

int search(char * Name)
{
    int iterator = 0;

    while (iterator < varcount) 
    {
	if (strcmp(varArr[iterator].name, Name) == 0) 
        {

	    return iterator;  //return location if found
	}
	
        iterator++;  
    }
    return -1;   //return -1 if not found
}

//*****************************************************************************
//*****************************************************************************





//********** function to check if given string is variable or not using "="**********
//***********************************************************************************

int isenv(char *command)
{
    int iterator = 0;
    while (command[iterator] != '\0') 
    {
	if (command[iterator] == '=') 
        {
	    return 1;  //if it is environment var return one
	}
        
	iterator++;
    }
    return 0;   //if it is not environment var return zero

}

//***********************************************************************************
//***********************************************************************************






//********** function to get var in form of "name=value" and store it in array of structs**********
//*************************************************************************************************
void construct(char * element)
{

    char tmp1[strlen(element)];
    strcpy   (tmp1,  element) ;
    char *varname = strtok(tmp1, "=");    //get the string before = to check if it is already defined or not

    if (search(varname) == -1)            
    //if it is not defined creat new name and value structure element
    //***************************************************************
    {   
	char tmp[strlen(element)];
	strcpy(tmp, element);
	char *div = strtok(tmp, "=");              //name
	strcpy(varArr[varcount].name, div);
	while (div != NULL) 
        {
	    strcpy(varArr[varcount].value, div);   //value
	    div = strtok(NULL, "=");
	}
        varArr[varcount].global=0;
	varcount++;                                //increase number of vars 
    } 
    //***************************************************************
    
    else 
    //if it is defined change the value only
    //**************************************
    {

	char tmp[strlen(element)];
	strcpy(tmp, element);
	char *div = strtok(tmp, "=");                  

	while (div != NULL) 
        {
	    strcpy(varArr[search(varname)].value, div);
	    div = strtok(NULL, "=");
	}
	if(varArr[search(varname)].global==1)
	{
	    if (setenv(varArr[search(varname)].name,varArr[search(varname)].value,1)!=0)    
	    {
		//******** error in setenv *******							
		red();        
	        printf("not set \n");
		perror("the error is ");
		reset();
										
		//*******************************
	    }
	}

    }
    //**************************************
}
//*************************************************************************************************
//*************************************************************************************************




//********** function to count number of vars in forn "name=value" in given string line  **********
//*************************************************************************************************
int countenv(char * line)
{

    int iterator = 0;
    int count = 0;
    while (line[iterator] != '\0') 
    {
	if (line[iterator] == '=')
	    count++;
	
        iterator++;
    }
    return count;
}
//*************************************************************************************************
//*************************************************************************************************




//*******function to list all vars defined **********
//***************************************************
void printvars()
{
    for (int iterator = 0; iterator < varcount; iterator++)
	printf("%d  name : %s  value : %s\n", iterator, varArr[iterator].name,varArr[iterator].value);
}
//***************************************************
//***************************************************



/**********************************************************************************************************************
 *  END OF FILE: environment_vars.c
 *********************************************************************************************************************/
