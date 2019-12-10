/*
 * heap.h -- All Heap suport Functions
 */

#ifndef NJCM_HEAP_H_INCLUDED
#define NJCM_HEAP_H_INCLUDED

void initHeap(int size);
void switchHeap(void);
void *allocOnHeap(const int size);

#endif