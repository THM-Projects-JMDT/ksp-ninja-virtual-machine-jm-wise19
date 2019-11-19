#ifndef NJCM_OBJ_H_INCLUDED
#define NJCM_OBJ_H_INCLUDED

typedef struct {
  unsigned int size;     /* byte count of payload data */
  unsigned char data[1]; /* payload data , size as needed */
} * ObjRef;

#endif