#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 0
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
// 2 d ARRAY? VLT? STAT DIE 3? UND WAS IS HIER MIT DER FORMATIERUNG LOS^^
unsigned int code0[] = {(PUSHC << 24) | IMMEDIATE(3),
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
unsigned int code1[] = {
    (PUSHC << 24) | IMMEDIATE(-2),   (RDINT << 24), (MUL << 24),
    (PUSHC << 24) | IMMEDIATE(3),    (ADD << 24),   (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE('\n'), (WRCHR << 24), (HALT << 24)};
unsigned int code2[] = {(RDCHR << 24), (WRINT << 24),
                        (PUSHC << 24) | IMMEDIATE('\n'), (WRCHR << 24),
                        (HALT << 24)};
int lenght[3] = {11, 9, 5};
static int pc = 0;
static unsigned int program_memory[20];
static int halt = 0;

// Handle version argument
static void version(const char *myself) {
  printf("Ninja Virtual Machine Version %d (compiled %s, %s)\n", VERSION,
         __DATE__, __TIME__);
}
static void loadprog(const int x) {
  for (int i = 0; i < lenght[x]; i++) {
    if (x == 0)
      program_memory[i] = code0[i];
    if (x == 1)
      program_memory[i] = code1[i];
    if (x == 2)
      program_memory[i] = code2[i];
  }
  while (!halt) {
    int ir = program_memory[pc];
    pc++;
    // AB HIER MUSS NOCH IN EXEC METHoDE AUSGELAGERT WERDEN, ABER WIE? HABE
    // IMMER implicit declaration of function ERROR
    printf("%d\n", ir);
    switch (ir) {
    case (HALT << 24):
      halt = 1;
      break;

    default:
      break;
    }
  }
}

// Handle help argument
static void help(const char *myself) {
  printf("usage: %s [options] ...\n"
         "Options: \n"
         "\t--version \t show version and exit\n"
         "\t--help \t\t show this text and exit\n",
         myself);
}

// Handle an invalid argument
static void invalid(const char *myself, const char *arg) {
  printf("unknown command line argument '%s', try '%s --help'\n", arg, myself);
}

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    // argument version
    if (strcmp(argv[i], "--version") == 0) {
      version(argv[0]);
      exit(0);
    }
    // argument help
    else if (strcmp(argv[i], "--help") == 0) {
      help(argv[0]);
      exit(0);
      // argument prog 1-3
    } else if (strcmp(argv[i], "--prog1") == 0) {
      loadprog(0);
      exit(0);
    } else if (strcmp(argv[i], "--prog2") == 0) {
      loadprog(1);
      exit(0);
    } else if (strcmp(argv[i], "--prog3") == 0) {
      loadprog(2);
      exit(0);
    }
    // handle an invalid argument
    else {
      invalid(argv[0], argv[i]);
      exit(0);
    }
  }

  // Start Message
  printf("Ninja Virtual Machine started\n");

  // Stop Message
  printf("Ninja Virtual Machine stopped\n");
}
