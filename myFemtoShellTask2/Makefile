##my makefile used for project building and some other options 

$(info hello in my Makefile if you want help type make help )

define helpmsg


run          --> runs the executable program 
clean        --> cleans both executable and object files 
clean_exec   --> cleans the created executable 
clean_object --> cleans the created object.o file
help         --> prints help message 



endef


enable_gdb = TRUE

all : myFemtoShell

myFemtoShell : myFemtoShell.o
ifeq ($(enable_gdb),TRUE)
	gcc myFemtoShell.o -o myFemtoShell -ggdb
else 
	gcc myFemtoShell.o -o myFemtoShell 
endif

myFemtoShell.o:
	gcc -c myFemtoShell.c -o myFemtoShell.o

run : myFemtoShell
	./myFemtoShell

clean_exec : myFemtoShell
	rm myFemtoShell

clean_object : myFemtoShell.o
	rm myFemtoShell.o

clean : 
	rm myFemtoShell.o
	rm myFemtoShell

export helpmsg
help :
	@echo "$$helpmsg"
