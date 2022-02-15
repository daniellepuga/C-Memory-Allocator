#include "myalloc.h"

// head of the list, empty
struct block * head = NULL;  

// example runs from project document
int main(void)
{
  void *p;
    print_data();
    p = myalloc(32);
    print_data();
    // [empty]
    // [32, used] -> [960, free]
    // since we have splitting
}

// https://www.geeksforgeeks.org/first-fit-algorithm-in-memory-management-using-linked-list/
void split_space(block ** current, block ** next, int bytes) 
{
    // add conditional here for if the node not big enough to split
    block * cur = *current;

    block * nxt = *next;
    
    // we create a new node and expect that the next one is not in use
    nxt->in_use = false;
    // we make the next node's size equal to current's size minus
    // the total padding
    nxt->size = cur->size - (TOTAL_PAD);
    // next should have no next value yet
    nxt->next = NULL;
    // we set the current node's next equal to next node
    cur->next = nxt;
    // we know that our current node is in use
    cur->in_use = true;
    // we update the current node's size to be equal to the padding
    cur->size = PADDED_SIZE(bytes);
}

// add a myfree() function to mark blocks as unused.
// this function will receive only pointers they got
// from myalloc().

void *myalloc(int bytes)
{
  if (head == NULL)
  {
    // if this is the first call, sbrk() to get space (1024)
    // at the same time, we will make a linked list node inside
    // this new space indicating its size and "in use" status.
    head = sbrk(1024);
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
    head->next = NULL;

  // we look to see if memory is available
  if (PADDED_SIZE(bytes) <= head->size)
  {
    // when memory is available, we make the next block's head
    // have memory equal to the size of the block plus a buffer
    // at the head.
    block * next = PTR_OFFSET(head, TOTAL_PAD);
    split_space(&head, &next, bytes);
    // use the provided macro to return # of bytes equal to size of block 
    // ahead of head node
    return PTR_OFFSET(head, PAD_BLOCK_SIZE);
  }
  }
  else
  {
    // walk the linked list in a look and look for the first
    // node that is not in use and big enough to hold amt+ some
    block * cur = head;
    while (cur)
    {
      if(!cur->in_use && (PADDED_SIZE(bytes) + PAD_BLOCK_SIZE) <= cur->size)
      {
        // if the block is found, mark it in use and
        // return a pointer to the user data just after the linked
        // list node (plus some padding).
        block * next = PTR_OFFSET(cur, TOTAL_PAD);
        split_space(&cur, &next, bytes); 
        // use the provided macro to return # of bytes equal to size of block 
        // ahead of current node
        return PTR_OFFSET(cur, PAD_BLOCK_SIZE);
      }
      else
      {
        cur = cur->next;
      }
    }
  }
  // if NO space is found:
  return NULL;
}

// below function from project document
void print_data(void)
{
    struct block *b = head;
    if (b == NULL) {
        printf("[empty]\n");
        return;
    }
    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        // printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        b = b->next;
    }
    printf("\n");
}
