#ifndef ALPHABET_H_INCLUDED
#define ALPHABET_H_INCLUDED

#include "defs.h"

#define ALPHABET_MAX_SIZE 256
#define INVALID_SYMBOL    255

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct {
  uint32_t size;
  uint64_t *positions;
  }
POSITIONS;

typedef struct {
  uint8_t    *numeric;    // Symbols in numbers (20213413...) from file
  uint8_t    *toChars;    // chars: { 'A', 'C', 'G', 'T', 'N', ...}
  uint8_t    *revMap;     // Reverse symbols to numbers
  uint8_t    *alphabet;
  uint8_t    *mask;       // binary vector with symbol existing or not
  uint64_t   *counts;     // counts for symbol distribution
  uint64_t   length;      // total size of the symbols
  uint32_t   low;         // low frequent symbol threshold
  uint32_t   nLow;        // number below low
  uint8_t    *lowAlpha;   // lowChars
  POSITIONS  *posAlpha; // positions of Low chars
  int        cardinality;
  }
ALPHABET;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ALPHABET   *CreateAlphabet            (uint32_t);
void       ResetAlphabet              (ALPHABET *);
void       LoadAlphabet               (ALPHABET *, FILE *);
void       PrintAlphabet              (ALPHABET *);
void       PrintPositions             (ALPHABET *);
void       AdaptAlphabetNonFrequent   (ALPHABET *, FILE *);
void       RemoveAlphabet             (ALPHABET *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif
