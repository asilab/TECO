#include <stdio.h>
#include "alphabet.h"
#include "mem.h"


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PrintID
//
void PrintID(ALPHABET *A, int id){
  switch(id){
    case 9:
      fprintf(stderr, "%3d :'\\t' ( %"PRIu64" )\n", id, A->counts[id]);
    break;
    case 10:
      fprintf(stderr, "%3d :'\\n' ( %"PRIu64" )\n", id, A->counts[id]);
    break;
    default:
      fprintf(stderr, "%3d :'%c' ( %"PRIu64" )\n", id, id, A->counts[id]);
    break;
    }
  }


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
  A->length      = 0;
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
  A->length = size;

  A->cardinality = 0;
  for(x = 0 ; x < ALPHABET_MAX_SIZE ; x++){
    if(A->mask[x] == 1){
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
  fprintf(stderr, "File size        : %"PRIu64"\n", A->length);
  fprintf(stderr, "Alphabet size    : %u\n", A->cardinality);
  fprintf(stderr, "Alphabet         : \n");
  for(x = 0 ; x < A->cardinality ; ++x){
    PrintID(A, (int) A->toChars[x]);
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ADAPT ALPHABET
//
void AdaptAlphabetNonFrequent(ALPHABET *A){
  uint32_t x;

  for(x = 0 ; x < A->cardinality ; ++x){
    int id = (int) A->toChars[x];
    if(A->counts[id] < 100 && A->length > 1000000){
      A->mask[id] = 2;
      }
    }

  fprintf(stderr, "\nLow frequent sym : \n");
  for(x = 0 ; x < A->cardinality ; ++x){
    int id = (int) A->toChars[x];
    if(A->mask[id] == 2){
      PrintID(A, id);
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
