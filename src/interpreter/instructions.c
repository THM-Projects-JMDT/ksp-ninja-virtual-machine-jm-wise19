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
void execPushc(int value) { push(createObjRefInt(value)); }
void execAdd(void) {
  ObjRef num2 = pop();
  ObjRef num1 = pop();
  push(createObjRefInt((intptr_t)num2 + (intptr_t)num1));
}
void execSub(void) {
  ObjRef num2 = pop();
  ObjRef num1 = pop();

  push(createObjRefInt((intptr_t)num1 - (intptr_t)num2));
}
void execMul(void) {
  ObjRef num2 = pop();
  ObjRef num1 = pop();

  push(createObjRefInt((intptr_t)num1 * (intptr_t)num2));
}
void execDiv(void) {
  // Check if Secound nummber is Zero
  ObjRef num2 = pop();
  ObjRef num1 = pop();

  if ((intptr_t)num2 == 0)
    dividedByZeroError();

  push(createObjRefInt((intptr_t)num1 / (intptr_t)num2));
}
void execMod(void) {
  ObjRef num2 = pop();
  ObjRef num1 = pop();

  if (num2 == 0)
    dividedByZeroError();

  push(createObjRefInt((intptr_t)num1 % (intptr_t)num2));
}
void execRdint(void) {
  int myInt;
  scanf("%d", &myInt);
  push(createObjRefInt(myInt));
}
void execWrint(void) { printf("%ld", (intptr_t)pop()); }
void execRdchr(void) {
  char myChar;
  scanf("%c", &myChar);
  push(createObjRefChar(myChar));
}
void execWrchr(void) { printf("%c", (char)pop()); }
void execPushg(int n) { push(createObjRefInt(getGlobVar(n))); }
void execPopg(int n) { setGlobVar(n, (intptr_t)pop()); }
void execAsf(int n) { asf(n); }
void execRsf(void) { rsf(); }
void execPushl(int n) { pushl(n); }
void execPopl(int n) { popl(n); }
void execEq(void) {
  ObjRef n2 = pop();
  ObjRef n1 = pop();
  push((intptr_t)n1 == (intptr_t)n2 ? createObjRefBool(true)
                                    : createObjRefBool(false));
}
void execNe(void) {
  ObjRef n2 = pop();
  ObjRef n1 = pop();
  push((intptr_t)n1 != (intptr_t)n2 ? createObjRefBool(true)
                                    : createObjRefBool(false));
}
void execLt(void) {
  ObjRef n2 = pop();
  ObjRef n1 = pop();
  push((intptr_t)n1 < (intptr_t)n2 ? createObjRefBool(true)
                                   : createObjRefBool(false));
}
void execLe(void) {
  ObjRef n2 = pop();
  ObjRef n1 = pop();
  push((intptr_t)n1 <= (intptr_t)n2 ? createObjRefBool(true)
                                    : createObjRefBool(false));
}
void execGt(void) {
  ObjRef n2 = pop();
  ObjRef n1 = pop();
  push((intptr_t)n1 > (intptr_t)n2 ? createObjRefBool(true)
                                   : createObjRefBool(false));
}
void execGe(void) {
  ObjRef n2 = pop();
  ObjRef n1 = pop();
  push((intptr_t)n1 >= (intptr_t)n2 ? createObjRefBool(true)
                                    : createObjRefBool(false));
}
void execJmp(int n) { changePC(n); }
void execBrf(int n) {
  bool b = (bool)pop();
  if (!b)
    changePC(n);
}
void execBrt(int n) {
  bool b = (bool)pop();
  if (b)
    changePC(n);
}
void execCall(int n) {
  pushInt(getPC());
  changePC(n);
}
void execRet(void) { changePC(popint()); }
void execDrop(int n) { drop(n); }
void execPushr(void) { pushr(); }
void execPopr(void) { popr(); }
void execDup(void) {
  ObjRef i = pop();
  push(i);
  push(i);
}