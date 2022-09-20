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


enable_gdb = TRUE

all : myFemtoShell

myFemtoShell : myFemtoShell.o libcommand.a
ifeq ($(enable_gdb),TRUE)
	gcc myFemtoShell.o -o myFemtoShell -ggdb -lcommand -L./ 
else 
	gcc myFemtoShell.o -o myFemtoShell -lcommand -L./
endif

myFemtoShell.o:myFemtoShell.c
	gcc -c myFemtoShell.c -o myFemtoShell.o

libcommand.a:rand.o fact.o fib.o
	ar -rs libcommand.a rand.o fact.o fib.o

rand.o:rand.c
	gcc -c rand.c 

fact.o:fact.c
	gcc -c fact.c

fib.o:fib.c
	gcc -c fib.c

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
