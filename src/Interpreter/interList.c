#include "interList.h"
#include "Memory/programMemory.h"

static int haltList = 0;
static int lc = 0;

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
  wrchr
} inst;

static void execInst(const unsigned int inst) {
  int opcode = GET_INST(inst);
  int value = SIGN_EXTEND(GET_IMMEDIATE(inst));

  switch (opcode) {
  case halt:
    execHalt();
    break;
  case pushc:
    execPushc(value);
    break;
  case add:
    execAdd();
    break;
  case sub:
    execSub();
    break;
  case mul:
    execMul();
    break;
  case div:
    execDiv();
    break;
  case mod:
    execMod();
    break;
  case rdint:
    execRdint();
    break;
  case wrint:
    execWrint();
    break;
  case rdchr:
    execRdchr();
    break;
  case wrchr:
    execWrchr();
    break;

  default:
    unknownInstructionError(opcode);
    break;
  }
}

void execList() {
  while (!haltList) {
    if (lc == filledMemory)
      invalidProgrammCodeError();

    int ir = programMemory[lc];
    lc++;
    execInst(ir);
  }
  lc = 0;
}