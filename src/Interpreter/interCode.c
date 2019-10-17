#include "interCode.h"
#include "../Memory/programMemory.h"
#include "../Memory/stack.h"
#include "../util/error.h"
#include <stdio.h>

#define GET_INST(i) (((i)&0xFF000000) >> 24)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))
#define GET_IMMEDIATE(i) ((i)&0x00FFFFFF)

static int pc = 0;
static int haltProg = 0;
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
  wrchr
} inst;

// Instructions Functions
static void execHalt() { haltProg = 1; }
static void execPushc(int value) { push(value); }
static void execAdd() { push(pop() + pop()); }
static void execSub() { push(pop() - pop()); }
static void execMul() { push(pop() * pop()); }
static void execDiv() {
  // Check if Secound nummber is Zero
  int num1 = pop();
  int num2 = pop();

  if (num2 == 0)
    dividedByZeroError();

  push(num1 / num2);
}
static void execMod() { push(pop() % pop()); }
static void execRdint() {
  int myInt;
  scanf("%d", &myInt);
  push(myInt);
}
static void execWrint() { printf("%d", pop()); }
static void execRdchr() {
  char myChar;
  scanf("%c", &myChar);
  push(myChar);
}
static void execWrchr() { printf("%c", pop()); }

// Find right Instruction
void execInst(const unsigned int inst) {
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

void execprog() {
  while (!haltProg) {
    if (pc == filledMemory)
      invalidProgrammCodeError();

    int ir = programMemory[pc];
    pc++;
    execInst(ir);
  }
  pc = 0;
}