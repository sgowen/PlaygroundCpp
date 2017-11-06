//
//  HashMapUtil.h
//  HashMap
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef NoctisGames_HashMapUtil_h
#define NoctisGames_HashMapUtil_h

#include <hash_map/HashMap.h>

#include <string>
#include <assert.h>

namespace NoctisGames
{
    class HashMapUtil
    {
    public:
        template<typename K, typename T, typename H>
        static void cleanUpHashMapOfPointers(HashMap<K, T*, H>& hashMap)
        {
            for (typename HashMap<K, T*, H>::Iterator i = hashMap.begin(); i != hashMap.end(); )
            {
                delete i.second();
                
                i = hashMap.erase(i);
            }
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        HashMapUtil();
        HashMapUtil(const HashMapUtil&);
        HashMapUtil& operator=(const HashMapUtil&);
    };
}

#endif /* NoctisGames_HashMapUtil_h */
