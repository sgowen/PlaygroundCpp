//
//  Pool.h
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/12/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#ifndef sgowen_Pool_h
#define sgowen_Pool_h

#include <vector/Vector.h>
#include <vector/VectorUtil.h>
#include <vector/Extension.h>

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
        VectorUtil::cleanUpVectorOfPointers(_objects);
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
            T* ret = NEW(T);
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
    Vector<T*> _objects;
};

#endif /* sgowen_Pool_h */
