#ifndef GARBAGE_H
#define GARBAGE_H

void initGarbageHeap (void);
void freeGarbageHeap (void);
void* gmalloc (size_t sizemem);
void* gcalloc (size_t number, size_t size);
void* grealloc (void* ptrmem, size_t sizemem);

#endif // GARBAGE_H
