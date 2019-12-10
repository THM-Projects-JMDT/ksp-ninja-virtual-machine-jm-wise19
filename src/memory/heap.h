/*
 * heap.h -- All Heap suport Functions
 */

#ifndef NJCM_HEAP_H_INCLUDED
#define NJCM_HEAP_H_INCLUDED

#include <support.h>

void initHeap(int size);
void switchHeap(void);
void *allocOnHeap(const int size);
void *copyObject(void *pointer, int size);
void setbip(ObjRef objRef);

#endif