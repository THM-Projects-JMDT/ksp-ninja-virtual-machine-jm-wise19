#include "instructions.h"
#include "../debugger/debugger.h"
#include "../memory/programMemory.h"
#include "../memory/stack.h"
#include "../runner/runner.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include <bigint.h>
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
void execPushc(int value) {
  bigFromInt(value);
  push(bip.res);
}
void execAdd(void) {
  bip.op2 = pop();
  bip.op1 = pop();

  pushInt(bip.res);
}
void execSub(void) {
  bip.op2 = pop();
  bip.op1 = pop();

  pushInt(bip.res);
}
void execMul(void) {
  bip.op2 = pop();
  bip.op1 = pop();

  pushInt(bip.res);
}
void execDiv(void) {
  // Check if Secound nummber is Zero
  int num2 = popInt();
  int num1 = popInt();

  if (num2 == 0)
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
  int myInt = 0;
  scanf("%d", &myInt);
  bigFromInt(myInt);
  push(bip.res);
}
void execWrint(void) { printf("%d", popInt()); }
void execRdchr(void) {
  char myChar;
  scanf("%c", &myChar);
  bigFromInt(myChar);
  push(bip.res);
}
void execWrchr(void) { printf("%c", popInt()); }
void execPushg(int n) { push(getGlobVar(n)); }
void execPopg(int n) { setGlobVar(n, pop()); }
void execAsf(int n) { asf(n); }
void execRsf(void) { rsf(); }
void execPushl(int n) { pushl(n); }
void execPopl(int n) { popl(n); }
void execEq(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  execPushc(bigCmp() == 0);
}
void execNe(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  execPushc(bigCmp() != 0);
}
void execLt(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  execPushc(bigCmp() < 0);
}
void execLe(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  execPushc(bigCmp() <= 0);
}
void execGt(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  execPushc(bigCmp() > 0);
}
void execGe(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  execPushc(bigCmp() >= 0);
}
void execJmp(int n) { changePC(n); }
void execBrf(int n) {
  bip.op1 = pop();
  int b = bigToInt();
  if (!b)
    changePC(n);
}
void execBrt(int n) {
  bip.op1 = pop();
  int b = bigToInt();
  if (b)
    changePC(n);
}
void execCall(int n) {
  pushNoRef(getPC());
  changePC(n);
}
void execRet(void) { changePC(popNoRef()); }
void execDrop(int n) { drop(n); }
void execPushr(void) { pushr(); }
void execPopr(void) { popr(); }
void execDup(void) {
  int i = popInt();
  pushInt(i);
  pushInt(i);
}