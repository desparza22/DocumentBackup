#ifndef SECUREBITS2_H
#define SECUREBITS2_H

#include <stdbool.h>
#include <stdio.h>

struct ParityTreeNode;

struct ParityTreeNode {
  bool parity;
  int start;
  int length;
  struct ParityTreeNode* left;
  struct ParityTreeNode* right;
};

//form security information
bool* secure_chunk(bool* array, int length);
void secure_chunk_copy_into(bool* array, int length, bool* copyInto, int startCopyingAt);
bool parity_of_section(struct ParityTreeNode* treeNode, int sectionLength);

//numerical operations
int bits_required_to_secure(int length);
int log_base_2(int number);
bool xor(bool a, bool b);

//initialize structs
struct ParityTreeNode* init_ParityTreeNode(bool* array, int start, int end);
void deallocate_ParityTreeNode(struct ParityTreeNode* destroy);

//format: overall, every other half, every other quarter, etc...
bool* secure_chunk(bool* array, int length) {
  int bitsRequired = bits_required_to_secure(length);
  bool* securityInformation = malloc(bitsRequired*sizeof(bool));
  int startOfArray = 0;
  secure_chunk_copy_into(array, length, securityInformation, startOfArray);
  return securityInformation;
}

void secure_chunk_copy_into(bool* array, int length, bool* copyInto, int startCopyingAt) {
  struct ParityTreeNode* head = init_ParityTreeNode(array, 0, length);
  for(int sectionLength = length; sectionLength > 0; sectionLength /= 2) {
    copyInto[startCopyingAt++] = parity_of_section(head, sectionLength);
  }
  deallocate_ParityTreeNode(head);
}

bool parity_of_section(struct ParityTreeNode* treeNode, int sectionLength) {
  if(treeNode->length == sectionLength) {
    return treeNode->parity;
  }
  bool parityOfLeftSections = parity_of_section(treeNode->left, sectionLength);
  if(treeNode->left->length == sectionLength) {
    return parityOfLeftSections;
  }
  bool parityOfRightSections = parity_of_section(treeNode->right, sectionLength);
  return xor(parityOfLeftSections, parityOfRightSections);
}

int bits_required_to_secure(int length) {
  int bitsRequiredToTrackOverallParity = 1;
  return log_base_2(length) + bitsRequiredToTrackOverallParity;
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

bool xor(bool a, bool b) {
  return a != b;
}

struct ParityTreeNode* init_ParityTreeNode(bool* array, int start, int end) {
  int length = end - start;
  struct ParityTreeNode* constructing = malloc(sizeof(struct ParityTreeNode));
  constructing->start = start;
  constructing->length = length;
  if(1 == length) {
    constructing->left = NULL;
    constructing->right = NULL;
    constructing->parity = array[start];
  } else {
    int middle = start + length / 2;
    constructing->left = init_ParityTreeNode(array, start, middle);
    constructing->right = init_ParityTreeNode(array, middle, end);
    constructing->parity = xor(constructing->left->parity, constructing->right->parity);
  }
  return constructing;
}

void deallocate_ParityTreeNode(struct ParityTreeNode* destroy) {
  if(1 != destroy->length) {
    deallocate_ParityTreeNode(destroy->left);
    deallocate_ParityTreeNode(destroy->right);
  }
  free(destroy);
}

#endif
