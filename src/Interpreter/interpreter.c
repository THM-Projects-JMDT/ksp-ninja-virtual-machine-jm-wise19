#include "interpreter.h"
#include "../Memory/programMemory.h"
#include "../Memory/stack.h"
#include "../util/error.h"
#include <stdio.h>

#define GET_INST(i) (((i)&0xFF000000) >> 24)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))
#define GET_IMMEDIATE(i) ((i)&0x00FFFFFF)

static int pc = 0;
static int lc = 0;
static int haltProg = 0;
// Instruction definition (starts with 0)
typedef enum inst
{
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

// Instructions Functions
static void execHalt() { haltProg = 1; }
static void execPushc(int value) { push(value); }
static void execAdd() { push(pop() + pop()); }
static void execSub() { push(pop() - pop()); }
static void execMul() { push(pop() * pop()); }
static void execDiv()
{
  // Check if Secound nummber is Zero
  int num1 = pop();
  int num2 = pop();

  if (num2 == 0)
    dividedByZeroError();

  push(num1 / num2);
}
static void execMod() { push(pop() % pop()); }
static void execRdint()
{
  int myInt;
  scanf("%d", &myInt);
  push(myInt);
}
static void execWrint() { printf("%d", pop()); }
static void execRdchr()
{
  char myChar;
  scanf("%c", &myChar);
  push(myChar);
}
static void execWrchr() { printf("%c", pop()); }

// Print functions
static void printInst(char *inst) { printf("%03d:\t %s\n", lc - 1, inst); }
static void printInstValue(char *inst, int value)
{
  printf("%03d:\t %s\t %d\n", lc - 1, inst, value);
}

// Find right Instruction
static void execInst(const unsigned int inst, int dpMode)
{
  int opcode = GET_INST(inst);
  int value = SIGN_EXTEND(GET_IMMEDIATE(inst));

  // If Display Mode(dpMode) == 1 -> Just Print Instructions
  switch (opcode)
  {
  case halt:
    dpMode ? printInst("halt") : execHalt();
    break;
  case pushc:
    dpMode ? printInstValue("pushc", value) : execPushc(value);
    break;
  case add:
    dpMode ? printInst("add") : execAdd();
    break;
  case sub:
    dpMode ? printInst("sub") : execSub();
    break;
  case mul:
    dpMode ? printInst("mul") : execMul();
    break;
  case div:
    dpMode ? printInst("div") : execDiv();
    break;
  case mod:
    dpMode ? printInst("mod") : execMod();
    break;
  case rdint:
    dpMode ? printInst("rdint") : execRdint();
    break;
  case wrint:
    dpMode ? printInst("wrint") : execWrint();
    break;
  case rdchr:
    dpMode ? printInst("rdchr") : execRdchr();
    break;
  case wrchr:
    dpMode ? printInst("wrchr") : execWrchr();
    break;

  default:
    unknownInstructionError(opcode);
    break;
  }
}

// Display all Instructions in Memory
void execList()
{
  while (lc < filledMemory)
  {
    int ir = programMemory[lc];
    lc++;
    execInst(ir, 1);
  }
  lc = 0;
}

// Run Programm in Memory
void execprog()
{
  while (!haltProg)
  {
    if (pc == filledMemory)
      invalidProgrammCodeError();

    int ir = programMemory[pc];
    pc++;
    execInst(ir, 0);
  }
  pc = 0;
}