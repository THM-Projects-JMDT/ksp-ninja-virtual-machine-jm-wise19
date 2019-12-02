/*
 * interpreter.c -- All functions that determine which instruction to execute
 */

#include "interpreter.h"
#include "../util/error.h"
#include "instructions.h"
#include <stdio.h>

#define GET_INST(i) ((i) >> 24)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))
#define GET_IMMEDIATE(i) ((i)&0x00FFFFFF)

// Instruction definition (starts with 0)
typedef enum inst {
  halt,
  pushc,
  add,
  sub,
  mul,
  div,
  mod,
  rdint,
  wrint,
  rdchr,
  wrchr,
  pushg,
  popg,
  asf,
  rsf,
  pushl,
  popl,
  eq,
  ne,
  lt,
  le,
  gt,
  ge,
  jmp,
  brf,
  brt,
  call,
  ret,
  drop,
  pushr,
  popr,
  dup,
  new,
  getf,
  putf,
  newa,
  getfa,
  putfa,
  getsz,
  pushn,
  refeq,
  refne,
} Inst;

// Find right Instruction
void execInst(const unsigned int inst, const int counter, const int dpMode) {
  int opcode = GET_INST(inst);
  int value = SIGN_EXTEND(GET_IMMEDIATE(inst));

  // If Display Mode(dpMode) == 1 -> Just Print Instructions
  switch (opcode) {
  case halt:
    dpMode ? printInst("halt", counter) : execHalt();
    break;
  case pushc:
    dpMode ? printInstValue("pushc", value, counter) : execPushc(value);
    break;
  case add:
    dpMode ? printInst("add", counter) : execAdd();
    break;
  case sub:
    dpMode ? printInst("sub", counter) : execSub();
    break;
  case mul:
    dpMode ? printInst("mul", counter) : execMul();
    break;
  case div:
    dpMode ? printInst("div", counter) : execDiv();
    break;
  case mod:
    dpMode ? printInst("mod", counter) : execMod();
    break;
  case rdint:
    dpMode ? printInst("rdint", counter) : execRdint();
    break;
  case wrint:
    dpMode ? printInst("wrint", counter) : execWrint();
    break;
  case rdchr:
    dpMode ? printInst("rdchr", counter) : execRdchr();
    break;
  case wrchr:
    dpMode ? printInst("wrchr", counter) : execWrchr();
    break;
  case pushg:
    dpMode ? printInstValue("pushg", value, counter) : execPushg(value);
    break;
  case popg:
    dpMode ? printInstValue("popg", value, counter) : execPopg(value);
    break;
  case asf:
    dpMode ? printInstValue("asf", value, counter) : execAsf(value);
    break;
  case rsf:
    dpMode ? printInst("rsf", counter) : execRsf();
    break;
  case pushl:
    dpMode ? printInstValue("pushl", value, counter) : execPushl(value);
    break;
  case popl:
    dpMode ? printInstValue("popl", value, counter) : execPopl(value);
    break;
  case eq:
    dpMode ? printInst("eq", counter) : execEq();
    break;
  case ne:
    dpMode ? printInst("ne", counter) : execNe();
    break;
  case lt:
    dpMode ? printInst("lt", counter) : execLt();
    break;
  case le:
    dpMode ? printInst("le", counter) : execLe();
    break;
  case gt:
    dpMode ? printInst("gt", counter) : execGt();
    break;
  case ge:
    dpMode ? printInst("ge", counter) : execGe();
    break;
  case jmp:
    dpMode ? printInstValue("jmp", value, counter) : execJmp(value);
    break;
  case brf:
    dpMode ? printInstValue("brf", value, counter) : execBrf(value);
    break;
  case brt:
    dpMode ? printInstValue("brt", value, counter) : execBrt(value);
    break;
  case call:
    dpMode ? printInstValue("call", value, counter) : execCall(value);
    break;
  case ret:
    dpMode ? printInst("ret", counter) : execRet();
    break;
  case drop:
    dpMode ? printInstValue("drop", value, counter) : execDrop(value);
    break;
  case pushr:
    dpMode ? printInst("pushr", counter) : execPushr();
    break;
  case popr:
    dpMode ? printInst("popr", counter) : execPopr();
    break;
  case dup:
    dpMode ? printInst("dup", counter) : execDup();
    break;
  case new:
    dpMode ? printInstValue("new", value, counter) : execNew(value);
    break;
  case getf:
    dpMode ? printInstValue("getf", value, counter) : execGetf(value);
    break;
  case putf:
    dpMode ? printInstValue("putf", value, counter) : execPutf(value);
    break;
  case newa:
    dpMode ? printInst("newa", counter) : execNewa();
    break;
  case getfa:
    dpMode ? printInst("getfa", counter) : execGetfa();
    break;
  case putfa:
    dpMode ? printInst("putfa", counter) : execPutfa();
    break;
  case getsz:
    dpMode ? printInst("getsz", counter) : execGetsz();
    break;
  case pushn:
    dpMode ? printInst("pushn", counter) : execPushn();
    break;
  case refeq:
    dpMode ? printInst("refeq", counter) : execRefeq();
    break;
  case refne:
    dpMode ? printInst("refne", counter) : execRefne();
    break;
  default:
    unknownInstructionError(opcode);
    break;
  }
}