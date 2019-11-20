#include "instructions.h"
#include "../debugger/debugger.h"
#include "../memory/programMemory.h"
#include "../memory/stack.h"
#include "../runner/runner.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include <stdint.h>
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
void execPushc(int value) { pushInt(value); }
void execAdd(void) {
  int num2 = popInt();
  int num1 = popInt();

  pushInt(num1 + num2);
}
void execSub(void) {
  int num2 = popInt();
  int num1 = popInt();

  pushInt(num1 - num2);
}
void execMul(void) {
  int num2 = popInt();
  int num1 = popInt();

  pushInt(num1 * num2);
}
void execDiv(void) {
  // Check if Secound nummber is Zero
  int num2 = popInt();
  int num1 = popInt();

  if ((intptr_t)num2 == 0)
    dividedByZeroError();

  pushInt(num1 / num2);
}
void execMod(void) {
  int num2 = popInt();
  int num1 = popInt();

  if (num2 == 0)
    dividedByZeroError();

  pushInt(num1 % num2);
}
void execRdint(void) {
  int myInt;
  scanf("%d", &myInt);
  pushInt(myInt);
}
void execWrint(void) { printf("%d", popInt()); }
void execRdchr(void) {
  char myChar;
  scanf("%c", &myChar);
  pushInt(myChar);
}
void execWrchr(void) { printf("%c", popInt()); }
void execPushg(int n) { push(getGlobVar(n)); }
void execPopg(int n) { setGlobVar(n, pop()); }
void execAsf(int n) { asf(n); }
void execRsf(void) { rsf(); }
void execPushl(int n) { pushl(n); }
void execPopl(int n) { popl(n); }
void execEq(void) {
  int n2 = popInt();
  int n1 = popInt();
  pushInt(n1 == n2);
}
void execNe(void) {
  int n2 = popInt();
  int n1 = popInt();
  pushInt(n1 != n2);
}
void execLt(void) {
  int n2 = popInt();
  int n1 = popInt();
  pushInt(n1 < n2);
}
void execLe(void) {
  int n2 = popInt();
  int n1 = popInt();
  pushInt(n1 <= n2);
}
void execGt(void) {
  int n2 = popInt();
  int n1 = popInt();
  pushInt(n1 > n2);
}
void execGe(void) {
  int n2 = popInt();
  int n1 = popInt();
  pushInt(n1 >= n2);
}
void execJmp(int n) { changePC(n); }
void execBrf(int n) {
  int b = popInt();
  if (!b)
    changePC(n);
}
void execBrt(int n) {
  int b = popInt();
  if (b)
    changePC(n);
}
void execCall(int n) {
  pushInt(getPC());
  changePC(n);
}
void execRet(void) { changePC(popInt()); }
void execDrop(int n) { drop(n); }
void execPushr(void) { pushr(); }
void execPopr(void) { popr(); }
void execDup(void) {
  int i = popInt();
  pushInt(i);
  pushInt(i);
}