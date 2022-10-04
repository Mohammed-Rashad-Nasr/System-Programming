#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
extern int errno;


int main(int argc, char *argv[])
{
    char c;
    int nfd = open(argv[2], O_CREAT | O_WRONLY, 0755);
    if (nfd == -1)
	perror("error file 1 : ");
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
	perror("error file 2 : ");
    while (read(fd, &c, 1))
	write(nfd, &c, 1);
    close(fd);
    close(nfd);
}
