#ifndef __minute_h__
#define __minute_h__

#define assertTrue(arg)  do { __minute__assert(#arg, (int) arg); }    while (0); 
#define assertFalse(arg) do { __minute__assert(#arg, !((int) arg)); } while (0); 
void __minute__assert(char*, int);
void report(); 

#endif 
