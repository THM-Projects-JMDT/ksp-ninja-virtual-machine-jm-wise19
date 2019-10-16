#include "stack.h"
#include "../util/error.h"

#define SK_SIZE 20

static int sp = 0;
static int stack[SK_SIZE];

void pushc(int value) {
  if (sp == SK_SIZE)
    stackOverflowError();
  stack[sp] = value;
  sp++;
}

int pop() {
  if (sp == 0)
    emptyStackError();
  sp--;
  return stack[sp];
}