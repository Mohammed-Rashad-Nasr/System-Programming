##my makefile used for project building and some other options 

$(info hello in my Makefile if you want help type make help )

define helpmsg


run          --> runs the executable program 
clean        --> cleans both executable and object files 
clean_exec   --> cleans the created executable 
clean_object --> cleans the created object.o file
clean_lib    --> cleans the created library
help         --> prints help message 



endef


enable_gdb =FALSE
linking_type =dynamic
lib=shared


ifeq ($(lib),shared)
libname:=libcommand.so 

else 
libname:=libcommand.a 

endif


all : myFemtoShell

myFemtoShell : myFemtoShell.o $(libname)

ifeq ($(enable_gdb),TRUE)
ifeq ($(linking_type),dynamic)
	gcc myFemtoShell.o -o myFemtoShell -ggdb -lcommand -L./ 

else
	gcc myFemtoShell.o -o myFemtoShell -ggdb --static -lcommand -L./
endif
 
else
ifeq ($(linking_type),dynamic)
	gcc myFemtoShell.o -o myFemtoShell -lcommand -L./ 
else
	gcc myFemtoShell.o -o myFemtoShell --static -lcommand -L./
endif	
endif
 
myFemtoShell.o:myFemtoShell.c
	gcc -c myFemtoShell.c -o myFemtoShell.o

$(libname):rand.o fact.o fib.o
ifeq ($(libname),libcommand.a )
	ar -rs libcommand.a rand.o fact.o fib.o
else
	gcc -shared rand.o fact.o fib.o -o libcommand.so
endif

rand.o:rand.c
ifeq ($(lib),shared)
	gcc -c -fPIC rand.c 
else 
	gcc -c rand.c
endif

fact.o:fact.c
ifeq ($(lib),shared)
	gcc -c -fPIC fact.c 
else 
	gcc -c fact.c
endif


fib.o:fib.c
ifeq ($(lib),shared)
	gcc -c -fPIC fib.c 
else 
	gcc -c fib.c
endif

run : myFemtoShell
	./myFemtoShell

clean_exec : myFemtoShell
	rm myFemtoShell

clean_object : 
	rm *.o

clean_lib: libcommand.a
	rm libcommand.a

clean : 
	rm *.o
	rm myFemtoShell
	rm libcommand.a

export helpmsg
help :
	@echo "$$helpmsg"
