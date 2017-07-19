#include <stdio.h>
#include "alphabet.h"
#include "mem.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CREATE ALPHABET
//
ALPHABET *CreateAlphabet(void){
  ALPHABET *A    = (ALPHABET *) Calloc(1,                 sizeof(ALPHABET));
  A->numeric     = (uint8_t  *) Calloc(ALPHABET_MAX_SIZE, sizeof(uint8_t));
  A->toChars     = (uint8_t  *) Calloc(ALPHABET_MAX_SIZE, sizeof(uint8_t));
  A->revMap      = (uint8_t  *) Calloc(ALPHABET_MAX_SIZE, sizeof(uint8_t));
  A->alphabet    = (uint8_t  *) Calloc(ALPHABET_MAX_SIZE, sizeof(uint8_t));
  A->mask        = (uint8_t  *) Calloc(ALPHABET_MAX_SIZE, sizeof(uint8_t));
  A->counts      = (uint64_t *) Calloc(ALPHABET_MAX_SIZE, sizeof(uint64_t));
  A->cardinality = 0;
  return A;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// LOAD ALPHABET
//
void LoadAlphabet(ALPHABET *A, FILE *F){
  uint64_t size = 0;
  uint32_t x;
  int32_t  k;
  uint8_t  *buffer;

  buffer = (uint8_t *) Calloc(BUFFER_SIZE, sizeof(uint8_t));
  while((k = fread(buffer, 1, BUFFER_SIZE, F)))
    for(x = 0 ; x < k ; ++x){
      A->mask[buffer[x]] = 1;
      A->counts[buffer[x]]++;
      ++size;
      }
  Free(buffer);

  

  A->cardinality = 0;
  for(x = 0 ; x < ALPHABET_MAX_SIZE ; x++){
    if(A->mask[x]){
      A->toChars[A->cardinality] = x;
      A->revMap[x] = A->cardinality++;
      }      
    else 
      A->revMap[x] = INVALID_SYMBOL;
    }

  rewind(F);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PRINT ALPHABET
//
void PrintAlphabet(ALPHABET *A){
  int x;
  fprintf(stderr, "Alphabet size    : %u\n", A->cardinality);
  fprintf(stderr, "Alphabet         : \n");
  for(x = 0 ; x < A->cardinality ; ++x){
    int id = (int) A->toChars[x];
    switch(id){
      case 9:  fprintf(stderr, "%3d :'\\t' (%"PRIu64")\n", id, A->counts[id]); break;
      case 10: fprintf(stderr, "%3d :'\\n' (%"PRIu64")\n", id, A->counts[id]); break;
      default: fprintf(stderr, "%3d :'%c' (%"PRIu64")\n", id, id, A->counts[id]); break;
      }
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REMOVE ALPHABET
//
void RemoveAlphabet(ALPHABET *A){
  Free(A->numeric);
  Free(A->toChars);
  Free(A->revMap);
  Free(A->alphabet);
  Free(A->mask);
  Free(A);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
