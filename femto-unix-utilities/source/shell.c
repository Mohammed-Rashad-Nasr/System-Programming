#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main()
{

    while (1) {
	char buff[100];
	printf("my amazing shell >> ");
	fgets(buff, 100, stdin);
	if (buff[0] == '\n')
	    continue;
	buff[strlen(buff) - 1] = '\0';
	//char command[strlen(buff)];
	//      printf("entered : %s \n",buff);
	//strcpy(command, buff);
	//      printf("command %s \n",command);
	char tmp [strlen(buff)];
	strcpy(tmp,buff);
//	printf (" tmp : %s \n ",tmp );
	int count = 0 ;
	char *tok =strtok(tmp," ");
	char * command = tok ; 
	while(tok){
	      // 	printf("count : %s \n",tmp);
		count++;
		tok = strtok(NULL," ");
	}
//	printf("count : %d \n",count);
	char *margv[count+1];
	int i =0 ;
//	printf ("buff : %s \n",buff);
	char * p ;
	p = strtok(buff," ");
//	printf ("strtok : %s \n",p);
	while (p!=NULL){
	   // printf("comm %d : %s " ,i,p);

            //margv[i]=malloc(sizeof(char)*strlen(p));
	    margv[i++]=p;
	    p = strtok(NULL," ");
	}
	char *menvp[] = { NULL };
	int waitstat = 0;
	for(int x = 0 ; x<i ; x++ ) printf ("arg of %d : %s\n",x,margv[x]);
	margv[i]=NULL;
	int ret = fork();
	if (ret > 0) {
	    //      printf("parent\n");
	    wait(&waitstat);
	} else if (ret == 0) {
	    //      printf("child\n");
	    //      strcpy(margv[0],command);
	    execve(command, margv, menvp);
	    printf("exec failed\n");
	    perror("the error is : ");
	    return -1;
	} else
	    printf("not forked\n");

    }


}
