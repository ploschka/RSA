#ifndef ALG_H
#define ALG_H
#include <stdint.h>

uint32_t random_prime(uint32_t iteration);
uint64_t exp_mod(int64_t base, uint64_t exponent, uint64_t mod);
uint64_t euler(uint64_t a, uint64_t b);
uint64_t extended_euclid(uint64_t a, uint64_t b, int64_t *x, int64_t *y);

#endif
