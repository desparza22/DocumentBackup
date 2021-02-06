#ifndef HANDLEINTERACTION_H
#define HANDLEINTERACTION_H

#include <stdbool.h>
#include <stdio.h>

#include "Filing.h"
#include "RestoreBits.h"
#include "SecureBits3.h"

void start_script();
void create_file();
void modify_file();
void restore_file();

void start_script() {
  printf("This is a testing mode for the program. \nYou can create a file to be secured (\"c\"), modify a secured file (\"m\"), or restore a secured file (\"r\"). \nType the letter next to the action you would like to take then press return/enter...\n");
  char* holdInput = calloc(2, sizeof(char));
  fgets(holdInput, 2, stdin);
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
  char* holdInput = calloc(4, sizeof(char));
  fgets(holdInput, 3, stdin);
  int power = string_to_integer(holdInput);
  free(holdInput);
  if(power >= 0 && power <= 16) {
    int numWords = 1<<power;
    printf("Please enter the length of the text for each line [1-999]. Note: the number of security bits grows linearly with the length of the lines...\n");
    holdInput = calloc(4, sizeof(char));
    fgets(holdInput, 4, stdin);
    int wordLength = string_to_integer(holdInput);
    
  } else {
    printf("ERROR: The number should be in the inclusive range of [0-16]. ");
    free(holdInput);
    create_file();
  }
}

void modify_file() {

}

void restore_file() {

}

#endif
