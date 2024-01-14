#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "rsa.h"

int main()
{
    rsa_key_t *public = rsa_create_key();
    rsa_key_t *private = rsa_create_key();
    unsigned int seed = time(NULL);
    rsa_generate_keys(seed, public, private);
    int64_t message = 65;
    uint64_t em = rsa_encrypt(public, message);
    int64_t dm = rsa_decrypt(private, em);

    printf("message = %ld\n", message);
    printf("encrypted message = %lu\n", em);
    printf("decrypted message = %ld\n", dm);
}
