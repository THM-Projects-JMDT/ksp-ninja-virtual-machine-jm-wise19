#include "programMemory.h"
#include "../njvm.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int *programMemory;
int *globalvars;
int memorySize;
int globalVarSize;

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
  if (strcmp(format, "NJBF") != 0)
    invalidFileIdentifierError();

  // read header (version, instructions count, global vars count)
  if (fread(header, sizeof(int), 3, fp) != 3)
    invalidFileSizeError();

  // Verify that the version Number matches the current VM's version number
  if (header[0] != version)
    invalidCodeVersion(header[0], version);

  // Reading Instructions
  programMemory = (unsigned int *)malloc(header[1] * sizeof(unsigned int));

  if (fread(programMemory, sizeof(unsigned int), header[1], fp) != header[1])
    invalidFileSizeError();

  memorySize = header[1];

  // Setting amount of global Varibales
  globalVarSize = header[2];
  globalvars = (int *)malloc(globalVarSize * sizeof(int));

  // TODO vtl check int
  fclose(fp);
}