#ifndef BLOODHOUND_H
#define BLOODHOUND_H
#include <stdlib.h>
#include <inttypes.h>

void **head;
void **tail = head;
uint64_t check = UINT64_MAX>>1;

typedef struct{
  uint64_t map;
  void **nose;
} hound;

int bloodhound(){
  if (head == tail){
    head = calloc(64, sizeof(void*));
    if (head == NULL){
      return -1;
    }
    hound one;
    one->nose = head;
    one.map = 1;
    tail = one->nose[63];
    return 1;
  } else { 
  //chech if full and add tail if necessary
  }
  return 0;
}

int blood(int size){
  //run through and see if anything is bleedinf
  return 0;
}

#endif
