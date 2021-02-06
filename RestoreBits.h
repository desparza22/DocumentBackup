#ifndef RESTOREBITS_H
#define RESTOREBITS_H

#include <stdbool.h>

#include "Arrays.h"
#include "SecureBits3.h"

void restore_words(struct Array** arrays, struct Array* originalSecurity, int numWords);
int incorrect_word(struct Array* originalSecurity, struct Array* currentSecurity, int securityStart, int numWords);
bool compare_bit_at(struct Array* a, struct Array* b, int bitIndex);

void restore_words(struct Array** arrays, struct Array* originalSecurity, int numWords) {
  int wordLength = arrays[0]->length;
  int bitsInWord = wordLength * 8;
  int bitsRequiredToSecure = bits_required_to_secure(numWords);
  struct Array* currentSecurity = secure_words(arrays, numWords);
  for(int bitIndex = 0; bitIndex < bitsInWord; bitIndex++) {
    int securityStart = bitIndex * bitsRequiredToSecure;
    int incorrectWordIndex = incorrect_word(originalSecurity, currentSecurity, securityStart, numWords);
    if(incorrectWordIndex != -1) {
      struct Array* incorrectWord = arrays[incorrectWordIndex];
      flip_bit_at(incorrectWord, bitIndex);
    }
  }
}

int incorrect_word(struct Array* originalSecurity, struct Array* currentSecurity, int securityStart, int numWords) {
  int securityLength = originalSecurity->length;
  if(compare_bit_at(originalSecurity, currentSecurity, securityStart)) {
    return -1;
  }
  int wrongWord = 0;
  int wordIndexAdding = numWords/2;
  for(int i = securityStart+1; i < securityStart + securityLength; i++) {
    if(compare_bit_at(originalSecurity, currentSecurity, i)) {
      wrongWord += wordIndexAdding;
    }
    wordIndexAdding /= 2;
  }
  return wrongWord;
}

bool compare_bit_at(struct Array* a, struct Array* b, int bitIndex) {
  return get_bit_at(a, bitIndex) == get_bit_at(b, bitIndex);
}

#endif
