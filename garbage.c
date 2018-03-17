#include <stdlib.h>
#include "garbage.h"

typedef struct
{
    void** buffer;
    int len;
    int capacity;
}
GarbageHeap;

static GarbageHeap garbage_heap;

void initGarbageHeap (void)
{
    int len = 32;
    garbage_heap.len = 0;
    garbage_heap.capacity = len;
    garbage_heap.buffer = (void**)malloc(sizeof(void*)*len);
    for (int i = 0; i < len; ++i)
        garbage_heap.buffer[i] = NULL;
}

void freeGarbageHeap (void)
{
    for (int i = 0; i < garbage_heap.len; ++i)
        if (garbage_heap.buffer[i] != NULL)
            free(garbage_heap.buffer[i]);
    free(garbage_heap.buffer);
}

void resizeGarbageHeap (void)
{
    garbage_heap.capacity *= 2;
    garbage_heap.buffer = (void**)realloc(garbage_heap.buffer, sizeof(void*)*garbage_heap.capacity);
    for (int i = garbage_heap.len; i < garbage_heap.capacity; ++i)
        garbage_heap.buffer[i] = NULL;
}

void* gmalloc (size_t sizemem)
{
    if (garbage_heap.len == garbage_heap.capacity)
        resizeGarbageHeap();
    garbage_heap.buffer[garbage_heap.len] = malloc(sizemem);
    ++garbage_heap.len;
    return garbage_heap.buffer[garbage_heap.len - 1];
}

void* gcalloc (size_t number, size_t size)
{
    if (garbage_heap.len == garbage_heap.capacity)
        resizeGarbageHeap();
    garbage_heap.buffer[garbage_heap.len] = calloc(number, size);
    ++garbage_heap.len;
    return garbage_heap.buffer[garbage_heap.len - 1];
}

void* grealloc (void* ptrmem, size_t sizemem)
{
    if (ptrmem == NULL)
        return gmalloc(sizemem);
    int i = 0;
    while (garbage_heap.buffer[i] != ptrmem)
        ++i;
    void* tmp_ptr = realloc(ptrmem, sizemem);
    if (tmp_ptr != NULL)
        garbage_heap.buffer[i] = tmp_ptr;
    return tmp_ptr;
}
