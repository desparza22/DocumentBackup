#ifndef SECUREBITS3_H
#define SECUREBITS3_H

#include <stdbool.h>
#include <stdio.h>

#include "Arrays.h"
#include "Numerical.h"
#include "ParityTree.h"

struct Array* secure_words(struct Array** arrays, int numberOfArrays);
struct Array* secure_chunk(struct Array** arrays, int numberOfArrays, int distanceIntoWord);
int secure_chunk_copy_into(struct Array** arrays, int length, struct Array* copyInto, int startCopyingAt, int distanceIntoWord);

struct Array* secure_words(struct Array** arrays, int numberOfArrays) {
  int wordLength = arrays[0]->length;
  int securityBitLength = bits_required_to_secure(numberOfArrays) * wordLength * 8;
  int securityCharLength = chars_required_for_n_bits(securityBitLength);
  struct Array* security = init_array_malloc(securityCharLength);
  int copyIntoFrom = 0;
  for(int i = 0; i < wordLength*8; i++) {
    copyIntoFrom = secure_chunk_copy_into(arrays, numberOfArrays, security, copyIntoFrom, i);
  }
  return security;
}

//format: overall, every other half, every other quarter, etc...
struct Array* secure_chunk(struct Array** arrays, int numberOfArrays, int distanceIntoWord) {
  int wordLength = arrays[0]->length;
  int securityBitLength = bits_required_to_secure(numberOfArrays) * wordLength;
  int securityCharLength = chars_required_for_n_bits(securityBitLength);
  struct Array* security = init_array_malloc(securityCharLength);
  int startOfArray = 0;
  secure_chunk_copy_into(arrays, numberOfArrays, security, startOfArray, distanceIntoWord);
  return security;
}

int secure_chunk_copy_into(struct Array** arrays, int numberOfArrays, struct Array* copyInto, int startCopyingAt, int distanceIntoWord) {
  struct ParityTreeNode* head = init_ParityTreeNode(arrays, 0, numberOfArrays, distanceIntoWord);
  for(int sectionLength = numberOfArrays; sectionLength > 0; sectionLength /= 2) {
    char parityOfSection = parity_of_section(head, sectionLength);
    set_bit_to(copyInto, startCopyingAt++, parityOfSection);
  }
  deallocate_ParityTreeNode(head);
  return startCopyingAt;
}

#endif
