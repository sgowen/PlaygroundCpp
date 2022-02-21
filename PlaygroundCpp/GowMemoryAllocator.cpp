//
//  GowMemoryAllocator.cpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 2/21/22.
//  Copyright © 2022 Stephen Gowen. All rights reserved.
//

#include "GowMemoryAllocator.hpp"

#include <iostream>

void* GowMemoryAllocator::gowAlloc(size_t size, const char* file, int line)
{
    printf("gowAlloc size: %lu, file: %s, line: %d \n", size, file, line);
    
    return malloc(size);
}

void* GowMemoryAllocator::gowCalloc(size_t size, const char* file, int line)
{
    void* ptr = gowAlloc(size, file, line);
    if (ptr != nullptr)
    {
        memset(ptr, 0, size);
    }
    
    return ptr;
}

void* GowMemoryAllocator::gowRealloc(void* ptr, size_t size, const char* file, int line)
{
    printf("gowRealloc size: %lu, file: %s, line: %d \n", size, file, line);
    
    return realloc(ptr, size);
}

void GowMemoryAllocator::gowFree(void* ptr, const char* file, int line)
{
    printf("gowFree file: %s, line: %d \n", file, line);
    
    free(ptr);
}
