#ifndef PRINT_H
#define PRINT_H

#include "Numerical.h"

void print_binary(struct Array* string);
struct Array* represent_binary(struct Array* string);
struct Array* represent_string(struct Array* binary);
char represent_bit_at(struct Array* string, int index);
void print_bool_array(bool* array, int rowLength, int length);
void print_strings(struct Array** strings, int length);
struct Array* int_to_string(int number);
int num_tens(int number);
void print_new_line();

void print_binary(struct Array* string) {
  struct Array* binaryString = represent_binary(string);
  printf("%s", binaryString->array);
}

struct Array* represent_binary(struct Array* string) {
  int length = string->length;
  int binaryLength = 8*length;
  struct Array* binaryString = init_array_malloc(binaryLength);
  for(int i = 0; i < binaryLength; i++) {
    binaryString->array[i] = represent_bit_at(string, i);
  }
  return binaryString;
}

struct Array* represent_string(struct Array* binary) {
  int binaryLength = binary->length;
  int stringLength = chars_required_for_n_bits(binaryLength);
  struct Array* string = init_array_malloc(stringLength);
  for(int i = 0; i < binaryLength; i++) {
    char currentBit = binary->array[i];
    if(currentBit == '1') {
      set_bit_to(string, i, 1);
    } else {
      set_bit_to(string, i, 0);
    }
  }
  return string;
}

char represent_bit_at(struct Array* string, int index) {
  int stringIndex = index/8;
  int charIndex = index%8;
  char mask = 1<<charIndex;
  if(0 == (string->array[stringIndex] & mask)) {
    return '0';
  }
  return '1';
}

void print_bool_array(bool* array, int rowLength, int length) {
  for(int i = 0; i < length; i++) {
    int value = array[i]? 1: 0;
    printf("%d ", value);
    if(i % rowLength == rowLength-1) {
      print_new_line();
    }
  }
}

void print_strings(struct Array** strings, int length) {
  for(int i = 0; i < length; i++) {
    struct Array* intString = int_to_string(i+1);
    printf("\n%s. %s", intString->array, strings[i]->array);
  }
}

struct Array* int_to_string(int number) {
  int numTens = num_tens(number);
  char* string = malloc(numTens * sizeof(int) + sizeof(char));
  sprintf(string, "%d", number);
  return init_array(string, numTens);
}

int num_tens(int number) {
  if(number == 0) {
    return 1;
  }
  int numTens = 0;
  while(number > 0) {
    numTens++;
    number /= 10;
  }
  return numTens;
}

void print_new_line() {
  printf("\n");
}

#endif
