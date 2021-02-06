#ifndef RANDOMWORD_H
#define RANDOMWORD_H

#include <stdbool.h>
#include <stdlib.h>

#include "Arrays.h"

bool* random_bool_array(int length);
struct Array** random_words_with_default_alphabet(int numWords, int wordLength);
struct Array* random_word_with_alphabet(int length, struct Array* alphabet);
struct Array* get_default_alphabet();

bool* random_bool_array(int length) {
  bool* array = malloc(length * sizeof(bool));
  for(int i = 0; i < length; i++) {
    array[i] = (rand()%2) == 1;
  }
  return array;
}

struct Array** random_words_with_default_alphabet(int numWords, int wordLength) {
 struct Array** words = malloc(numWords * sizeof(struct Array*));
 struct Array* alphabet = get_default_alphabet();
 for(int i = 0; i < numWords; i++) {
   words[i] = random_word_with_alphabet(wordLength, alphabet);
 }
 return words;
}

struct Array* random_word_with_alphabet(int length, struct Array* alphabet) {
  int alphabetLength = alphabet->length;
  struct Array* word = init_array_malloc(length);
  for(int i = 0; i < length; i++) {
    word->array[i] = alphabet->array[rand()%alphabetLength];
  }
  word->array[length] = '\0';
  return word;
}

struct Array* get_default_alphabet() {
  int alphabetLength = 26;
  struct Array* alphabet = init_array_malloc(alphabetLength);
  for(int i = 0; i < 26; i++) {
    alphabet->array[i] = 'a' + i;
  }
  return alphabet;
}

#endif
