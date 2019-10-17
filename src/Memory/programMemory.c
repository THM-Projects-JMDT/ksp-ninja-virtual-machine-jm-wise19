#include "programMemory.h"

#define MEMORY_SIZE 20

#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10
#define IMMEDIATE(x) ((x)&0x00FFFFFF)

unsigned int programMemory[MEMORY_SIZE];
int filledMemory = 0;

// Program definitions

// prog1
static unsigned int code0[] = {(PUSHC << 24) | IMMEDIATE(3),
                               (PUSHC << 24) | IMMEDIATE(4),
                               (ADD << 24),
                               (PUSHC << 24) | IMMEDIATE(10),
                               (PUSHC << 24) | IMMEDIATE(6),
                               (SUB << 24),
                               (MUL << 24),
                               (WRINT << 24),
                               (PUSHC << 24) | IMMEDIATE(10),
                               (WRCHR << 24),
                               (HALT << 24)};

// prog2
static unsigned int code1[] = {
    (PUSHC << 24) | IMMEDIATE(-2),   (RDINT << 24), (MUL << 24),
    (PUSHC << 24) | IMMEDIATE(3),    (ADD << 24),   (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE('\n'), (WRCHR << 24), (HALT << 24)};

// prog3
static unsigned int code2[] = {(RDCHR << 24), (WRINT << 24),
                               (PUSHC << 24) | IMMEDIATE('\n'), (WRCHR << 24),
                               (HALT << 24)};

static int lenght[3] = {11, 9, 5};

// Load programs
void loadprog(const int x) {
  for (int i = 0; i < lenght[x]; i++) {
    if (x == 0)
      programMemory[i] = code0[i];
    if (x == 1)
      programMemory[i] = code1[i];
    if (x == 2)
      programMemory[i] = code2[i];
  }

  filledMemory = lenght[x];
}