/*
 * instructions.c -- All Functions that handle the VM  Instructions
 */

#include "instructions.h"
#include "../debugger/debugger.h"
#include "../memory/heap.h"
#include "../memory/programMemory.h"
#include "../memory/stack.h"
#include "../njvm.h"
#include "../objects/CompoundObject.h"
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

  // If gcstats -> run gc at the end
  if (gcstats)
    runGC();
}
void execPushc(int value) {
  bigFromInt(value);
  push(bip.res);
}
void execAdd(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  bigAdd();

  push(bip.res);
}
void execSub(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  bigSub();

  push(bip.res);
}
void execMul(void) {
  bip.op2 = pop();
  bip.op1 = pop();
  bigMul();

  push(bip.res);
}
void execDiv(void) {
  bip.op2 = pop();
  bip.op1 = pop();

  bigDiv();
  push(bip.res);
}
void execMod(void) {
  bip.op2 = pop();
  bip.op1 = pop();

  bigDiv();
  push(bip.rem);
}
void execRdint(void) {
  bigRead(stdin);
  push(bip.res);
}
void execWrint(void) {
  bip.op1 = pop();
  bigPrint(stdout);
}
void execRdchr(void) {
  char myChar;
  scanf("%c", &myChar);
  bigFromInt(myChar);
  push(bip.res);
}
void execWrchr(void) {
  bip.op1 = pop();
  printf("%c", bigToInt());
}
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

  if (!bigToInt())
    changePC(n);
}
void execBrt(int n) {
  bip.op1 = pop();

  if (bigToInt())
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
  ObjRef objRef = pop();
  push(objRef);
  push(objRef);
}
void execNew(int n) { push(newCompoundObject(n)); }
void execGetf(int i) {
  ObjRef obj = pop();

  checkIsCompundObject(obj);

  push(GET_REF(obj));
}
void execPutf(int i) {
  ObjRef value = pop();
  ObjRef obj = pop();

  checkIsCompundObject(obj);

  GET_REF(obj) = value;
}
void execNewa(void) {
  bip.op1 = pop();
  push(newCompoundObject(bigToInt()));
}
void execGetfa(void) {
  bip.op1 = pop();
  int i = bigToInt();

  ObjRef obj = pop();

  checkIsCompundObject(obj);
  checkIndex(obj, i);

  push(GET_REF(obj));
}
void execPutfa(void) {
  ObjRef value = pop();

  bip.op1 = pop();
  int i = bigToInt();

  ObjRef obj = pop();

  checkIsCompundObject(obj);
  checkIndex(obj, i);

  GET_REF(obj) = value;
}
void execGetsz(void) {
  ObjRef obj = pop();

  if (obj == NULL)
    ilegalNilRefecenceError();

  // If is CompoundObject -> push size
  if (!IS_PRIM(obj))
    execPushc(GET_SIZE(obj));
  else
    execPushc(-1);
}
void execPushn(void) { push(NULL); }
void execRefeq(void) {
  ObjRef objRef2 = pop();
  ObjRef objRef1 = pop();
  bigFromInt(objRef2 == objRef1);
  push(bip.res);
}
void execRefne(void) {
  ObjRef objRef2 = pop();
  ObjRef objRef1 = pop();
  bigFromInt(objRef2 != objRef1);
  push(bip.res);
}