////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowengine/memory.h>

#include <assert.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

void* vow_memory_allocate(int bytes)
{
    // It's very common to zero-initialize memory after allocating it,
    // hence the use of `calloc()` instead of `malloc()`.
    void* memory = calloc(1, bytes);

    // If the machine can't allocate enough memory,
    // then chances are that the program is going to fail anyway.
    assert(memory);

    return memory;
}

void vow_memory_free(void* memory)
{
    // The `free()` function gracefully handles invalid `memory` scenarios.
    free(memory);
}