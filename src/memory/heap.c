/*
 * heap.c -- All Heap suport Functions
 */

#include "heap.h"
#include "../njvm.h"
#include "../objects/CompoundObject.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"
#include "programMemory.h"
#include "stack.h"
#include <bigint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int heapSize;
static int heapMax;
static int heapMin;
static int hp;
static char *heap;
static bool gc;

static HeapStats heapStats;

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

int getHeapSize(void) { return heapSize; }

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

  // if not run a gc and gcstats -> Collect Heap Stats
  if (!gc && gcstats) {
    heapStats.cObjCount++;
    heapStats.cObjByte += size;
  }

  return out;
}

void runGC(void) {
  gc = true;

  switchHeap();
  copyRootObjects();
  scanHeap();

  // If gcpurge -> clear unused heap area
  if (gcpurge)
    memset(heap + ((heapMax) % heapSize), 0, heapSize / 2);

  // If gcStats -> print stats
  if (gcstats) {
    printStats();

    // Reset heap stats
    resetStats();
  }

  gc = false;
}

void copyRootObjects(void) {
  for (int i = 0; i < globalVarSize; i++)
    setGlobVar(i, copyObject(getGlobVar(i)));

  for (int i = 0; i < getsp(); i++) {
    StackSlot stackSlot = getStackSlot(i);
    if (stackSlot.isObjRef)
      setObjRef(i, copyObject(getObjRef(i)));
  }

  setReturnReg(copyObject(getReturnReg()));

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

  // if gcstats -> Collect heap Stats
  if (gcstats) {
    heapStats.mObjCount++;
    heapStats.mObjByte += getTotalSize(objRef);
  }

  // Set Forwart Pointer and flag
  objRef->size = hp - getTotalSize(objRef);
  SET_BROKEN_HEART(objRef);

  return newpointer;
}

void scanHeap() {
  int scan = heapMin;
  while (scan < hp) {
    ObjRef obj = (ObjRef)(heap + scan);
    if (!IS_PRIM(obj)) {
      for (int i = 0; i < GET_SIZE(obj); i++) {
        GET_REF(obj) = (ObjRef)copyObject(GET_REF(obj));
      }
    }
    scan += getTotalSize(obj);
  }
}

void printStats(void) {
  pprintf(BLUE, "======\n");

  pprintf(YELLOW, "Garbage Collector:\n");
  pprintf(BOLD, "\t%d Objects (%d bytes) allocated since last collection\n",
          heapStats.cObjCount, heapStats.cObjByte);
  pprintf(BOLD, "\t%d objects (%d bytes) copied during this collection\n",
          heapStats.mObjCount, heapStats.mObjByte);
  pprintf(BOLD, "\t%d of %d bytes free after this collection\n", heapMax - hp,
          heapSize / 2);

  pprintf(BLUE, "======\n");
}

void resetStats(void) {
  heapStats.cObjByte = 0;
  heapStats.cObjCount = 0;
  heapStats.mObjByte = 0;
  heapStats.mObjCount = 0;
}