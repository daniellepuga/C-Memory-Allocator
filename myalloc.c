#include "myalloc.h"

struct block * head = NULL;  

void print_data(void) {
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

void split(struct block *b, int padded_size)
{
  int block_padded_size = PADDED_SIZE(sizeof(struct block));

  int old_size = b->size;
  int remaining_free_space = old_size - padded_size - block_padded_size;

  int room_to_split = remaining_free_space >= 16;
  
  if (room_to_split)
  {
  // get a pointer to new block
  struct block *new_b = PTR_OFFSET(b, padded_size + block_padded_size);
  // set new block's size
  new_b->size = b->size - padded_size - block_padded_size;
  // set this block's size 
  b->size = padded_size;
  // set new block to free
  new_b->in_use = 0;
  // wire up the linked list
  new_b->next = b->next;
  b->next = new_b;
  }
}

void *myalloc(size_t size) {

	if (head == NULL) { 
    	head = sbrk(1024);
    	head->next = NULL;
    	head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    	head->in_use = 0;
    }

    (void)size;

    int padded_size = PADDED_SIZE(size);
    int block_padded_size = PADDED_SIZE(sizeof(struct block));

    struct block *cur = head;

    while (cur != NULL) {
        // if this node is big enough and not in use:
        if (!cur->in_use && cur->size >= padded_size) {
          split(cur, padded_size);
            // mark it in use
            cur->in_use = 1;
            // printf("Found one!\n");

            // return pointer to node data
            return PTR_OFFSET(cur, block_padded_size);
        }
        cur = cur->next;
    }
    return NULL;
}

void myfree(void *p)
{
  // find struct block that correpsonds to pointer p
  struct block *b = PTR_OFFSET(p, -PADDED_SIZE(sizeof(struct block)));

  // mark it as free
  b->in_use = 0;

// start cur at head
  struct block *cur = head;

    // while cur->next isn't NULL:
	while (cur->next != NULL) { 
        // if cur is not in_use and next node not in use:
	    if ((cur->in_use == 0) && (cur->next->in_use == 0)) {
            // add the next node's region's size to cur's
		    cur->size += PADDED_SIZE(sizeof(struct block)) + (cur->next)->size;
            // make cur's next pointer skip the next node	
		    cur->next = cur->next->next;	
		}
        // else
		else {
            // move cur to next node
		    cur = cur->next;	
		}		
	}
}


int main(void) {
void *p, *q, *r, *s;

    p = myalloc(10); print_data();
    q = myalloc(20); print_data();
    r = myalloc(30); print_data();
    s = myalloc(40); print_data();

    myfree(q); print_data();
    myfree(p); print_data();
    myfree(s); print_data();
    myfree(r); print_data();
}
