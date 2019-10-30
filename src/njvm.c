#include "Memory/programMemory.h"
#include "runner/runner.h"
#include "util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int version = 3;
int debug = 0;

// Handle version argument
static void displayVersion(const char *myself) {
  printf("Ninja Virtual Machine Version %d (compiled %s, %s)\n", version,
         __DATE__, __TIME__);
}

// Handle help argument
static void help(const char *myself) {
  printf("\033[1musage:\033[0m %s [options] ... [code file]\n"
         "\033[1mOptions:\033[0m \n"
         "\t\033[1m--version\033[0m \t show version and exit\n"
         "\t\033[1m--help\033[0m \t\t show this text and exit\n"
         "\033[1mError Codes:\033[0m \n"
         "\t\033[1m1x:\033[0m Argument Errors codes\n"
         "\t\033[1m2x:\033[0m File read Errors\n"
         "\t\033[1m3x:\033[0m Memory Errors\n"
         "\t\033[1m4x:\033[0m Stack Errors\n"
         "\t\033[1m5x:\033[0m Runtime Errors\n",
         myself);
}

int main(int argc, char *argv[]) {
  int filePos = -1;

  for (int i = 1; i < argc; i++) {
    // argument version
    if (strcmp(argv[i], "--version") == 0) {
      displayVersion(argv[0]);
      exit(0);
    }
    // argument help
    else if (strcmp(argv[i], "--help") == 0) {
      help(argv[0]);
      exit(0);
    }
    // argument debug
    else if (strcmp(argv[i], "--debug") == 0) {
      debug = 1;
    }

    // handle an invalid argument
    else if (argv[i][0] == '-') {
      invalidArgumentError(argv[0], argv[i]);
      // Save file path
    } else {
      // If more than 1 file path -> error
      if (filePos > -1)
        moreThanOneInputError(argv[0]);

      filePos = i;
    }
  }

  // check if progFile was Specified
  if (filePos == -1)
    noPathError(argv[0]);

  // load programm in Memory
  loadprog(argv[filePos]);

  // Start Message
  printf("Ninja Virtual Machine started\n");

  // TODO remove
  // execList();

  // if debug mode is offline start Programm
  if (debug) {
    // TODO
  } else
    execprog();

  // TODO maybe somewhere else
  freeProgMem();
  freeGlobVars();

  // Stop Message
  printf("Ninja Virtual Machine stopped\n");
}
