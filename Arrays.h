#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdlib.h>

#include "Numerical.h"

struct Array;
struct Array {
  char* array;
  int length;
};

struct Array* init_array_malloc(int _length);
struct Array* init_array_calloc(int _length);
struct Array* init_array(char* _array, int _length);

char get_bit_at(struct Array* container, int index);
void set_bit_to(struct Array* container, int index, char bit);
void flip_bit_at(struct Array* container, int index);

struct Array* init_array_malloc(int _length) {
  struct Array* initialized = malloc(sizeof(struct Array));
  initialized->array = malloc((_length + 1) * sizeof(char));
  initialized->array[_length] = '\0';
  initialized->length = _length;
  return initialized;
}

struct Array* init_array_calloc(int _length) {
  struct Array* initialized = malloc(sizeof(struct Array));
  initialized->array = calloc(_length + 1, sizeof(char));
  initialized->array[_length] = '\0';
  initialized->length = _length;
  return initialized;
}

struct Array* init_array(char* _array, int _length) {
  struct Array* initialized = malloc(sizeof(struct Array));
  initialized->array = _array;
  initialized->length = _length;
  return initialized;
}

char get_bit_at(struct Array* container, int index) {
  int arrayIndex = index/8;
  int charIndex = index%8;
  char mask = 1<<charIndex;
  char bitReturning = (container->array[arrayIndex] & mask) >> charIndex;
  return bitReturning;
}

void set_bit_to(struct Array* container, int index, char bit) {
  int arrayIndex = index/8;
  int charIndex = index%8;
  char mask = bit<<charIndex;
  char bitLocation = 1<<charIndex;
  char maskOpposite = bitLocation ^ mask;
  char flippedMaskOpposite = ~maskOpposite;
  container->array[arrayIndex] |= mask;
  container->array[arrayIndex] &= flippedMaskOpposite;
}

void flip_bit_at(struct Array* container, int bitIndex) {
  char currentBit = get_bit_at(container, bitIndex);
  char oppositeBit = opposite_bit(currentBit);
  set_bit_to(container, bitIndex, oppositeBit);
}

#endif
