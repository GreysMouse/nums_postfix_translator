#include "../include/buffer.h"
#include "../macro/exceptions.h"
#include <stddef.h>
#include <stdlib.h>

void *create_buf(size_t size)
{
    void *buf = malloc(size);

    if (!buf) {
        NO_BUFFER_MEMORY_ERR();
    }
    return buf;
}
