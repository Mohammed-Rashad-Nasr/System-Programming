all : bin/shell

bin/shell : sources/shell.c sources/environment_vars.c sources/IO_redirection.c sources/pipes.c sources/strings.c
        gcc sources/shell.c sources/environment_vars.c sources/IO_redirection.c sources/pipes.c sources/strings.c -o bin/shell -I ./headers

clean : 
        rm bin/*
        
        
