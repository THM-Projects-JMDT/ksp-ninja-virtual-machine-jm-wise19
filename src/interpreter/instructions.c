#include "instructions.h"
#include "../debugger/debugger.h"
#include "../memory/programMemory.h"
#include "../memory/stack.h"
#include "../runner/runner.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include <stdio.h>

// Print functions
void printInst(char *inst, int ct) {
  pprintf(BOLD, "%04d:\t %s\n", ct - 1, inst);
}
void printInstValue(char *inst, int value, int ct) {
  pprintf(BOLD, "%04d:\t %s\t %d\n", ct - 1, inst, value);
}

// Instructions Functions
void execHalt(void) {
  stopProgramm();
  stopDebugging();
}
void execPushc(int value) { push(value); }
void execAdd(void) {
  int num2 = pop();
  int num1 = pop();

  push(num1 + num2);
}
void execSub(void) {
  int num2 = pop();
  int num1 = pop();

  push(num1 - num2);
}
void execMul(void) {
  int num2 = pop();
  int num1 = pop();

  push(num1 * num2);
}
void execDiv(void) {
  // Check if Secound nummber is Zero
  int num2 = pop();
  int num1 = pop();

  if (num2 == 0)
    dividedByZeroError();

  push(num1 / num2);
}
void execMod(void) {
  int num2 = pop();
  int num1 = pop();

  if (num2 == 0)
    dividedByZeroError();

  push(num1 % num2);
}
void execRdint(void) {
  int myInt;
  scanf("%d", &myInt);
  push(myInt);
}
void execWrint(void) { printf("%d", pop()); }
void execRdchr(void) {
  char myChar;
  scanf("%c", &myChar);
  push(myChar);
}
void execWrchr(void) { printf("%c", pop()); }
void execPushg(int n) { push(getGlobVar(n)); }
void execPopg(int n) { setGlobVar(n, pop()); }
void execAsf(int n) { asf(n); }
void execRsf(void) { rsf(); }
void execPushl(int n) { pushl(n); }
void execPopl(int n) { popl(n); }
void execEq(void) {
  int n2 = pop();
  int n1 = pop();
  push(n1 == n2);
}
void execNe(void) {
  int n2 = pop();
  int n1 = pop();
  push(n1 != n2);
}
void execLt(void) {
  int n2 = pop();
  int n1 = pop();
  push(n1 < n2);
}
void execLe(void) {
  int n2 = pop();
  int n1 = pop();
  push(n1 <= n2);
}
void execGt(void) {
  int n2 = pop();
  int n1 = pop();
  push(n1 > n2);
}
void execGe(void) {
  int n2 = pop();
  int n1 = pop();
  push(n1 >= n2);
}
void execJmp(int n) { changePC(n); }
void execBrf(int n) {
  int b = pop();
  if (b == 0) {
    execJmp(n);
  }
}
void execBrt(int n) {
  int b = pop();
  if (b == 1) {
    execJmp(n);
  }
}
void execCall(int n) {}
void execRet() {}
void execDrop(int n) {}
void execPushr() {}
void execDropr() {}
void execDup() {}