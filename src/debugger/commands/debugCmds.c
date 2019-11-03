#include "debugCmds.h"
#include "../../util/prettyPrint.h"
#include "../debugger.h"
#include "debugCmdDef.h"
#include <stdio.h>

static debugCmd *cmds;
static int cmdsCount;

// change Actual Commands
void setActCmds(int count, debugCmd newCmds[], char *command) {
  cmds = newCmds;
  cmdsCount = count;
  setSubPromt(command);
}

// Find Command and run Command
void findCmd(char *input) {
  int hasSub;

  for (int i = 0; i < cmdsCount; i++) {
    if (cmds[i].command[0] == input[0]) {
      hasSub = cmds[i].hasSubCmd;
      cmds[i].action(cmds[i].command);

      // If command not has Sub Commands print next Instruction
      if (!hasSub)
        printNextInst();
      break;
    }
  }
}

// Print Actual Commands
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