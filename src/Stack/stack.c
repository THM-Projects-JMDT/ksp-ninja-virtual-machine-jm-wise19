#include "stack.h"

#define SK_SIZE 20

static int sp = 0;
static int stack[SK_SIZE];

void pushc(int value) {
  if (sp == SK_SIZE)
    ; // TODO
  stack[sp] = value;
  sp++;
}

int pop() {
  if (sp == 0)
    ; // TODO ERROR
  sp--;
  return stack[sp];
}