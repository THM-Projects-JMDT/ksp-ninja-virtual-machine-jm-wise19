#include "stack.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include <stdio.h>
#define SK_SIZE 10000

static int sp = 0;
static int fp = 0;

static int stack[SK_SIZE];

void push(int value) {
  if (sp == SK_SIZE)
    stackOverflowError();
  stack[sp] = value;
  sp++;
}

int pop(void) {
  if (sp == 0)
    stackUnderflowError();
  sp--;
  return stack[sp];
}

void asf(int n) {
  push(fp);
  fp = sp;
  sp = sp + n;

  if (sp == SK_SIZE)
    stackOverflowError();
}

void rsf(void) {
  sp = fp;
  fp = pop();
}

void pushl(int n) {
  // check if asf where fist
  if (fp == 0)
    noStackFrameAllocatedError();

  // check if n in not negativ
  if (fp < 0)
    invalidLocalVarPositionError(n);

  push(stack[fp + n]);
}

void popl(int n) {
  // check if asf where fist
  if (fp == 0)
    noStackFrameAllocatedError();

  // check if n in not negativ
  if (fp < 0)
    invalidLocalVarPositionError(n);

  stack[fp + n] = pop();
}

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