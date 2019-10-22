#include "Interpreter/interpreter.h"
#include "Memory/programMemory.h"
#include "util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 1

// Handle version argument
static void version(const char *myself) {
  printf("Ninja Virtual Machine Version %d (compiled %s, %s)\n", VERSION,
         __DATE__, __TIME__);
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
  char *progFile;

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
    }
    // handle an invalid argument
    else if ((argv[i][0] == '-' && argv[i][1] == '-')) {
      invalid(argv[0], argv[argc - 1]);
      exit(0);
      // Save file path
    } else {
      // If more than 1 file path -> error
      if (progFile != NULL)
        moreThanOneInputError();

      progFile = argv[i];
    }
  }

  // Start Message
  printf("Ninja Virtual Machine started\n");

  // loadprog(progFile);
  // execList();
  // execprog();

  // Stop Message
  printf("Ninja Virtual Machine stopped\n");
}
