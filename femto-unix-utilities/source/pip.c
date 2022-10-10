#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
        FILE *pipe_fp, *infile;
        char readbuf[80];
char buf[100];
fgets(buf,100,stdin);
        char  arg1 [50] ;
	char  arg2 [50] ; 
	char * p = strtok(buf , "|");
	strcpy(arg1,p);
	while(p!=NULL){

strcpy(arg2,p);
p=strtok(NULL,"|");
	}
	/*while (strcmp(argv[i],",")!=0) i++;
	printf("%d\n",i);
	for (int j =0 ; j<i ; j++) {
        int len = strlen(arg1)-1;
	for (int c= len;argv[j][c-len]!='\0';c++) arg1[c]=argv[j][c-len];
	arg1[strlen(arg1)-1]=" "; 
	}*/
	//printf("%s\n",arg1);
	//printf("%s\n",arg2);
	/*if( argc != 3) {
                fprintf(stderr, "USAGE:  popen3 [command] [filename]\n");       
                exit(1);
        }*/

        /* Open up input file */
	
        if (( infile = popen(arg2, "r")) == NULL)
        {
                perror("popen1");
                exit(1);        
        }

        /* Create one way pipe line with call to popen() */
       if (( pipe_fp = popen(arg1, "w")) == NULL)
        {
                perror("popen2");
                exit(1);
        }

        /* Processing loop */
        do { 
                fgets(readbuf, 80, infile);
                if(feof(infile)) break;

                fputs(readbuf, pipe_fp);
        } while(!feof(infile));

        pclose(infile); 
        pclose(pipe_fp);

        return(0);
}
