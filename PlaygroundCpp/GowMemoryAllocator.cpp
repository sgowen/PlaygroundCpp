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
    
    void* ret = malloc(size);
    
    _allocations[ret] = size;
    logAllocations();
    
    return ret;
}

void* GowMemoryAllocator::gowCalloc(size_t size, const char* file, int line)
{
    void* ret = gowAlloc(size, file, line);
    if (ret != nullptr)
    {
        memset(ret, 0, size);
    }
    
    return ret;
}

void* GowMemoryAllocator::gowRealloc(void* ptr, size_t size, const char* file, int line)
{
    printf("gowRealloc size: %lu, file: %s, line: %d \n", size, file, line);
    
    if (ptr != nullptr)
    {
        _allocations.erase(ptr);
    }
    
    void* ret = realloc(ptr, size);
    
    _allocations[ret] = size;
    logAllocations();
    
    return ret;
}

void GowMemoryAllocator::gowFree(void* ptr, const char* file, int line)
{
    printf("gowFree file: %s, line: %d \n", file, line);
    
    free(ptr);
    
    if (ptr != nullptr)
    {
        _allocations.erase(ptr);
    }
    logAllocations();
}

void GowMemoryAllocator::logAllocations()
{
    printf("allocations:\n");
    for (auto const &pair : _allocations)
    {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}
