#ifndef PARITYTREE_H
#define PARITYTREE_H

struct ParityTreeNode;
struct ParityTreeNode {
  char parity;
  int startWord;
  int wordsSpanned;
  struct ParityTreeNode* left;
  struct ParityTreeNode* right;
};

struct ParityTreeNode* init_ParityTreeNode(struct Array** arrays, int startWord, int endWord, int distanceIntoWord);
void deallocate_ParityTreeNode(struct ParityTreeNode* destroy);
char parity_of_section(struct ParityTreeNode* treeNode, int sectionLength);

char parity_of_section(struct ParityTreeNode* treeNode, int sectionLength) {
  if(treeNode->wordsSpanned == sectionLength) {
    return treeNode->parity;
  }
  char parityOfLeftSections = parity_of_section(treeNode->left, sectionLength);
  if(treeNode->left->wordsSpanned == sectionLength) {
    return parityOfLeftSections;
  }
  char parityOfRightSections = parity_of_section(treeNode->right, sectionLength);
  return xor(parityOfLeftSections, parityOfRightSections);
}

struct ParityTreeNode* init_ParityTreeNode(struct Array** arrays, int startWord, int endWord, int distanceIntoWord) {
  int wordsSpanned = endWord - startWord;
  struct ParityTreeNode* constructing = malloc(sizeof(struct ParityTreeNode));
  constructing->startWord = startWord;
  constructing->wordsSpanned = wordsSpanned;
  if(1 == wordsSpanned) {
    constructing->left = NULL;
    constructing->right = NULL;
    struct Array* container = arrays[startWord];
    constructing->parity = get_bit_at(container, distanceIntoWord);
  } else {
    int middleWord = startWord + wordsSpanned / 2;
    constructing->left = init_ParityTreeNode(arrays, startWord, middleWord, distanceIntoWord);
    constructing->right = init_ParityTreeNode(arrays, middleWord, endWord, distanceIntoWord);
    constructing->parity = xor(constructing->left->parity, constructing->right->parity);
  }
  return constructing;
}

void deallocate_ParityTreeNode(struct ParityTreeNode* destroy) {
  if(1 != destroy->wordsSpanned) {
    deallocate_ParityTreeNode(destroy->left);
    deallocate_ParityTreeNode(destroy->right);
  }
  free(destroy);
}


#endif
