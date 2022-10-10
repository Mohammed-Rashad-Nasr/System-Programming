
#include <stdio.h>



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

int simicount(char *c)
{
    int i = 0;
    int count = 0;
    while (c[i] != '\0') {
	if (c[i] == ';')
	    count++;
	i++;
    }

    return count;
}
