#ifndef FILING_H
#define FILING_H

#include <stdio.h>

#include "Arrays.h"
#include "Helper.h"
#include "Numerical.h"
#include "Print.h"

struct FileContents;
struct FileContents {
  struct Array** words;
  struct Array* security;
  int numWords;
};

void file_words_and_security(struct Array* fileName, struct FileContents* fileContents);
struct FileContents* retrieve_words_and_security(struct Array* fileName);
int read_lines_and_get_number(int numberOfLines, FILE* filePointer);
struct Array* read_lines_and_security_bits(int linesBeforeSecurityBits, int numSecurityBits, FILE* filePointer);
void read_lines(int numberOfLines, FILE* filePointer);
void read_words(struct Array** words, int numWords, int wordLength, FILE* filePointer);
void read_past_new_line(FILE* filePointer);
struct FileContents* init_FileContents(struct Array** _words, struct Array* _security, int _numWords);


void file_words_and_security(struct Array* fileName, struct FileContents* fileContents) {
  assert(power_of_two(fileContents->numWords), "ERROR: The number of words passed must be a power of 2\n");
  int wordLength = fileContents->words[0]->length;
  FILE* filePointer = fopen(fileName->array, "w");
  fprintf(filePointer, "Number of strings being backed up:\n%d\n", fileContents->numWords);
  fprintf(filePointer, "The strings are of length:\n%d\n\n", wordLength);
  struct Array* securityBinary = represent_binary(fileContents->security);
  fprintf(filePointer, "The number of security bits are:\n%d\n", securityBinary->length);
  fprintf(filePointer, "Security Bits:\n%s\n\n", securityBinary->array);
  for(int i = 0; i < fileContents->numWords; i++) {
    fprintf(filePointer, "%s\n", fileContents->words[i]->array);
  }
  fclose(filePointer);
}

struct FileContents* retrieve_words_and_security(struct Array* fileName) {
  FILE* filePointer = fopen(fileName->array, "r");
  int linesBeforeNumberOfWords = 1;
  int linesBeforeWordLength = 1;
  int linesBeforeNumberOfSecurityBits = 2;
  int linesBeforeSecurityBits = 1;
  int linesBeforeWords = 1;
  int numWords = read_lines_and_get_number(linesBeforeNumberOfWords, filePointer);
  int wordLength = read_lines_and_get_number(linesBeforeWordLength, filePointer);
  int numSecurityBits = read_lines_and_get_number(linesBeforeNumberOfSecurityBits, filePointer);

  struct Array* securityBits = read_lines_and_security_bits(linesBeforeSecurityBits, numSecurityBits, filePointer);
  struct Array** words = malloc(numWords * sizeof(struct Array*));
  struct Array* security = represent_string(securityBits);

  read_lines(linesBeforeWords, filePointer);
  read_words(words, numWords, wordLength, filePointer);

  fclose(filePointer);
  return init_FileContents(words, security, numWords);
}

int read_lines_and_get_number(int numberOfLines, FILE* filePointer) {
  read_lines(numberOfLines, filePointer);
  int maxIntegerLength = 11;
  char* holdNumber = malloc(maxIntegerLength * sizeof(char));

  fgets(holdNumber, maxIntegerLength, filePointer);
  return string_to_integer(holdNumber);
}

struct Array* read_lines_and_security_bits(int linesBeforeSecurityBits, int numSecurityBits, FILE* filePointer) {
  read_lines(linesBeforeSecurityBits, filePointer);
  struct Array* securityBits = init_array_malloc(numSecurityBits);
  fgets(securityBits->array, numSecurityBits+1, filePointer);
  read_past_new_line(filePointer);
  return securityBits;
}

void read_past_new_line(FILE* filePointer) {
  read_lines(1, filePointer);
}

void read_lines(int numberOfLines, FILE* filePointer) {
  int maxTextLength = 40;
  char* holdText = malloc(maxTextLength * sizeof(char));

  for(int i = 0; i < numberOfLines; i++) {
    fgets(holdText, maxTextLength, filePointer);
  }
}

void read_words(struct Array** words, int numWords, int wordLength, FILE* filePointer) {
  for(int i = 0; i < numWords; i++) {
    struct Array* word = init_array_malloc(wordLength);
    fgets(word->array, wordLength+1, filePointer);
    read_past_new_line(filePointer);
    words[i] = word;
  }
}

struct FileContents* init_FileContents(struct Array** _words, struct Array* _security, int _numWords) {
  struct FileContents* holdFileContents = malloc(sizeof(struct FileContents));
  holdFileContents->words = _words;
  holdFileContents->security = _security;
  holdFileContents->numWords = _numWords;
  return holdFileContents;
}

#endif

