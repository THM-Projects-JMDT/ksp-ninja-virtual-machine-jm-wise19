/*
 * stack.h -- All Heap suport Functions
 */

#include "../njvm.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>

static int heapSize;
static int hp;
static char *heap;

void initHeap(int size) {
  // Get Bytes
  heapSize = size * 1024;

  heap = malloc(heapSize);

  if (heap == NULL)
    outOfMemoryError();

  hp = 0;
}

void *allocOnHeap(const int size) {
  void *out = &heap[hp];
  hp += size;

  if (hp >= heapSize / 2)
    outOfHeapSpaceError();

  // TODO init fields with null

  return out;
}