//
//  QueueTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 12/11/19.
//  Copyright © 2019 Stephen Gowen. All rights reserved.
//

#pragma once

#include <inttypes.h>
#include <iostream>
#include <queue>

class QueueTest
{
public:
    static void test()
    {
        std::queue<int> myqueue;

        myqueue.push(3);
        myqueue.push(6);
        myqueue.push(9);
        myqueue.push(2);
        myqueue.push(4);
        myqueue.push(1);

        std::cout << "myqueue contains: ";
        while (!myqueue.empty())
        {
          std::cout << ' ' << myqueue.front();
          myqueue.pop();
        }
        std::cout << '\n';
    }
    
private:
    QueueTest();
    ~QueueTest();
    QueueTest(const QueueTest&);
    QueueTest& operator=(const QueueTest&);
};
