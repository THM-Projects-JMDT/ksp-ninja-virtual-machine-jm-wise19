/*
 * stack.h -- All Stack suport Functions
 */

#ifndef NJCM_STACK_H_INCLUDED
#define NJCM_STACK_H_INCLUDED

#include <stdbool.h>
#include <support.h>

typedef struct {
  bool isObjRef; /* slot used for object reference? */
  union {
    ObjRef objRef; /* used if isObjRef=TRUE */
    int number;    /* used if isObjRef=FALSE */
  } u;
} StackSlot;

void initStack(int size);
void push(ObjRef value);
void pushNoRef(int value);
ObjRef pop(void);
int popNoRef(void);
void asf(int value);
void rsf(void);
void pushl(int n);
void popl(int n);
void printStack(int atFrame);
void drop(const int n);
void pushr(void);
void popr(void);

#endif