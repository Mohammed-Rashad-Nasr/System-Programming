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
int size = 0;
int main()
{
    stdo = fileno(stdout);
    stdi = fileno(stdin);
    while (1) {

	resetOut();
	char buff[100];
	green();
	printf("my amazing shell >> ");
	reset();

	fgets(buff, 100, stdin);
	if (buff[0] == '\n')
	    continue;
	buff[strlen(buff) - 1] = '\0';
	int envcounter = countenv(buff);
	char alltmp[strlen(buff)];
	strcpy(alltmp, buff);
	char *sentance[simicount(buff)];
	char *divider = strtok(alltmp, ";");
	sentance[0] = (char *) malloc(strlen(divider) * sizeof(char));
	int elements = 1;
	while (divider != NULL) {
	    sentance[elements] =
		(char *) malloc(strlen(divider) * sizeof(char));
	    strcpy(sentance[elements], divider);
	    divider = strtok(NULL, ";");
	    elements++;
	}
	
	for (int sent = 1; sent < elements; sent++) {
	    char tmp[strlen(sentance[sent])];
	    strcpy(tmp, sentance[sent]);
	    int pipeflag = ispipe(tmp);
	    if (!pipeflag) {

		int count = 0;
		char *tok = strtok(tmp, " ");
		char *command = tok;
		while (tok) {

		    count++;
		    tok = strtok(NULL, " ");
		}

		char *margv[count + 1];

		char *vars[100];
		int i = 0;

		char *p;
		p = strtok(sentance[sent], " ");

		int e = size;
		int ex = 0;
		int reo = 0, rei = 0;
		while (p != NULL) {
		    if (p[0] != '#') {
			if (!isenv(p)) {
			    if (ex == 0) {
				if (reo == 0) {
				    if (rei == 0) {
					if (p[0] == '$') {
					    char searcher[strlen(p)];
					    int sc = 1;
					    while (p[sc] != '\0') {
						searcher[sc - 1] = p[sc];
						sc++;
					    }
					    searcher[sc - 1] = '\0';

					    margv[i++] =
						vararr[search(searcher)].
						value;
					} else if (strcmp(p, "export") ==
						   0)
					    ex = 1;
					else if (strcmp(p, "list") == 0)
					    printvars();

					else if (strcmp(p, ">") == 0)
					    reo = 1;

					else if (strcmp(p, "<") == 0)
					    rei = 1;
					else
					    margv[i++] = p;
				    } else {
					changeIn(p);
					rei = 0;
				    }
				} else {

				    changeOut(p);
				    reo = 0;
				}
			    } else {


				if (setenv
				    (vararr[search(p)].name,
				     vararr[search(p)].value, 1) != 0)
				    perror("not set :");
				ex = 0;
			    }
			} else {
			    char template[strlen(p)];
			    strcpy(template, p);

			    vars[e] =
				(char *) malloc(strlen(p) * sizeof(char));
			    strcpy(vars[e], p);
			    e++;


			}
			p = strtok(NULL, " ");
		    } else
			break;
		}

		for (int cc = size; cc < e; cc++)
		    construct(vars[cc]);
		size += envcounter;

		int waitstat = 0;

		margv[i] = NULL;
		vars[size] = NULL;


		if (margv[0] != NULL) {
		    int ret = fork();
		    if (ret > 0) {

			wait(&waitstat);
			resetOut();
			resetIn();
			fflush(stdout);
			fflush(stdin);
			
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

	    else {

		FILE *pipe_fp, *infile;
		char readbuf[80];
		char arg1[50];
		char arg2[50];
		char *p = strtok(tmp, "|");
		strcpy(arg1, p);
		while (p != NULL) {

		    strcpy(arg2, p);
		    p = strtok(NULL, "|");
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
