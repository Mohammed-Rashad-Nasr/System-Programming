#include <string.h>
#include <stdio.h>
#include "header.h"



int search(char *s)
{
    int i = 0;

    while (i < varcount) {
	if (strcmp(vararr[i].name, s) == 0) {

	    return i;
	}
	i++;
    }
    return -1;
}

int isenv(char *c)
{
    int i = 0;
    while (c[i] != '\0') {
	if (c[i] == '=') {
	    return 1;

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

void printvars()
{
    for (int ii = 0; ii < varcount; ii++)
	printf("%d  name : %s  value : %s\n", ii, vararr[ii].name,
	       vararr[ii].value);
}