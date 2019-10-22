#include "programMemory.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int programMemory[20];
int filledMemory = 0;

// Load programs
void loadprog(const int x) {
  FILE *fp;
  fp = fopen("bin/test.txt", "r");
  if (fp == NULL)
    printf("error\n");
  else {
    printf("geht\n");
  }

  exit(0);
}