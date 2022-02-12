

// myalloc() function
// will allocate certain # of bytes and return a
// pointer to it.
// NO using builtin malloc.
// intentionally incomplete for now

// logic:
// if this is the first call, sbrk() to get space
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