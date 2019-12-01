#ifndef NJCM_COMPOUNDOBJECT_H_INCLUDED
#define NJCM_COMPOUNDOBJECT_H_INCLUDED

#include <Support.h>
#include <stdio.h>

#define MSB (1 << (8 * sizeof(unsigned int) - 1))
#define GET_SIZE(obj) ((obj)->size & ~MSB)
#define IS_PRIM(obj) (((obj)->size & MSB) == 0)
#define GET_REF(obj) (((ObjRef *)((obj)->data))[i])

ObjRef newCompoundObject(int numObjRefs);
void checkIsCompundObject(ObjRef obj);

#endif