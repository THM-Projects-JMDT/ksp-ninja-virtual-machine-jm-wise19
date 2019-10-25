#include "interpreter.h"
#include "../util/error.h"
#include "instructions.h"
#include <stdio.h>

#define GET_INST(i) (((i)&0xFF000000) >> 24)
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
  popl
} inst;

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
    dpMode ? printInstValue("wrchr", value, counter) : execPushl(value);
    break;
  case popl:
    dpMode ? printInstValue("popl", value, counter) : execPopl(value);
    break;
  default:
    unknownInstructionError(opcode);
    break;
  }
}