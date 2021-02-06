#ifndef NUMERICAL_H
#define NUMERICAL_H

#include <stdbool.h>
#include <stdio.h>

int bits_required_to_secure(int numberOfArrays);
int chars_required_for_n_bits(int numBits);
int log_base_2(int number);
char xor(char a, char b);
char opposite_bit(char bit);
bool power_of_two(int number);
int bits_set(int number);
int string_to_integer(char* string);
bool is_digit(char checkIfDigit);
int char_to_integer(char digit);

int bits_required_to_secure(int numberOfArrays) {
  int bitsRequiredToTrackOverallParity = 1;
  return log_base_2(numberOfArrays) + bitsRequiredToTrackOverallParity;
}

int chars_required_for_n_bits(int numBits) {
  return (numBits + 7) / 8;
}

int log_base_2(int number) {
  for(int i = 0; i < 31; i++) {
    if(1<<i == number) {
      return i;
    }
  }
  printf("non power of 2 %d passed as number into log_base_2() in SecureBits.h\n", number);
  return -1;
}

char xor(char a, char b) {
  //assumes char a and char b each have at most one activated bit, and that the
  //activated bit is the least significant bit
  return a ^ b;
}

char opposite_bit(char bit) {
  return 1 ^ bit;
}

bool power_of_two(int number) {
  return bits_set(number) == 1;
}

int bits_set(int number) {
  int mask = 1;
  int bitsSet = number & mask;
  for(int i = 1; i < 32; i++) {
    mask <<= 1;
    bitsSet += (mask & number) >> i;
  }
  return bitsSet;
}

int string_to_integer(char* string) {
  char endOfString = '\0';
  int pointer = 0;
  int tally = 0;
  while(is_digit(string[pointer])) {
    tally *= 10;
    tally += char_to_integer(string[pointer++]);
  }
  return tally;
}

bool is_digit(char checkIfDigit) {
  return checkIfDigit >= '0' && checkIfDigit <= '9';
}

int char_to_integer(char digit) {
  return digit - '0';
}

#endif
