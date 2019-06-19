//
//  HashMapUtil.h
//  HashMap
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#ifndef sgowen_HashMapUtil_h
#define sgowen_HashMapUtil_h

#include <hash_map/HashMap.h>

#include <vector/Extension.h>

#include <string>
#include <assert.h>

class HashMapUtil
{
public:
    template<typename K, typename T, typename H>
    static void cleanUpHashMapOfPointers(HashMap<K, T*, H>& hashMap)
    {
        for (typename HashMap<K, T*, H>::Iterator i = hashMap.begin(); i != hashMap.end(); )
        {
            DESTROY(T, i.second());
            
            i = hashMap.erase(i);
        }
    }
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    HashMapUtil();
    HashMapUtil(const HashMapUtil&);
    HashMapUtil& operator=(const HashMapUtil&);
};

#endif /* sgowen_HashMapUtil_h */
