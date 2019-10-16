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
unsigned int code1[][3] = {
    {(PUSHC << 24) | IMMEDIATE(3), (PUSHC << 24) | IMMEDIATE(4), (ADD << 24),
     (PUSHC << 24) | IMMEDIATE(10), (PUSHC << 24) | IMMEDIATE(6), (SUB << 24),
     (MUL << 24), (WRINT << 24), (PUSHC << 24) | IMMEDIATE(10), (WRCHR << 24),
     (HALT << 24)},
    {(PUSHC << 24) | IMMEDIATE(-2), (RDINT << 24), (MUL << 24),
     (PUSHC << 24) | IMMEDIATE(3), (ADD << 24), (WRINT << 24),
     (PUSHC << 24) | IMMEDIATE('\n'), (WRCHR << 24), (HALT << 24)},
    {(RDCHR << 24), (WRINT << 24), (PUSHC << 24) | IMMEDIATE('\n'),
     (WRCHR << 24), (HALT << 24)}};

// Handle version argument
static void version(const char *myself) {
  printf("Ninja Virtual Machine Version %d (compiled %s, %s)\n", VERSION,
         __DATE__, __TIME__);
}
static void prog(const int i) {}

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
    } else if (strcmp(argv[i], "--prog1") == 0) {
      prog(1);
      exit(0);
    } else if (strcmp(argv[i], "--prog2") == 0) {
      prog(2);
      exit(0);
    } else if (strcmp(argv[i], "--prog3") == 0) {
      prog(3);
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