#ifndef NJCM_COMPOUNDOBJECT_H_INCLUDED
#define NJCM_COMPOUNDOBJECT_H_INCLUDED

#include <Support.h>
#include <stdio.h>

#define GET_SIZE(s) ((s) & (0xFFFFFFFF >> 1))
#define Get_MSB(s) (((s) & (0x80000000)) >> 31)
#define CP_OBj_VALUE(o) (((ObjRef *)((o)->data))[n])

ObjRef newCompoundObject(int numObjRefs);
void checkIsCompundObject(ObjRef obj);

#endif