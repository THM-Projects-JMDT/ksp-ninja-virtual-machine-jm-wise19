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
static int heapMin;
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
  heapMin = hp;
}

void switchHeap(void) {
  hp = (heapMax) % heapSize;
  heapMin = hp;
  heapMax = heapMax == heapSize ? heapSize / 2 : heapSize;
}

int hasNoSpace(const int size) { return hp + size >= heapMax; }

void *allocOnHeap(const int size) {
  // Check if enough space is free
  if (hasNoSpace(size)) {
    runGC();

    if (hasNoSpace(size))
      outOfHeapSpaceError();
  }

  // Get next free Memory
  void *out = heap + hp;
  hp += size;

  return out;
}

void runGC(void) {
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
    return heap + GET_POINTER(objRef);

  void *newpointer = allocOnHeap(getTotalSize(objRef));

  memcpy(newpointer, objRef, getTotalSize(objRef));
  objRef->size = hp - getTotalSize(objRef);
  SET_BROKEN_HEART(objRef);

  return newpointer;
}

void scanHeap() {
  int scan = heapMin;
  while (scan < hp) {
    ObjRef obj = (ObjRef)(heap + scan);
    if (obj != NULL && !IS_PRIM(obj)) {
      for (int i = 0; i < GET_SIZE(obj); i++) {
        ObjRef sObj = GET_REF(obj);
        GET_REF(obj) = (ObjRef)copyObject(sObj);
      }
    }
    scan += getTotalSize(obj);
  }
}