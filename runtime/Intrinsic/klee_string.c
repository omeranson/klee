//===-- klee_string.c -----------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <assert.h>
#include "klee/klee.h"

extern void * malloc(size_t);

#define DEFAULT_SIZE 16

char * klee_string(size_t size, const char * name) {
  if (size == 0) {
    size = DEFAULT_SIZE;
  }
  char * buffer = (char *)malloc(sizeof(char)*size);
  klee_make_symbolic(buffer, size*sizeof(char), name);
  return buffer;
}

