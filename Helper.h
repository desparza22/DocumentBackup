#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void assert(bool check, char* result);

void assert(bool check, char* result) {
  if(!check) {
    printf("%s", result);
  }
}

#endif
