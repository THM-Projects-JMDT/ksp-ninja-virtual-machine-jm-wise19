/*
 * heap.c -- All Heap suport Functions
 */

#include "heap.h"
#include "../njvm.h"
#include "../util/error.h"
#include "programMemory.h"
#include "stack.h"
#include <bigint.h>
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

void copyRootObjects() {
  for (int i = 0; i < globalVarSize; i++) {
    ObjRef objRef = getGlobVar(i);
    setGlobVar(i, copyObject(objRef, objRef->size + sizeof(unsigned int)));
  }
  for (int i = 0; i < getsp(); i++) {
    StackSlot stackSlot = getStackSlot(i);
    if (stackSlot.isObjRef) {
      ObjRef objRef = getObjRef(i);
      setObjRef(i, copyObject(objRef, objRef->size + sizeof(unsigned int)));
    }
  }
  setbip(bip.op1);
  setbip(bip.op2);
  setbip(bip.rem);
  setbip(bip.res);
}

void setbip(ObjRef objRef) {
  objRef = copyObject(objRef, objRef->size + sizeof(unsigned int));
}

void *copyObject(void *pointer, int size) {
  void *newpointer = allocOnHeap(size);

  memcpy(newpointer, pointer, size);

  return newpointer;
}
