#include "interList.h"
#include "../Memory/programMemory.h"
#include "../util/error.h"
#include <stdio.h>

#define GET_INST(i) (((i)&0xFF000000) >> 24)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))
#define GET_IMMEDIATE(i) ((i)&0x00FFFFFF)

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

static void execInst(const unsigned int inst, int count) {
  int opcode = GET_INST(inst);
  int value = SIGN_EXTEND(GET_IMMEDIATE(inst));

  switch (opcode) {
  case halt:
    printf("%03d:\t HALT\n", count);
    break;
  case pushc:
    printf("%03d:\t PUSHC\t %d\n", count, value);
    break;
  case add:
    printf("%03d:\t ADD\n", count);
    break;
  case sub:
    printf("%03d:\t SUB\n", count);
    break;
  case mul:
    printf("%03d:\t MUL\n", count);
    break;
  case div:
    printf("%03d:\t DIV\n", count);
    break;
  case mod:
    printf("%03d:\t MOD\n", count);
    break;
  case rdint:
    printf("%03d:\t RDINT\n", count);
    break;
  case wrint:
    printf("%03d:\t WRINT\n", count);
    break;
  case rdchr:
    printf("%03d:\t RDCHR\n", count);
    break;
  case wrchr:
    printf("%03d:\t WRCHR\n", count);
    break;

  default:
    unknownInstructionError(opcode);
    break;
  }
}

void execList() {
  while (lc < filledMemory) {
    int ir = programMemory[lc];
    lc++;
    execInst(ir, lc - 1);
  }
  lc = 0;
}