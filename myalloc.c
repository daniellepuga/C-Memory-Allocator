#include "myalloc.h"

// the goal is to make a myalloc() function
// will allocate certain # of bytes and return a
// pointer to it.
// NO using builtin malloc.
// intentionally incomplete for now

struct block *head = NULL;  // Head of the list, empty

void *myalloc(int bytes)
{
  if (head == NULL)
  {
    // if this is the first call, sbrk() to get space
    head = sbrk(1024);
    head->next = NULL;
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
  }
}

// below from project document
void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }
    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        b = b->next;
    }
    printf("\n");
}

// example runs from project document
int main(void)
{
  void *p;
    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
    // should return:
    // [empty]
    // [1008, used]

    // print_data();
    // p = myalloc(64);
    // print_data();
    // should return:
    // [empty]
    // [1008, used]
    // 0x0
}

// logic:
// > at the same time, we will make a linked list node inside
// > this new space indicating its siez and "in use" status.

// walk the linked list in a look and look for the first
// node that is not in use and big enough to hold amt+ some

// if the block is found:
// > mark it in use
// > return a pointer to the user data just after the linked
// list node (plus some padding).

// if NO block found:
// > return NULL