#include "programMemory.h"
#include "../debugger/debugger.h"
#include "../njvm.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <support.h>

static unsigned int *programMemory;
static ObjRef *globalvars;
int memorySize;
int globalVarSize;

// get Program Memory at pos
unsigned int getInst(const int pos) {
  if (pos < 0 || pos == memorySize)
    invalidProgrammCodeError();

  return programMemory[pos];
}

// check global vars pos
static void checkGlobalVars(const int pos) {
  if (pos < 0 || pos == globalVarSize)
    invalidGlobalVarPositionError(pos);
}

// get global var at Pos
ObjRef getGlobVar(const int pos) {
  checkGlobalVars(pos);
  return globalvars[pos];
}

// set global var at Pos
void setGlobVar(const int pos, const ObjRef val) {
  checkGlobalVars(pos);
  globalvars[pos] = val;
}

// free Program Memory
void freeProgMem(void) {
  free(programMemory);
  memorySize = 0;
}

// free Global vars
void freeGlobVars(void) {
  free(globalvars);
  globalVarSize = 0;
}

// Load programs
void loadprog(const char *path) {
  // Read File
  FILE *fp;
  char format[4];
  unsigned int header[3];
  fp = fopen(path, "r");

  if (fp == NULL)
    invalidPathError(path);

  // read format
  if (fread(format, sizeof(char), 4, fp) != 4)
    invalidFileSizeError();

  // Verify the format identifier
  if (strncmp(format, "NJBF", 4) != 0)
    invalidFileIdentifierError();

  // read header (version, instructions count, global vars count)
  if (fread(header, sizeof(int), 3, fp) != 3)
    invalidFileSizeError();

  // Verify that the version Number matches the current VM's version number
  if (header[0] != version)
    invalidCodeVersionError(header[0], version);

  // Reading Instructions
  programMemory = (unsigned int *)malloc(header[1] * sizeof(unsigned int));

  // Check if Memory was Allocated
  if (programMemory == NULL)
    outOfMemoryError();

  if (fread(programMemory, sizeof(unsigned int), header[1], fp) != header[1])
    invalidFileSizeError();

  memorySize = header[1];

  // Setting amount of global Varibales
  globalVarSize = header[2];
  globalvars = (ObjRef *)malloc(globalVarSize * sizeof(int));

  // Check if Memory was Allocated
  if (globalvars == NULL)
    outOfMemoryError();

  // Close and Check if file Close is possible
  if (fclose(fp) == EOF)
    cantCloseCodeFileError();

  // If debug mode is on Print File loaded Message
  if (debug)
    showFileLoaded(memorySize, globalVarSize);
}

void printglobalvars(void) {
  if (globalVarSize == 0)
    pprintf(BOLD, "No global Variables pressent\n");

  for (int i = 0; i < globalVarSize; i++) {
    pprintf(BOLD, "data[%04d]:     %p\n", i, globalvars[i]);
  }
}