//
//  main.cpp
//  TestHarness
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include <endianness/EndiannessTest.h>
#include <hash_map/HashMapTest.h>
#include <memory/MemoryTest.h>
#include <operator/BitwiseOperatorTest.h>
#include <pool/PoolTest.h>
#include <sin_table/SinTableTest.h>
#include <uniqueness/UniquenessTest.h>
#include <vector/VectorTest.h>
#include <vector/Extension.h>

int main(int argc, const char * argv[])
{
    using namespace NoctisGames;
    
    NGExtension::setInstance(DefaultNGExtension::getInstance());
    
    EndiannessTest::test();
    
    HashMapTest::test();

    MemoryTest::test();

    BitwiseOperatorTest::test();
    
    PoolTest::test();

    SinTableTest::test();

    UniquenessTest::test();

    VectorTest::test();
}
