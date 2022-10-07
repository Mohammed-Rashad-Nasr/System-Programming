#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    char name[20];
    char value[100];
} variable;
int varcount = 0;
variable vararr[100];

int search(char *s)
{
    int i = 0;

    while (i < varcount) {
	if (strcmp(vararr[i].name, s) == 0) {
	    printf("found at %d\n", i);
	    return i;
	}
	i++;
    }
    return -1;
}


void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[1;32m");
}

void reset()
{
    printf("\033[0m");
}

void cyan()
{

    printf("\033[0;36m");
}

int isenv(char *c)
{
    int i = 0;
    while (c[i] != '\0') {
	if (c[i] == '=') {
	    return 1;
	    // printf("found\n");
	}
	i++;
    }
    return 0;

}

void construct(char *c)
{

    char tempo1[strlen(c)];
    strcpy(tempo1, c);
    char *div1 = strtok(tempo1, "=");

    if (search(div1) == -1) {
	char tempo[strlen(c)];
	strcpy(tempo, c);
	char *div = strtok(tempo, "=");
	strcpy(vararr[varcount].name, div);
	while (div != NULL) {
	    strcpy(vararr[varcount].value, div);
	    div = strtok(NULL, "=");
	}
	varcount++;
    } else {
	char tempo[strlen(c)];
	strcpy(tempo, c);
	char *div = strtok(tempo, "=");

	while (div != NULL) {
	    strcpy(vararr[search(div1)].value, div);
	    div = strtok(NULL, "=");
	}

    }


}

int countenv(char *c)
{

    int i = 0;
    int count = 0;
    while (c[i] != '\0') {
	if (c[i] == '=')
	    count++;
	i++;
    }
    return count;
}



//char ** vars ;
int size = 0;
int main()
{

    while (1) {
	char buff[100];
	green();
	printf("my amazing shell >> ");
	reset();
//      if(vars!=NULL){
//      for(int u = 0 ; u<=size ; u++ ) printf ("var of %d : %s\n",u,vars[u]);
//      }
	fgets(buff, 100, stdin);
	if (buff[0] == '\n')
	    continue;
	buff[strlen(buff) - 1] = '\0';
	int envcounter = countenv(buff);

	char tmp[strlen(buff)];
	strcpy(tmp, buff);

	int count = 0;
	char *tok = strtok(tmp, " ");
	char *command = tok;
	while (tok) {

	    count++;
	    tok = strtok(NULL, " ");
	}

	char *margv[count + 1];

/*	if (vars==NULL) {
		vars =(char**)malloc((100)*sizeof(*vars));
		printf("first time \n");
	for(int u = 0 ; u<=size ; u++ ) printf ("var of %d : %s\n",u,vars[u]);

	}
	else{
	       //	vars = (char**)realloc(vars,(size+envcounter)*sizeof(*vars));
                printf("not first\n");
	for(int u = 0 ; u<=size ; u++ ) printf ("var of %d : %s\n",u,vars[u]);

	}*/

	char *vars[100];
	int i = 0;

	char *p;
	p = strtok(buff, " ");

	int e = size;
	int ex = 0;
	while (p != NULL) {

	    if (!isenv(p)) {
		if (ex == 0) {
		    printf("not extract\n");
		    if (p[0] == '$') {
			char searcher[strlen(p)];
			int sc = 1;
			while (p[sc] != '\0') {
			    searcher[sc - 1] = p[sc];
			    sc++;
			}
			searcher[sc - 1] = '\0';
			//printf("%s,%s\n",p,searcher);
			margv[i++] = vararr[search(searcher)].value;
		    } else if (strcmp(p, "extract") == 0)
			ex = 1;
		    else
			margv[i++] = p;
		} else {
		    printf("extractng \"%s=%s\"\n", vararr[search(p)].name,
			   vararr[search(p)].value);
		    if (setenv
			(vararr[search(p)].name, vararr[search(p)].value,
			 1) != 0)
			perror("not set :");
		    ex = 0;
		}
	    } else {
		char template[strlen(p)];
		strcpy(template, p);
		// template  = strtok(template,"=");
		// template[strlen(template)-1]='=';
		// printf("search : %d\n",search(vars,template));
		vars[e] = (char *) malloc(strlen(p) * sizeof(char));
		strcpy(vars[e], p);
		e++;
		//printf("var\n");

	    }
	    p = strtok(NULL, " ");
	}

	for (int cc = size; cc < e; cc++)
	    construct(vars[cc]);
	for (int ii = 0; ii < varcount; ii++)
	    printf("%d  name : %s  value : %s\n", ii, vararr[ii].name,
		   vararr[ii].value);
	size += envcounter;

	int waitstat = 0;
	for (int x = 0; x < i; x++)
	    printf("arg of %d : %s\n", x, margv[x]);
	margv[i] = NULL;
	vars[size] = NULL;
	//printf("size = %ld\n",sizeof(vars));
//      for(int u = 0 ; u<=size ; u++ ) printf ("var of %d : %s\n",u,vars[u]);

	if (margv[0] != NULL) {
	    int ret = fork();
	    if (ret > 0) {

		wait(&waitstat);
	    } else if (ret == 0) {

		execvp(command, margv);
		red();
		printf("exec failed\n");
		perror("the error is : ");
		reset();
		return -1;
	    } else
		printf("not forked\n");


	}
    }

}
