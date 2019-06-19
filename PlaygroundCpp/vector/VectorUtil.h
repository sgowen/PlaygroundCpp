//
//  VectorUtil.h
//  Vector
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#ifndef sgowen_VectorUtil_h
#define sgowen_VectorUtil_h

#include <vector/Extension.h>
#include <vector/Vector.h>

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
    // ctor, copy ctor, and assignment should be private in a Singleton
    VectorUtil();
    VectorUtil(const VectorUtil&);
    VectorUtil& operator=(const VectorUtil&);
};

#endif /* sgowen_VectorUtil_h */
