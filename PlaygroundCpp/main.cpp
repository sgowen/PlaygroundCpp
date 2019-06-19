//
//  main.cpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#include <casting/CastingTest.h>
#include <endianness/EndiannessTest.h>
#include <hash_map/HashMapTest.h>
#include <math/MathTest.h>
#include <memory/MemoryTest.h>
#include <operator/BitwiseOperatorTest.h>
#include <pool/PoolTest.h>
#include <sin_table/SinTableTest.h>
#include <threading/ThreadingTest.h>
#include <uniqueness/UniquenessTest.h>
#include <vector/VectorTest.h>
#include <vector/Extension.h>

int main(int argc, const char * argv[])
{
    NGExtension::setInstance(DefaultNGExtension::getInstance());
    
//    CastingTest::test();
//    EndiannessTest::test();
//    HashMapTest::test();
    MathTest::test();
//    MemoryTest::test();
//    BitwiseOperatorTest::test();
//    PoolTest::test();
//    SinTableTest::test();
//    ThreadingTest::test();
//    UniquenessTest::test();
//    VectorTest::test();
}
