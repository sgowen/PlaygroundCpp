//
//  main.cpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#include <bitmask/BitMaskTest.h>
#include <casting/CastingTest.h>
#include <endianness/EndiannessTest.h>
#include <hash_map/HashMapTest.h>
#include <math/MathTest.h>
#include <memory/MemoryTest.h>
#include <operator/BitwiseOperatorTest.h>
#include <pool/PoolTest.h>
#include <random_file_access/RandomFileAccessTest.h>
#include <sin_table/SinTableTest.h>
#include <string_split/StringSplitTest.h>
#include <threading/ThreadingTest.h>
#include <uniqueness/UniquenessTest.h>
#include <vector/VectorTest.h>
#include <vector/Extension.h>

int main(int argc, const char* argv[])
{
    NGExtension::setInstance(DefaultNGExtension::getInstance());
    
    BitMaskTest::test();
//    CastingTest::test();
//    EndiannessTest::test();
//    HashMapTest::test();
//    MathTest::test();
//    MemoryTest::test();
//    BitwiseOperatorTest::test();
//    PoolTest::test();
//    RandomFileAccessTest::test();
//    SinTableTest::test();
//    StringSplitTest::test();
//    ThreadingTest::test();
//    UniquenessTest::test();
//    VectorTest::test();
}
