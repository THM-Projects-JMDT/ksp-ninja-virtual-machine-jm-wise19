#include "debugInput.h"
#include "../../util/prettyPrint.h"
#include "../debugger.h"
#include "debugCmdDef.h"
#include <stdio.h>

#define INPUT_SIZE 20

static debugCmd *cmds;
static int cmdsCount;
static int runDebug = 1;

void stopDebugging() { runDebug = 0; }

void setActCmds(int count, debugCmd newCmds[], char *command) {
  cmds = newCmds;
  cmdsCount = count;
  setSubPromt(command);
}

void findCmd(char *input) {
  for (int i = 0; i < cmdsCount; i++) {
    if (cmds[i].command[0] == input[0]) {
      cmds[i].action(cmds[i].command);
      break;
    }
  }
}

void printCmds() {
  // Set Format
  printMsPromt();
  setFormat(stdout, BOLD);
  setFormat(stdout, BLUE);

  // Print Commands
  for (int i = 0; i < cmdsCount; i++) {
    printf("%s", cmds[i].command);

    if (i != cmdsCount - 1)
      printf(", ");
  }

  printf("?\n");

  // Reset Format
  setFormat(stdout, RESET_FORMAT);
}

void cmdLoop() {
  while (runDebug) {
    char input[INPUT_SIZE];

    printCmds(cmdsCount, cmds);

    // Read input
    printPromt();
    fgets(input, INPUT_SIZE, stdin);

    // check input
    if (input == NULL)
      continue;

    findCmd(input);
  }
}