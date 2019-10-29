#include "stack.h"
#include "../util/error.h"

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

int pop() {
  if (sp == 0)
    stackUnderflowError();
  sp--;
  return stack[sp];
}

void asf(int n) {
  push(fp);
  fp = sp;
  sp = sp + n;
}

void rsf() {
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