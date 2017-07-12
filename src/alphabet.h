#ifndef ALPHABET_H_INCLUDED
#define ALPHABET_H_INCLUDED

#include "defs.h"

#define ALPHABET_MAX_SIZE 256
#define INVALID_SYMBOL    255

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct {
  uint8_t    *numeric;    // Symbols in numbers (20213413...) from file
  uint8_t    *toChars;    // chars: { 'A', 'C', 'G', 'T', 'N', ...}
  uint8_t    *revMap;     // Reverse symbols to numbers
  uint8_t    *alphabet;
  uint8_t    *mask;       // binary vector with symbol existing or not
  int        cardinality;
  }
ALPHABET;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ALPHABET   *CreateAlphabet   (void);
void       LoadAlphabet      (ALPHABET *, FILE *);
void       PrintAlphabet     (ALPHABET *);
void       RemoveAlphabet    (ALPHABET *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif
