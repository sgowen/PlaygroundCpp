//
//  VectorUtil.hpp
//  Vector
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include "Extension.hpp"
#include "Vector.hpp"

class VectorUtil
{
public:
    template<typename T>
    static void cleanUpVectorOfPointers(Vector<T*>& items)
    {
        for (size_t i = 0; i < items.size(); )
        {
            T* item = items[i];
            DESTROY(T, item);
            
            items.erase(i);
        }
    }
    
private:
    VectorUtil();
    ~VectorUtil();
    VectorUtil(const VectorUtil&);
    VectorUtil& operator=(const VectorUtil&);
};
