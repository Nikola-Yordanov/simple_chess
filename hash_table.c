#include "header.h"
#include <stdlib.h>
#include <memory.h>

uint32_t uint32_sqrt(unsigned long x)
{
    register unsigned long op, res, one;

    op = x;
    res = 0;

    /* "one" starts at the highest power of four <= than the argument. */
    one = 1 << 30;  /* second-to-top bit set */
    while (one > op) one >>= 2;

    while (one != 0) {
        if (op >= res + one) {
            op -= res + one;
            res += one << 1;  // <-- faster than 2 * one
        }
        res >>= 1;
        one >>= 2;
    }
    return res;
}

enum bool is_prime(uint32_t n)
{
    uint32_t n_sqrt = uint32_sqrt(n);
    for(int i = 2;i < n_sqrt;i++)
        if( n % i == 0)
            return false;

    return true;
}

uint32_t find_nearest_prime_above(uint32_t n)
{
    for(int c_p = n;;c_p++)
        if(is_prime(c_p))
            return c_p;
}

void set_to_zero(struct item **a, unsigned n)
{
    memset(*a, 0, sizeof *a * n);
}

enum bool create_hash_table(struct hash_table *hash_table, uint32_t table_size)
{
    uint32_t nearest_prime = find_nearest_prime_above(table_size);
    hash_table->array = malloc(sizeof *hash_table->array * nearest_prime);
    hash_table->table_size = nearest_prime;
    hash_table->used = 0;
    set_to_zero(&hash_table->array, hash_table->table_size);
}