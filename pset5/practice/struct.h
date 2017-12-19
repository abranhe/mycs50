typedef struct fullname
{
    char c;
    struct fullname *next;
}
node;

typedef struct dllist
{
    int n;
    struct dllist *prev;
    struct dllist *next;
}
dlnode;

typedef struct
{
    int *n;
    int top;
    int max; // as control to prevent spilling
}
stackarray;

typedef struct _stack
{
    int n;
    struct _stack *next;
}
stacklink;

typedef struct
{
    int *n;
    int front;
    int size;
}
queue;

typedef struct _queue
{
    int n;
    struct _queue *prev;
    struct _queue *next;
}
queuelist;

typedef struct _hash
{
    char name[20];
    struct _hash *next;
}
hashline;

typedef struct _trie
{
    char university[20];
    struct _trie *paths[10]
}
trie;