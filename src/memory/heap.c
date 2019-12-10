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
  printf("%d: %d, ", heapSize, heapMax);
  hp = heapMax;
  heapMax = heapMax == heapSize ? 0 : heapSize;
  printf("%d\n", heapMax);
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

void runGC(void) {
  switchHeap();
  copyRootObjects();
}

void copyRootObjects() {
  for (int i = 0; i < globalVarSize; i++) {
    ObjRef objRef = getGlobVar(i);
    setGlobVar(i, copyObject(objRef));
  }
  for (int i = 0; i < getsp(); i++) {
    StackSlot stackSlot = getStackSlot(i);
    if (stackSlot.isObjRef) {
      ObjRef objRef = getObjRef(i);
      setObjRef(i, copyObject(objRef));
    }
  }
  setbip(bip.op1);
  setbip(bip.op2);
  setbip(bip.rem);
  setbip(bip.res);
}

void setbip(ObjRef objRef) { objRef = copyObject(objRef); }

void *copyObject(ObjRef objRef) {
  void *newpointer = allocOnHeap(objRef->size + sizeof(unsigned int));

  memcpy(newpointer, objRef, objRef->size + sizeof(unsigned int));
  objRef->size = hp - objRef->size + sizeof(unsigned int);
  SET_BROKEN_HEART(objRef);

  return newpointer;
}

void scan() {
  int scan = 0;
  while (scan < hp) {
    ObjRef obj = (ObjRef)heap + (hp + scan);
    if (!IS_PRIM(obj)) {
      for (int i = 0; i < GET_SIZE(obj); i++) {
        ObjRef sObj = GET_REF(obj);

        if (!GET_BROKEN_HEART(sObj))
          copyObject(sObj, sObj->size);

        obj->data[i] = hp + GET_POINTER(sObj);
      }
    }
    scan += GET_SIZE(obj) + sizeof(unsigned int);
  }
}