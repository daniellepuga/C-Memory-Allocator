// myalloc.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))
#define PAD_BLOCK_SIZE ( (int) PADDED_SIZE(sizeof(block)) )
#define TOTAL_PAD (PAD_BLOCK_SIZE + PADDED_SIZE(bytes))

// https://www.tutorialspoint.com/cprogramming/c_typedef.htm
// we use typedef here to define this structure as a new data
// type and then use that to define structure variables in
// myalloc.c
typedef struct block {
    struct block *next;
    int size;   // Bytes
    int in_use; // Boolean
} block;

void * myalloc(int);
void print_data(void);
void allocate_memory(block **, block **, int);
