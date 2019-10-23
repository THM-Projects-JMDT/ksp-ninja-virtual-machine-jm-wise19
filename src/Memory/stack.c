#include "stack.h"
#include "../util/error.h"

#define SK_SIZE 10000

static int sp = 0;
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