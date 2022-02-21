//
//  GowMemoryAllocator.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 2/21/22.
//  Copyright © 2022 Stephen Gowen. All rights reserved.
//

#pragma once

#include <stdlib.h>

/* Calls malloc */
#define GOW_MALLOC(TYPE, COUNT) \
((TYPE*)GowMemoryAllocator::gowAlloc(sizeof(TYPE) * COUNT, __FILE__, __LINE__))

/* Calls malloc, followed by memset to zero out the block of memory */
#define GOW_CALLOC(TYPE, COUNT) \
((TYPE*)GowMemoryAllocator::gowCalloc(sizeof(TYPE) * COUNT, __FILE__, __LINE__))

/* Convenience macro to allocate and zero out memory for a single instance of TYPE */
#define GOW_NEW(TYPE) \
GOW_CALLOC(TYPE,1)

/* Calls realloc */
#define GOW_REALLOC(PTR, TYPE, COUNT) \
((TYPE*)GowMemoryAllocator::gowRealloc(PTR, sizeof(TYPE) * (COUNT), __FILE__, __LINE__))

/* Frees memory. Can be used on const types. */
#define GOW_FREE(PTR) \
GowMemoryAllocator::gowFree((void*)PTR, __FILE__, __LINE__)

/* Call destructor and then frees memory. Can be used on const types. */
#define GOW_DESTROY(PTR, TYPE)                            \
PTR->~TYPE();                                             \
GowMemoryAllocator::gowFree((void*)PTR, __FILE__, __LINE__)

class GowMemoryAllocator
{
public:
    static void* gowAlloc(size_t size, const char* file, int line);
    static void* gowCalloc(size_t size, const char* file, int line);
    static void* gowRealloc(void* ptr, size_t size, const char* file, int line);
    static void gowFree(void* ptr, const char* file, int line);
};
