#include "debugCmds.h"
#include "../../util/prettyPrint.h"
#include "../debugger.h"
#include "debugCmdDef.h"
#include "string.h"
#include <stdio.h>

#define CMD_DELIMITER " "

static debugCmd *cmds;
static int cmdsCount;

// change Actual Commands
void setActCmds(int count, debugCmd newCmds[], char *command) {
  cmds = newCmds;
  cmdsCount = count;
  setSubPromt(command);
}

// tests if subcommand was entered directly
void checkSubAsArg(char *input) {
  char *subCmd;
  strtok(input, CMD_DELIMITER);
  subCmd = strtok(NULL, CMD_DELIMITER);

  if (subCmd != NULL)
    findCmd(subCmd);
}

// Find Command and run Command
void findCmd(char *input) {
  int hasSub;

  for (int i = 0; i < cmdsCount; i++) {
    if (cmds[i].check(input, cmds[i].command)) {
      hasSub = cmds[i].hasSubCmd;
      cmds[i].action(cmds[i].command, input);

      // If Cmd with no Sub -> print next instruction
      if (!hasSub)
        printNextInst();
      // else check sub Cmd
      else
        checkSubAsArg(input);

      break;
    }
  }
}

// Print Actual Commands
void printCmds(void) {
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