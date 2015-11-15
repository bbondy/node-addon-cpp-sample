#include <math.h>
#include "hash.h"

/**
 * Computes a polynomial based hash of the input string.
 * In particular this is similar to a Rabin-Karp hash.
 */
uint64_t hash(uint32_t p, const char *input, int len) {
  uint64_t total = 0;
  for (int i = 0; i < len; i++) {
    total += input[i] * pow(p, len - i - 1);
  }
  return total;
}

