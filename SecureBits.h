#ifndef SECUREBITS_H
#define SECUREBITS_H

#include <stdbool.h>
#include <stdio.h>

bool row_parity(bool* array, int row, int sideLength);
bool col_parity(bool* array, int col, int sideLength);
bool* secure_chunk(bool* array, int sideLength);
bool* parities_of_rows_and_cols(bool* array, int sideLength, bool (*f)(bool*, int, int));
int bits_required_to_secure(int sideLength);
int log_base_2(int sideLength);
bool* secure_chunk_help(int bitsRequiredToSecure, bool* array, bool* rowParities, bool* colParities, int sideLength);
void fill_security_information(bool* securityInformation, bool* array, bool* rowColParities, int sideLength, int* indexToContinueFrom);
bool parity_between(bool* rowOrCol, int start, int end);
bool overall_parity(bool* rowOrCol, int sideLength);
bool xor(bool a, bool b);


bool row_parity(bool* array, int row, int sideLength) {
  int rowStart = sideLength * row;
  bool rowParity = false;
  for(int i = 0; i < sideLength; i++) {
    rowParity = xor(rowParity, array[i+rowStart]);
  }
  return rowParity;
}

bool col_parity(bool* array, int col, int sideLength) {
  int colStart = col;
  bool colParity = false;
  int numBits = sideLength*sideLength;
  for(int i = colStart; i < numBits; i+=sideLength) {
    colParity = xor(colParity, array[i]);
  }
  return colParity;
}

//format: single row, double row, quad row... single col... overall
bool* secure_chunk(bool* array, int sideLength) {
  bool* rowParities = parities_of_rows_and_cols(array, sideLength, row_parity);
  bool* colParities = parities_of_rows_and_cols(array, sideLength, col_parity);
  int bitsRequiredToSecure = bits_required_to_secure(sideLength);
  bool* securityInformation = secure_chunk_help(bitsRequiredToSecure, array, rowParities, colParities, sideLength);
  return securityInformation;
}

bool* parities_of_rows_and_cols(bool* array, int sideLength, bool (*f)(bool*, int, int)) {
  bool* rowParities = malloc(sideLength * sizeof(bool));
  for(int i = 0; i < sideLength; i++) {
    rowParities[i] = f(array, i, sideLength);
  }
  return rowParities;
}

int bits_required_to_secure(int sideLength) {
  int bitsRequiredToSecureSide = log_base_2(sideLength);
  int bitsRequiredToRecordOverallParity = 1;
  return 2*bitsRequiredToSecureSide + bitsRequiredToRecordOverallParity;
}

int bits_required_to_secure_nonsquare(int totalLength) {
  return log_base_2(totalLength) + 1;
}

int log_base_2(int sideLength) {
  for(int i = 0; i < 31; i++) {
    if(1<<i == sideLength) {
      return i;
    }
  }
  printf("non power of 2 %d passed as side length into log_base_2() in SecureBits.h\n", sideLength);
  return -1;
}

bool* secure_chunk_help(int bitsRequiredToSecure, bool* array, bool* rowParities, bool* colParities, int sideLength) {
  bool* securityInformation = malloc(bitsRequiredToSecure*sizeof(bool));
  int indexToContinueFrom = 0;
  fill_security_information(securityInformation, array, rowParities, sideLength, &indexToContinueFrom);
  fill_security_information(securityInformation, array, colParities, sideLength, &indexToContinueFrom);
  securityInformation[indexToContinueFrom] = overall_parity(rowParities, sideLength);
  return securityInformation;
}

void fill_security_information(bool* securityInformation, bool* array, bool* rowColParities, int sideLength, int* indexToContinueFrom) {
  for(int chunkSize = 2; chunkSize <= sideLength; chunkSize *= 2) {
    bool sectionParity = false;
    for(int start = 0; start < sideLength; start += chunkSize) {
      sectionParity = xor(sectionParity, parity_between(rowColParities, start, start+chunkSize/2));
    }
    // printf("%d \n", *indexToContinueFrom);
    securityInformation[(*indexToContinueFrom)++] = sectionParity;
  }
}

bool overall_parity(bool* rowOrCol, int sideLength) {
  int start = 0;
  int end = sideLength;
  return parity_between(rowOrCol, start, end);
}

bool parity_between(bool* rowOrCol, int start, int end) {
  bool parity = false;
  for(int i = start; i < end; i++) {
    parity = xor(parity, rowOrCol[i]);
  }
  return parity;
}

bool xor(bool a, bool b) {
  return a != b;
}

#endif
