/*
 * heap.c -- All Heap suport Functions
 */

#include "../njvm.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int heapSize;
static int hp;
static char *heap;

void initHeap(int size) {
  // Get Bytes
  heapSize = size * K_BYTES;

  heap = malloc(heapSize);

  if (heap == NULL)
    outOfMemoryError();

  hp = 0;
}

void *allocOnHeap(const int size) {
  // Check if enough space is free
  if (hp + size >= heapSize / 2)
    outOfHeapSpaceError();

  // Get next free Memory
  void *out = heap + hp;
  hp += size;

  // TODO init fields with null

  return out;
}

void *copyObject(void *pointer, int size) {
  void *newpointer = allocOnHeap(size);

  memcpy(newpointer, pointer, size);

  return newpointer;
}
