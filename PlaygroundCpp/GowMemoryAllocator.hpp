//
//  GowMemoryAllocator.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 2/21/22.
//  Copyright © 2022 Stephen Gowen. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <unordered_map>

/* Calls malloc */
#define GOW_MALLOC(TYPE, COUNT) \
((TYPE*)GowMemoryAllocator::getInstance().gowAlloc(sizeof(TYPE) * COUNT, __FILE__, __LINE__))

/* Calls malloc, followed by memset to zero out the block of memory */
#define GOW_CALLOC(TYPE, COUNT) \
((TYPE*)GowMemoryAllocator::getInstance().gowCalloc(sizeof(TYPE) * COUNT, __FILE__, __LINE__))

/* Convenience macro to allocate and zero out memory for a single instance of TYPE */
#define GOW_NEW(TYPE) \
GOW_CALLOC(TYPE,1)

/* Calls realloc */
#define GOW_REALLOC(PTR, TYPE, COUNT) \
((TYPE*)GowMemoryAllocator::getInstance().gowRealloc(PTR, sizeof(TYPE) * (COUNT), __FILE__, __LINE__))

/* Frees memory. Can be used on const types. */
#define GOW_FREE(PTR) \
GowMemoryAllocator::getInstance().gowFree((void*)PTR, __FILE__, __LINE__)

/* Call destructor and then frees memory. Can be used on const types. */
#define GOW_DESTROY(PTR, TYPE)                            \
PTR->~TYPE();                                             \
GowMemoryAllocator::getInstance().gowFree((void*)PTR, __FILE__, __LINE__)

class GowMemoryAllocator
{
public:
    static GowMemoryAllocator& getInstance()
    {
        static GowMemoryAllocator ret = GowMemoryAllocator();
        return ret;
    }
    
    void* gowAlloc(size_t size, const char* file, int line);
    void* gowCalloc(size_t size, const char* file, int line);
    void* gowRealloc(void* ptr, size_t size, const char* file, int line);
    void gowFree(void* ptr, const char* file, int line);
    
private:
    std::unordered_map<void*, size_t> _allocations;
    
    void logAllocations();
};
