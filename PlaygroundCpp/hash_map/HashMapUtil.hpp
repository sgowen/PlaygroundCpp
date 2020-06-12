//
//  HashMapUtil.hpp
//  HashMap
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include <hash_map/HashMap.hpp>

#include <vector/Extension.hpp>

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
    HashMapUtil();
    ~HashMapUtil();
    HashMapUtil(const HashMapUtil&);
    HashMapUtil& operator=(const HashMapUtil&);
};
