/*
 * stack.h -- All Heap suport Functions
 */

#include "../njvm.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>

static int heapSize;
static char *heap;

void initHeap(int size) {
  // Get Bytes
  heapSize = size * 1024;

  heap = malloc(heapSize);

  if (heap == NULL)
    outOfMemoryError();
}
