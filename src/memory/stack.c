#include "stack.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include <stdio.h>
#define SK_SIZE 10000

static int sp = 0;
static int fp = 0;

static StackSlot stack[SK_SIZE];
static ObjRef return_value_register;

// Check Stack Size
void checkOverflow() {
  if (sp >= SK_SIZE)
    stackOverflowError();
}
void checkUnderflow() {
  if (sp == 0)
    stackUnderflowError();
}

void push(ObjRef value) {
  checkOverflow();

  stack[sp].isObjRef = true;
  stack[sp].u.objRef = value;
  sp++;
}
void pushInt(int value) {
  checkOverflow();

  stack[sp].isObjRef = false;
  stack[sp].u.number = value;
  sp++;
}

ObjRef pop(void) {
  checkUnderflow();

  sp--;

  if (stack[sp].isObjRef == false)
    noObjRefError();

  return stack[sp].u.objRef;
}

int popint(void) {
  checkUnderflow();

  sp--;

  if (stack[sp].isObjRef == true)
    noIntError();

  return stack[sp].u.number;
}

void asf(int n) {
  pushInt(fp);
  fp = sp;
  sp = sp + n;

  checkOverflow();
}

void rsf(void) {
  sp = fp;
  fp = popint();
}

void pushl(int n) {
  // check if asf where fist
  if (fp == 0)
    noStackFrameAllocatedError();

  push(stack[fp + n].u.objRef);
}

void popl(int n) {
  // check if asf where fist
  if (fp == 0)
    noStackFrameAllocatedError();

  stack[fp + n].isObjRef = true;
  stack[fp + n].u.objRef = pop();
}
void drop(const int n) {
  sp = sp - n;

  if (sp < 0)
    stackUnderflowError();
}

void pushr(void) { push(return_value_register); }

void popr(void) { return_value_register = pop(); }

void printStack(int atFrame) {
  int bottom = 0;

  // if atFrame is true just print Current stack frame
  if (atFrame)
    bottom = fp;

  // If Stack pointer = Frampointer print both
  if (sp == fp)
    pprintf(BOLD, "sp, fp  --->  ");
  else
    pprintf(BOLD, "sp --->  ");

  pprintf(BOLD, "%04d:\txxxx\n", sp);
  for (int i = sp - 1; i >= bottom; i--) {
    // Print Frame Point
    if (i == fp)
      pprintf(BOLD, "fp --->  ");
    else
      printf("\t ");

    pprintf(BOLD, "%04d:\t%d\n", i, stack[i]);
  }
}