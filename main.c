#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "Arrays.h"
#include "Filing.h"
#include "HandleInteraction.h"
#include "Helper.h"
#include "Print.h"
#include "RandomWord.h"
#include "RestoreBits.h"
#include "SecureBits3.h"

void test1();
void test2();
void test3();
void test4();
void test5();

int main() {
  test5();
}

void test1() {
  srand(time(0));

  int numWords = 64;
  int wordLength = 2;
  struct Array** words = random_words_with_default_alphabet(numWords, wordLength);
  struct Array* security = secure_words(words, numWords);

  char* fileName = "file.txt";
  struct Array* fileArray = init_array(fileName, 8);
  struct FileContents* fileContents = init_FileContents(words, security, numWords);
  file_words_and_security(fileArray, fileContents);

  restore_words(words, security, numWords);
}

void test2() {
  srand(time(0));
  int numWords = 8;
  int wordLength = 4;
  struct Array** words = random_words_with_default_alphabet(numWords, wordLength);
  print_strings(words, numWords);
  struct Array* security = secure_words(words, numWords);
  print_new_line();
  print_binary(security);
  print_new_line();
  print_new_line();

  char* fileName = "file.txt";
  struct Array* fileArray = init_array(fileName, 8);
  struct FileContents* fileContents = init_FileContents(words, security, numWords);
  file_words_and_security(fileArray, fileContents);

  struct FileContents* fileContents2 = retrieve_words_and_security(fileArray);
  struct Array** wordsRetrieved = fileContents2->words;
  struct Array* securityRetrieved = fileContents2->security;
  int numWordsRetrieved = fileContents2->numWords;
  print_strings(wordsRetrieved, numWordsRetrieved);
  print_new_line();
  print_binary(security);
  print_new_line();
}

void test3() {
  srand(time(0));
  int numWords = 64;
  int wordLength = 4;
  struct Array** words = random_words_with_default_alphabet(numWords, wordLength);
  struct Array* security = secure_words(words, numWords);
  char* fileName = "file.txt";
  struct Array* fileArray = init_array(fileName, 8);
  struct FileContents* fileContents = init_FileContents(words, security, numWords);
  file_words_and_security(fileArray, fileContents);
}

void test4() {
  char* fileName = "file.txt";
  struct Array* fileArray = init_array(fileName, 8);

  struct FileContents* fileContents = retrieve_words_and_security(fileArray);
  struct Array** wordsRetrieved = fileContents->words;
  struct Array* securityRetrieved = fileContents->security;
  int numWordsRetrieved = fileContents->numWords;

  restore_words(wordsRetrieved, securityRetrieved, numWordsRetrieved);
  file_words_and_security(fileArray, fileContents);
}

void test5() {
  start_script();
}
