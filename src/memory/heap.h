/*
 * heap.h -- All Heap suport Functions
 */

#ifndef NJCM_HEAP_H_INCLUDED
#define NJCM_HEAP_H_INCLUDED

#include "../objects/CompoundObject.h"
#include <support.h>

#define BROKEN_HEART (1 << (sizeof(unsigned int) * 8 - 2))
#define SET_BROKEN_HEART(obj) ((obj)->size = (obj)->size | BROKEN_HEART)
#define GET_BROKEN_HEART(obj)                                                  \
  (((obj)->size & BROKEN_HEART) >> (sizeof(unsigned int) * 8 - 2))
#define GET_POINTER(obj) ((obj)->size & ~(BROKEN_HEART | MSB))

void initHeap(int size);
void switchHeap(void);
void *allocOnHeap(const int size);
void *copyObject(void *pointer, int size);
void copyRootObjects();
void setbip(ObjRef objRef);

#endif