//
//  Pool.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/12/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include "GowMemoryAllocator.hpp"

#include <data_structures/GowArray.hpp>

template <typename T>
class Pool
{
public:
    Pool()
    {
        // Empty
    }
    
    ~Pool()
    {
        for (size_t i = 0; i < _objects.size(); )
        {
            T* item = _objects[i];
            GOW_DESTROY(item, T);
            
            _objects.erase(i);
        }
    }
    
    T* obtain()
    {
        if (_objects.size() > 0)
        {
            T** object = _objects.begin();
            _objects.erase(0);
            
            return *object;
        }
        else
        {
            T* ret = GOW_NEW(T);
            new (ret) T();
            
            return ret;
        }
    }
    
    void free(T* object)
    {
        if (!_objects.contains(object))
        {
            _objects.push_back(object);
        }
    }
    
private:
    GowArray<T*> _objects;
};
