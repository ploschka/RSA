#ifndef RSA_H
#define RSA_H

#include <stdint.h>

typedef struct rsa_key_t rsa_key_t;

rsa_key_t *rsa_create_key();
void rsa_generate_keys(unsigned int seed, rsa_key_t *public, rsa_key_t *private);
int64_t rsa_encrypt(rsa_key_t *public, int64_t message);
int64_t rsa_decrypt(rsa_key_t *private, int64_t message);

#endif
