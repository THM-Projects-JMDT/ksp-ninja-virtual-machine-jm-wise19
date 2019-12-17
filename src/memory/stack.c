/*
 * stack.c -- All Stack suport Functions
 */

#include "stack.h"
#include "../njvm.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include <stdio.h>
#include <stdlib.h>
#include <support.h>

static int stackSlots = 0;
static int sp = 0;
static int fp = 0;

static StackSlot *stack;
static ObjRef return_value_register;

void initStack(int size) {
  // Get Bytes
  size *= K_BYTES;

  stack = malloc(size);

  if (stack == NULL)
    outOfMemoryError();

  // Calculate stack Slots
  stackSlots = size / sizeof(StackSlot);
}

void freeStack() { free(stack); }

ObjRef getReturnReg(void) { return return_value_register; }
void setReturnReg(ObjRef objRef) { return_value_register = objRef; }

int getStackSize(void) { return stackSlots; }

// Check Stack Size
void checkOverflow() {
  if (sp >= stackSlots)
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

void pushNoRef(int value) {
  checkOverflow();

  stack[sp].isObjRef = false;
  stack[sp].u.number = value;
  sp++;
}

ObjRef pop(void) {
  checkUnderflow();

  sp--;

  if (!stack[sp].isObjRef)
    popNoObjRefError();

  return stack[sp].u.objRef;
}

// get stackslot at Pos
StackSlot getStackSlot(const int pos) { return stack[pos]; }

// get ObjRef at Pos
ObjRef getObjRef(const int pos) { return stack[pos].u.objRef; }

// set stackslot at Pos
void setObjRef(const int pos, const ObjRef val) { stack[pos].u.objRef = val; }

int getsp() { return sp; }

int popNoRef(void) {
  checkUnderflow();

  sp--;

  if (stack[sp].isObjRef)
    noIntError();

  return stack[sp].u.number;
}

void asf(int n) {
  pushNoRef(fp);
  fp = sp;

  // init local vars with null
  for (int i = 0; i < n; i++) {
    push(NULL);
  }
}

void rsf(void) {
  sp = fp;
  fp = popNoRef();
}

void pushl(int n) {
  // check if asf where fist
  if (fp == 0)
    noStackFrameAllocatedError();

  if (!stack[fp + n].isObjRef)
    localNoObjRefError(n);

  push(stack[fp + n].u.objRef);
}

void popl(int n) {
  // check if asf where fist
  if (fp == 0)
    noStackFrameAllocatedError();

  if (!stack[fp + n].isObjRef)
    localNoObjRefError(n);

  stack[fp + n].u.objRef = pop();
}
void drop(const int n) {
  sp = sp - n;

  if (sp < 0)
    stackUnderflowError();
}

void pushr(void) {
  push(return_value_register);
  // return_value_register = NULL;
}

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

  pprintf(BOLD, "%04d:\t(xxxxxx)\txxxx\n", sp);
  for (int i = sp - 1; i >= bottom; i--) {
    // Print Frame Point
    if (i == fp)
      pprintf(BOLD, "fp --->  ");
    else
      printf("\t ");

    pprintf(BOLD, "%04d:\t", i);

    if (stack[i].isObjRef)
      pprintf(BOLD, "(objref)\t%p\n", stack[i].u.objRef);
    else
      pprintf(BOLD, "(number)\t%d\n", stack[i].u.number);
  }
}