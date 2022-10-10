#ifndef SHELL_H
#define SHELL_H



typedef struct {
    char name[20];
    char value[100];
} variable;

int varcount = 0;

variable vararr[100];

int out, in, err, stdi, stde, stdo;


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
extern int  simicount   (char *c);



#endif
