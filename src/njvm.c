#include "Interpreter/interCode.h"
#include "Memory/programMemory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 0

// Handle version argument
static void version(const char *myself) {
  printf("Ninja Virtual Machine Version %d (compiled %s, %s)\n", VERSION,
         __DATE__, __TIME__);
}

// Handle help argument
static void help(const char *myself) {
  printf("usage: %s [options] ...\n"
         "Options: \n"
         "\t--prog1 \t run program 1\n"
         "\t--prog2 \t run program 2\n"
         "\t--prog3 \t run program 3\n"
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
      break;
    } else if (strcmp(argv[i], "--prog2") == 0) {
      loadprog(1);
      break;
    } else if (strcmp(argv[i], "--prog3") == 0) {
      loadprog(2);
      break;
    }
    // handle an invalid argument
    else {
      invalid(argv[0], argv[i]);
      exit(0);
    }
  }

  // Start Message
  printf("Ninja Virtual Machine started\n");

  execprog();

  // Stop Message
  printf("Ninja Virtual Machine stopped\n");
}
