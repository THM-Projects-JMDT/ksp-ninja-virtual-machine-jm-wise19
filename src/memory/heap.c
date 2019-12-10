/*
 * heap.c -- All Heap suport Functions
 */

#include "heap.h"
#include "../njvm.h"
#include "../objects/CompoundObject.h"
#include "../util/error.h"
#include "programMemory.h"
#include "stack.h"
#include <bigint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int heapSize;
static int heapMax;
static int hp;
static char *heap;

void initHeap(int size) {
  // Get Bytes
  heapSize = size * K_BYTES;
  heapMax = heapSize / 2;

  heap = malloc(heapSize);

  if (heap == NULL)
    outOfMemoryError();

  hp = 0;
}

void switchHeap(void) {
  hp = (heapMax) % heapSize;
  heapMax = heapMax == heapSize ? 0 : heapSize;
}

int hasNoSpace(const int size) { return hp + size >= heapMax; }

void *unsaveAllocOnHeap(const int size) {
  if (hasNoSpace(size))
    outOfHeapSpaceError();

  // Get next free Memory
  void *out = heap + hp;
  hp += size;

  // TODO init fields with null

  return out;
}

void *allocOnHeap(const int size) {
  // Check if enough space is free
  if (hasNoSpace(size))
    runGC();

  return unsaveAllocOnHeap(size);
}

void runGC(void) {
  printf("GC\n");
  switchHeap();
  copyRootObjects();
  scanHeap();
}

void copyRootObjects(void) {
  for (int i = 0; i < globalVarSize; i++)
    setGlobVar(i, copyObject(getGlobVar(i)));

  for (int i = 0; i < getsp(); i++) {
    StackSlot stackSlot = getStackSlot(i);
    if (stackSlot.isObjRef)
      setObjRef(i, copyObject(getObjRef(i)));
  }
  bip.op1 = copyObject(bip.op1);
  bip.op2 = copyObject(bip.op2);
  bip.res = copyObject(bip.res);
  bip.rem = copyObject(bip.rem);
}

void *copyObject(ObjRef objRef) {
  if (objRef == NULL)
    return objRef;

  if (GET_BROKEN_HEART(objRef))
    return heap + (hp + GET_POINTER(objRef));

  void *newpointer = unsaveAllocOnHeap(GET_TOTAL_SIZE(objRef));

  memcpy(newpointer, objRef, GET_TOTAL_SIZE(objRef));
  objRef->size = hp - GET_TOTAL_SIZE(objRef);
  SET_BROKEN_HEART(objRef);

  return newpointer;
}

void scanHeap() {
  int scan = 0;
  while (scan < hp) {
    ObjRef obj = (ObjRef)(heap + (hp + scan));
    if (obj != NULL && !IS_PRIM(obj)) {
      for (int i = 0; i < GET_SIZE(obj); i++) {
        ObjRef sObj = GET_REF(obj);

        GET_REF(obj) = (ObjRef)copyObject(sObj);
      }
    }
    scan += GET_TOTAL_SIZE(obj);
  }
}