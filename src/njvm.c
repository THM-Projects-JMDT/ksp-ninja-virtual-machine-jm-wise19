/*
 * njvm.c -- Vm Start and argument functions
 */

#include "debugger/debugger.h"
#include "memory/programMemory.h"
#include "memory/stack.h"
#include "runner/runner.h"
#include "util/error.h"
#include "util/prettyPrint.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int version = 7;
int stacksize = 64;
int heapsize = 8192;
int debug = 0;

// Handle version argument
static void displayVersion(const char *myself) {
  pprintf(BOLD, "Ninja Virtual Machine Version %d (compiled %s, %s)\n", version,
          __DATE__, __TIME__);
}

// TODO vtl in own File
// Handle help argument
static void help(const char *myself) {
  // Print usage
  pprintf(BOLD, "usage: ");
  printf("%s [options] [code file]\n", myself);

  // Print Options
  pprintf(BOLD, "Options: \n");
  pprintf(BOLD, "\t--debug");
  printf("\t\t start debug mode\n");
  pprintf(BOLD, "\t--version");
  printf("\t show version and exit\n");
  pprintf(BOLD, "\t--help");
  printf("\t\t show this text and exit\n");

  // Print Error Codes
  pprintf(BOLD, "Error Codes:\n");
  pprintf(BOLD, "\t1x: ");
  printf("Argument Errors\n");
  pprintf(BOLD, "\t2x: ");
  printf("File read Errors\n");
  pprintf(BOLD, "\t3x: ");
  printf("Memory Errors\n");
  pprintf(BOLD, "\t4x: ");
  printf("Stack Errors\n");
  pprintf(BOLD, "\t5x: ");
  printf("Runtime Errors\n");
}
void checkArgument(char *argv, char *myself) {
  if (!isdigit(argv[0]))
    argumentNoInteger(argv, myself);
}

int main(int argc, char *argv[]) {
  int filePos = -1;

  // check arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--stack") == 0) {
      if (i + 1 == argc)
        missingArgument(argv[i], argv[0]);

      checkArgument(argv[i + 1], argv[0]);
      stacksize = atoi(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "--heap") == 0) {
      if (i + 1 == argc)
        missingArgument(argv[i], argv[0]);

      checkArgument(argv[i + 1], argv[0]);
      heapsize = atoi(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "--version") == 0) {
      displayVersion(argv[0]);
      exit(0);
    } else if (strcmp(argv[i], "--help") == 0) {
      help(argv[0]);
      exit(0);
    } else if (strcmp(argv[i], "--debug") == 0) {
      debug = 1;
    }
    // invalid argument
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
  // init stack
  initStack(stacksize);
  // load programm in Memory
  loadprog(argv[filePos]);

  printf("Ninja Virtual Machine started\n");

  // if debug mode is offline start Programm
  if (debug)
    startDebug();
  else
    execprog();

  // TODO maybe somewhere else
  freeProgMem();
  freeGlobVars();

  printf("Ninja Virtual Machine stopped\n");
}