#include "error.h"
#include <stdio.h>
#include <stdlib.h>

static void vmError(int errc, char *em) {
  // Change the Text Color to Red
  fprintf(stderr, "\033[0;31m");

  fprintf(stderr, "An error occurred:\n");

  // Reset Text Color
  fprintf(stderr, "\033[0m");

  // Print error
  fprintf(stderr, "%s\n", em);

  exit(errc);
}

void stackOverflowError(int line) { vmError(101, "stackOverflowError"); }
void emptyStackError(int line) { vmError(102, "emtyStackError"); }