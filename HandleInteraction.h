#ifndef HANDLEINTERACTION_H
#define HANDLEINTERACTION_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Arrays.h"
#include "Filing.h"
#include "RandomWord.h"
#include "RestoreBits.h"
#include "SecureBits3.h"

void start_script();
void create_file();
void modify_file();
void restore_file();
void read_to_end();

void start_script() {
  srand(time(0));
  printf("This is a testing mode for the program. \nYou can create a file to be secured (\"c\"), modify a secured file (\"m\"), or restore a secured file (\"r\"). \nType the letter next to the action you would like to take then press return/enter...\n");
  char* holdInput = calloc(100, sizeof(char));
  fgets(holdInput, 100, stdin);
  // read_to_end();
  char selection = holdInput[0];
  free(holdInput);
  if(selection == 'c') {
    create_file();
  } else if(selection == 'm') {
    modify_file();
  } else if(selection == 'r') {
    restore_file();
  } else {
    printf("Input entered was invalid. Program ended\n");
  }
}

void create_file() {
  printf("Please enter the two's power of the number of lines you want to have generated [0-16]. Example: entering 5 will generate 2^5 = 32 lines...\n");
  char* holdInput = calloc(100, sizeof(char));
  fgets(holdInput, 100, stdin);
  // read_to_end();
  int power = string_to_integer(holdInput);
  free(holdInput);
  if(power >= 0 && power <= 16) {
    int numWords = 1<<power;
    printf("Please enter the length of the text for each line [1-999]. Note: the number of security bits grows linearly with the length of the lines...\n");
    holdInput = calloc(100, sizeof(char));
    fgets(holdInput, 100, stdin);
    // read_to_end();
    int wordLength = string_to_integer(holdInput);
    struct Array** words = random_words_with_default_alphabet(numWords, wordLength);
    struct Array* security = secure_words(words, numWords);
    struct FileContents* fileContents = init_FileContents(words, security, numWords);
    char* fileName = "SecuredWords.txt";
    struct Array* fileNameArray = init_array(fileName, strlen(fileName));
    file_words_and_security(fileNameArray, fileContents);
    printf("Data has been filed to %s. Would you like to return to the menu where you can modify or restore bits (\"r\") or quit (any other key)?\n", fileName);
    free(holdInput);
    holdInput = calloc(100, sizeof(char));
    fgets(holdInput, 100, stdin);
    // read_to_end();
    char selection = holdInput[0];
    free(holdInput);
    if(selection == 'r') {
      start_script();
    }
  } else {
    printf("ERROR: The number should be in the inclusive range of [0-16]. ");
    free(holdInput);
    create_file();
  }
}

void modify_file() {
  char* fileName = "SecuredWords.txt";
  struct Array* fileNameArray = init_array(fileName, strlen(fileName));
  struct FileContents* fileContents = retrieve_words_and_security(fileNameArray);
  printf("There are %d words. Enter the line number, 0-indexed, that you would like to have modified [0-%d]...\n", fileContents->numWords, fileContents->numWords-1);
  printf("(Words start at line 11 so, if looking directly at the file, subtract 11 from the line you would like to modify)\n");
  char* holdLineToModify = calloc(100, sizeof(char));
  fgets(holdLineToModify, 100, stdin);
  // read_to_end();
  int lineToModify = string_to_integer(holdLineToModify);
  free(holdLineToModify);
  struct Array* replacement = random_word_with_alphabet(fileContents->words[0]->length, get_default_alphabet());
  printf("Line %d is being changed from %s to %s\n", lineToModify, fileContents->words[lineToModify]->array, replacement->array);
  fileContents->words[lineToModify] = replacement;
  file_words_and_security(fileNameArray, fileContents);
  char* holdInput = calloc(100, sizeof(char));
  printf("Data in %s has been modified. Would you like to return to the menu where you can restore the original information (\"r\") or quit (any other key)?\n", fileName);
  fgets(holdInput, 100, stdin);
  // read_to_end();
  char selection = holdInput[0];
  free(holdInput);
  if(selection == 'r') {
    start_script();
  }
}

void restore_file() {
  printf("File text is being recovered using security bits...\n");
  char* fileName = "SecuredWords.txt";
  struct Array* fileNameArray = init_array(fileName, strlen(fileName));
  struct FileContents* fileContents = retrieve_words_and_security(fileNameArray);
  restore_words(fileContents->words, fileContents->security, fileContents->numWords);
  file_words_and_security(fileNameArray, fileContents);
  printf("Information in %s has been corrected!\n", fileName);
}

void read_to_end() {
  int c = EOF - 1;
  while(c != EOF) {
    printf("Before %d != %d\n", c, EOF);
    c = getchar();
    printf("After %d != %d\n", c, EOF);
  }
}

#endif

