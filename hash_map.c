#include "header.h"
#include <stdlib.h>
#include<memory.h>
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

struct hash_item
{
    uint64_t zobrist_key;
    unsigned times_seen;
};

struct hash_table
{
    uint32_t size, used;
    struct hash_item **array;
};

struct zobirst_hash_values
{
    uint64_t values[64][4];
};


uint32_t sqrt64(uint64_t r)
{
    uint64_t t, b, c = 0;

    for (b = 1ull << 62; b; b >>= 2)
    {
        t = c + b;
        c >>= 1;
        if (t <= r)
        {
            r -= t;
            c += b;
        }
    }
    return (uint32_t)c;
}

int find_nearest_prime_above(unsigned n)
{
    for(uint64_t c_r = n;;c_r++)
    {
        enum bool a = true;
        if(c_r % 6 == 1 || c_r % 6 == 5)
        {
            uint32_t n1 = sqrt64(c_r);
            for (int i = 2; i < n1; i++)
                if (!(c_r % i))
                {
                    a = false;
                    break;
                }

            if (a) return c_r;
        }
    }
}


enum bool create_hash_table(struct hash_table * t, uint32_t size)
{
    uint32_t prime_size = find_nearest_prime_above(size);
    t->array = malloc( sizeof *t->array * prime_size);
    t->size = prime_size;
    t->used = 0;
    memset(t->array, 0, sizeof *t->array * prime_size);
    return !!t->array;
}

void insert(struct hash_table *t, uint64_t z_b)
{
    int index = z_b % t->size;
    t->array[index]->times_seen ++;
    t->used++;
}

struct hash_item *find(struct hash_table *t, uint64_t z_b)
{
    return t->array[z_b % t->size];
}

void destroy_hash_table(struct hash_table *t)
{
    free(t->array);
    t->used = 0;
    t->size = 0;
}

void fill_zobrist_values(struct zobirst_hash_values *p)
{
    for(int i = 0;i < 64;i++)
        for(int j = 0;j < 4;j++)
            p->values[i][i] = rand() % (uint64_t) - 1;
}

uint64_t zobrist_hash(const struct square (*curr_board)[SIZE], struct zobirst_hash_values *p)
{
    uint64_t hash = 0;
    for(int y = 0;y < SIZE;y++)
        for(int x = 0; x < SIZE;x++)
        {
            struct square *cell = &board[y][x];
            int index = cell->type;

            if(cell->color == white)
                index = (index + 1) * 2;

            hash ^= p->values[y*SIZE+x][index];
        }
    return hash;
}