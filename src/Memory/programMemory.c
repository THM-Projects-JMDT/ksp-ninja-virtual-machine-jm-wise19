#include "programMemory.h"
#include "../njvm.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int programMemory[200];
int filledMemory = 0;

// Load programs
void loadprog(const char *path)
{
  // check if path was Specified
  if (path == NULL)
    noPathError();

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
  unsigned int memmory[header[1]];
  if (fread(memmory, sizeof(int), header[1], fp) != header[1])
    invalidFileSizeError();
  for (int i = 0; i < header[1]; i++)
  {
    programMemory[i] = memmory[i];
    printf("%d\n", memmory[0]);
  }

  printf("format: %s\n", format);
  printf("version: %d\n", header[0]);
  printf("inst: %d\n", header[1]);
  printf("vars: %d\n", header[2]);
  // TODO vtl check int
  fclose(fp);
}