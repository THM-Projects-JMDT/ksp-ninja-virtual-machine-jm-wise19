#include "interList.h"
#include "../Memory/programMemory.h"
#include "../util/error.h"
#include <stdio.h>

#define GET_INST(i) (((i)&0xFF000000) >> 24)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))
#define GET_IMMEDIATE(i) ((i)&0x00FFFFFF)

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
    printf("HALT\n");
    break;
  case pushc:
    printf("PUSHC\t %d\n", value);
    break;
  case add:
    printf("ADD\n");
    break;
  case sub:
    printf("SUB\n");
    break;
  case mul:
    printf("MUL\n");
    break;
  case div:
    printf("DIV\n");
    break;
  case mod:
    printf("MOD\n");
    break;
  case rdint:
    printf("RDINT\n");
    break;
  case wrint:
    printf("WRINT\n");
    break;
  case rdchr:
    printf("RDCHR\n");
    break;
  case wrchr:
    printf("WRCHR\n");
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