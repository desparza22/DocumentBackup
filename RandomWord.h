#ifndef RANDOMWORD_H
#define RANDOMWORD_H

#include <stdlib.h>
#include <stdbool.h>

struct alphabetAndLength;

bool* random_bool_array(int length);
char** random_words_with_default_alphabet(int numWords, int wordLength);
char* random_word_with_default_alphabet(int length);
char* random_word_with_alphabet(int length, char* alphabet, int alphabetLength);
struct alphabetAndLength* get_default_alphabet();
struct alphabetAndLength* init_alphabetAndLength(char* alphabet, int length);

struct alphabetAndLength {
  char* alphabet;
  int length;
};

bool* random_bool_array(int length) {
  bool* array = malloc(length * sizeof(bool));
  for(int i = 0; i < length; i++) {
    array[i] = (rand()%2) == 1;
  }
  return array;
}

char** random_words_with_default_alphabet(int numWords, int wordLength) {
 char** words = malloc(numWords*sizeof(char*));
 struct alphabetAndLength* holdAlphabetAndLength = get_default_alphabet();
 for(int i = 0; i < numWords; i++) {
   words[i] = random_word_with_alphabet(wordLength, holdAlphabetAndLength->alphabet, holdAlphabetAndLength->length);
 }
 return words;
}

char* random_word_with_default_alphabet(int length) {
  char* randomWord = malloc(length * sizeof(char));
  struct alphabetAndLength* holdAlphabetAndLength = get_default_alphabet();
  return random_word_with_alphabet(length, holdAlphabetAndLength->alphabet, holdAlphabetAndLength->length);
}

char* random_word_with_alphabet(int length, char* alphabet, int alphabetLength) {
  char* word = malloc((length+1) * sizeof(char));
  for(int i = 0; i < length; i++) {
    word[i] = alphabet[rand()%alphabetLength];
  }
  word[length] = '\0';
  return word;
}

struct alphabetAndLength* get_default_alphabet() {
  int alphabetLength = 27;
  char* alphabet = malloc(alphabetLength * sizeof(char));
  for(int i = 0; i < 26; i++) {
    alphabet[i] = 'a' + i;
  }
  alphabet[26] = ' ';
  return init_alphabetAndLength(alphabet, alphabetLength);
}

struct alphabetAndLength* init_alphabetAndLength(char* alphabet, int length) {
  struct alphabetAndLength* holdAlphabetAndLength = malloc(sizeof(struct alphabetAndLength));
  holdAlphabetAndLength->alphabet = alphabet;
  holdAlphabetAndLength->length = length;
  return holdAlphabetAndLength;
}

#endif
