#include <unistd.h>
#include <errno.h>
#include <stdio.h>

extern int errno;


int main()
{
    char dir[100];
    if (getcwd(dir, 100) != NULL) {
	printf("current directory : %s \n ", dir);
    } else {
	perror("error : ");
    }
}
