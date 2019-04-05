//
//  main.cpp
//  Searching
//
//  Created by Иван Медведев on 08/03/2019.
//  Copyright © 2019 Medvedev. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include "Tree.h"





int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(0));
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    
    Clock::time_point start;
    Clock::time_point end;
    microseconds ms;

    double sumTime = 0;
    int numberOfElements = 1000;
    
    Tree<int> DEREVO;
    for(int i=0;i<numberOfElements;i++) {
        DEREVO.insert_node(i);
    }
    
    for(int i=0; i<numberOfElements;i++)
    {
    start = Clock::now();
    DEREVO.preorder_iter(DEREVO.get_root());
    end = Clock::now();
    ms = std::chrono::duration_cast<microseconds>(end - start);
    sumTime+= (double)ms.count()/1000000;
    }
    double res1 = sumTime;

    
    sumTime = 0;
    
    for(int i=0; i<numberOfElements;i++)
    {
    start = Clock::now();
    DEREVO.preorder_walk(DEREVO.get_root());
    end = Clock::now();
    ms = std::chrono::duration_cast<microseconds>(end - start);
    sumTime+= (double)ms.count()/1000000;
    }
    std::cout << "Binary Tree preorder_iter: " << std::fixed << res1/(double)numberOfElements << " s" << std::endl;
    std::cout << "Binary Tree preorder_walk: " << std::fixed << sumTime/(double)numberOfElements  << " s" << std::endl;
    
    
    
    return 0;
}
