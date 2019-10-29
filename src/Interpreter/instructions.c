#include "instructions.h"
#include "../Memory/programMemory.h"
#include "../Memory/stack.h"
#include "../runner/runner.h"
#include "../util/error.h"
#include <stdio.h>

// Print functions
void printInst(char *inst, int ct) { printf("%03d:\t %s\n", ct - 1, inst); }
void printInstValue(char *inst, int value, int ct) {
  printf("%03d:\t %s\t %d\n", ct - 1, inst, value);
}

// Instructions Functions
void execHalt() { haltProg = 1; }
void execPushc(int value) { push(value); }
void execAdd() {
  int num2 = pop();
  int num1 = pop();

  push(num1 + num2);
}
void execSub() {
  int num2 = pop();
  int num1 = pop();

  push(num1 - num2);
}
void execMul() {
  int num2 = pop();
  int num1 = pop();

  push(num1 * num2);
}
void execDiv() {
  // Check if Secound nummber is Zero
  int num2 = pop();
  int num1 = pop();

  if (num2 == 0)
    dividedByZeroError();

  push(num1 / num2);
}
void execMod() {
  int num2 = pop();
  int num1 = pop();
  push(num1 % num2);
}
void execRdint() {
  int myInt;
  scanf("%d", &myInt);
  push(myInt);
}
void execWrint() { printf("%d", pop()); }
void execRdchr() {
  char myChar;
  scanf("%c", &myChar);
  push(myChar);
}
void execWrchr() { printf("%c", pop()); }
void execPushg(int n) {
  if (n < 0 || n == globalVarSize)
    invalidGlobalVarPosition(n);

  push(globalvars[n]);
}
void execPopg(int n) {
  if (n < 0 || n == globalVarSize)
    invalidGlobalVarPosition(n);

  globalvars[n] = pop();
}
void execAsf(int n) { asf(n); }
void execRsf() { rsf(); }
void execPushl(int n) { pushl(n); }
void execPopl(int n) { popl(n); }
void execEq() {
  int n2 = pop();
  int n1 = pop();
  push(n1 == n2);
}
void execNe() {
  int n2 = pop();
  int n1 = pop();
  push(n1 != n2);
}
void execLt() {
  int n2 = pop();
  int n1 = pop();
  push(n1 < n2);
}
void execLe() {
  int n2 = pop();
  int n1 = pop();
  push(n1 <= n2);
}
void execGt() {
  int n2 = pop();
  int n1 = pop();
  push(n1 > n2);
}
void execGe() {
  int n2 = pop();
  int n1 = pop();
  push(n1 >= n2);
}
void execJmp(int n) { pc = n; }
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