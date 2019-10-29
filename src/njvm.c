#include "Memory/programMemory.h"
#include "runner/runner.h"
#include "util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int version = 3;

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
  char *progFile;

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
      // argument prog 1-3
    }
    // handle an invalid argument
    else if ((argv[i][0] == '-' && argv[i][1] == '-')) {
      invalidArgumentError(argv[0], argv[i]);
      // Save file path
    } else {
      // If more than 1 file path -> error
      if (progFile != NULL)
        moreThanOneInputError(argv[0]);

      progFile = argv[i];
    }
  }

  // check if progFile was Specified
  if (progFile == NULL)
    noPathError(argv[0]);

  // Start Message
  printf("Ninja Virtual Machine started\n");
  loadprog(progFile);
  execList();
  execprog();

  // TODO maybe somewhere else
  free(programMemory);
  memorySize = 0;
  free(globalvars);
  globalVarSize = 0;

  // Stop Message
  printf("Ninja Virtual Machine stopped\n");
}
