#include "alg.h"
#include <stdlib.h>

static const uint32_t simple_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                         31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                                         73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
                                         127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                                         179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
                                         233, 239, 241, 251};

/*
 * calculates (a * b) % c taking into account that a * b might overflow
 */
static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    uint64_t x = 0, y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

/*
 * modular exponentiation
 */
uint64_t exp_mod(int64_t base, uint64_t exponent, uint64_t mod)
{
    __int128_t x = 1;
    __int128_t y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent >> 1;
    }
    return x % mod;
}

/*
 * Miller-Rabin Primality test, iteration signifies the accuracy
 */
static int miller_rabin(uint32_t p, int iteration)
{
    int i;
    uint64_t s;

    if (p < 2)
    {
        return 0;
    }

    if (p != 2 && p % 2 == 0)
    {
        return 0;
    }
    s = p - 1;

    while (s % 2 == 0)
    {

        s /= 2;
    }

    for (i = 0; i < iteration; i++)
    {
        uint64_t a = rand() % (p - 1) + 1, temp = s;
        uint64_t mod = exp_mod(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mul_mod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return 0;
        }
    }
    return 1;
}

static int check_simple_primes(uint32_t num)
{
    for (int i = 0; i < 54; ++i)
    {
        if (num % simple_primes[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

uint64_t euler(uint64_t a, uint64_t b)
{
    return (a - 1) * (b - 1);
}

uint32_t random_prime(uint32_t iteration)
{
    uint32_t num;
    for (;;)
    {
        num = rand();
        if (!check_simple_primes(num))
            continue;
        if (!miller_rabin(num, iteration))
            continue;
        break;
    }
    return num;
}

uint64_t extended_euclid(uint64_t a, uint64_t b, int64_t *x, int64_t *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    int64_t x1, y1; // To store results of recursive call
    uint64_t gcd = extended_euclid(b % a, a, &x1, &y1);
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
