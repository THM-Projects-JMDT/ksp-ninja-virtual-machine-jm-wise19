/*
 * compoundObject.h -- Compound Object support Functions
 */

#ifndef NJCM_COMPOUNDOBJECT_H_INCLUDED
#define NJCM_COMPOUNDOBJECT_H_INCLUDED

#include <stdio.h>
#include <support.h>

#define MSB (1 << (8 * sizeof(unsigned int) - 1))
#define GET_SIZE(obj) ((obj)->size & ~MSB)
#define IS_PRIM(obj) (((obj)->size & MSB) == 0)
#define GET_REF(obj) (((ObjRef *)((obj)->data))[i])

ObjRef newCompoundObject(int numObjRefs);
void checkIsCompundObject(ObjRef obj);
void checkIndex(ObjRef obj, int i);
int getTotalSize(ObjRef obj);

#endif