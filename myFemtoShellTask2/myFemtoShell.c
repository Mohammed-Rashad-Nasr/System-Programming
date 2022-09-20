/*************************************************
**************************************************
**************************************************
********   author  : Mohammed Rashad      ********
********   date    : 19 SEPT 2022         ********
********   version : 2.0                  ********
**************************************************
**************************************************
*************************************************/



#include <stdio.h>        //standerd input output library --> printf and fgets functions
#include <string.h>       //string library                --> strcmp functions
#include "mycommands.h"

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
	
	else if (!strcmp("rand\n", string))        //check for rand command
	{
	    
	    printf("7ader >> %d \n",myrand());     //print random number
	
	}

	else if (!strcmp("fact\n", string))        //check for fact command
	{
	    int x ;
	    char c ;
	    printf("enter the number >> ");	   //get the number from user 
	    scanf("%d",&x);			
	    c=getchar();                           //input buffer flush
	    printf("7ader >> %d \n",myfact(x));    //print factorial of given number
	
	}

	else if (!strcmp("fib\n", string))        //check for fib command
	{
	    int x ;
	    char c ;
	    printf("enter the number >> ");	   //get the number from user 
	    scanf("%d",&x);			
	    c=getchar();                           //input buffer flush
	    printf("7ader >> %d \n",myfib(x));     //print fibonicii series of given number
	
	}
	else
       	{
	    printf("2ol kman 2ol : %s", string); //prompt msg and echo
	}



    }

    return 0 ;

}
