#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "header.h"

int out, in, err, stdi, stde, stdo;


void changeOut(char *path)
{

    out = open(path, O_CREAT | O_WRONLY, 0755);
    stdo = dup(fileno(stdout));
    dup2(out, fileno(stdout));

}

void changeIn(char *path)
{

    in = open(path, O_CREAT | O_RDONLY, 0755);
    stdi = dup(fileno(stdin));
    dup2(in, fileno(stdin));

}

void resetOut()
{
    fflush(stdin);
    fflush(stdout);
    dup2(stdo, fileno(stdout));
}

void resetIn()
{
    fflush(stdout);
    fflush(stdin);
    dup2(stdi, fileno(stdin));
}
