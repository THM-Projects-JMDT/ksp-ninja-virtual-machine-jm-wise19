/*
 * stack.h -- All Heap suport Functions
 */

#include "../njvm.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>

static char **heap;

void initHeap(int size) {
  // Get Bytes
  size = size * 1024;

  heap = malloc(size);

  if (heap == NULL)
    outOfMemoryError();
}
