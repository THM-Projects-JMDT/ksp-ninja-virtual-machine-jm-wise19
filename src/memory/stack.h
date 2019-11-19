#ifndef NJCM_STACK_H_INCLUDED
#define NJCM_STACK_H_INCLUDED

#include "obj.h"
#include <stdbool.h>

typedef struct {
  bool isObjRef; /* slot used for object reference? */
  union {
    ObjRef objRef; /* used if isObjRef=TRUE */
    int number;    /* used if isObjRef=FALSE */
  } u;
} StackSlot;

void push(int value);
int pop(void);
void asf(int value);
void rsf(void);
void pushl(int n);
void popl(int n);
void printStack(int atFrame);
void drop(const int n);
void pushr(void);
void popr(void);

#endif