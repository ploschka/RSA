#include <stdlib.h>

#include "alg.h"
#include "rsa.h"

typedef struct rsa_key_t
{
    uint64_t k;
    uint64_t n;
} rsa_key_t;

rsa_key_t *rsa_create_key()
{
    return malloc(sizeof(rsa_key_t));
}

void rsa_generate_keys(unsigned int seed, rsa_key_t *public, rsa_key_t *private)
{
    srand(seed);
    const unsigned int iteration = 5;

    uint64_t p = random_prime(iteration);
    uint64_t q = random_prime(iteration);
    uint64_t n = p * q;
    uint64_t phi = euler(p, q);
    uint64_t e = 65537;
    int64_t x, y;
    uint64_t d;
    extended_euclid(e, phi, &x, &y);
    if (x < 0)
    {
        d = phi + x;
    }
    else
    {
        d = x;
    }

    public->k = e;
    public->n = n;

    private->k = d;
    private->n = n;
}

uint64_t rsa_encrypt(rsa_key_t *public, int64_t message)
{
    return exp_mod(message, public->k, public->n);
}

int64_t rsa_decrypt(rsa_key_t *private, uint64_t message)
{
    return exp_mod(message, private->k, private->n);
}
