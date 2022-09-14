/*************************************************
**************************************************
**************************************************
********   author  : Mohammed Rashad      ********
********   date    : 14 SEPT 2022         ********
********   version : 1.0                  ********
**************************************************
**************************************************
*************************************************/



#include <stdio.h>   //standerd input output library --> printf and fgets functions
#include <string.h>  //string library                --> strcmp functions

int main()
{

    char string[50]; 		//string to hold text msg

    while (1)
    {		                //while loop contains the program 

	printf("2olly 7aga > ");           
	fgets(string, 50, stdin);          //take input from user


	if (!strcmp("exit\n", string))     //check for exit command
	{
	    
	    printf("bye ya basha :..(\n"); //good bye meassage 
	    break;                         //exit
	
	} 
	
	else
       	{
	    printf("2ol kman 2ol : %s", string); //prompt msg and echo
	}
    }

    return 0 ;

}
