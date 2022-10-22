#ifndef SHELL_H
#define SHELL_H


//************** variables struct ************************
//********************************************************
typedef struct {
    char name[20];
    char value[100];
    int global;
} variable;
//********************************************************
//********************************************************




//************** maximum numbers *************************
//********************************************************
#define MAX_LINE_LENGTH 100
#define MAX_VARS_NUMBER 100
#define MAX_PIPE_LENGTH 80
#define MAX_PIPE_ARG1   50
#define MAX_PIPE_ARG2   50
//********************************************************
//********************************************************





//************** functions declaration*************************
//********************************************************
extern int  search      (char *s);
extern int  isenv       (char *c);
extern void construct   (char *c);
extern int  countenv    (char *c);
extern void printvars   ();

extern void changeOut   (char *path);
extern void changeIn    (char *path);
extern void resetOut    ();
extern void resetIn     ();
					    
extern int  ispipe      (char *s);

extern void red         ();
extern void green       ();
extern void reset       ();
extern void cyan        ();
extern int  semicount   (char *c);
extern void printhelp   ();
//********************************************************
//********************************************************






#endif





/**********************************************************************************************************************
 *  END OF FILE: header.h
 *********************************************************************************************************************/
