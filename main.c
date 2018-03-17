#include <stdio.h>
#include "garbage.h"

/* 
Example of usage of GarbageHeap.
You can see that there is no free() call in your code
but also there is no memory leak.
*/

int main (void)
{
    initGarbageHeap();

    for (int i = 0; i < 10000; ++i)
    {
        char* str = gmalloc(1000*sizeof(char));
        str = grealloc(str, 2000*sizeof(char));
    }

    freeGarbageHeap();
    return 0;
}
