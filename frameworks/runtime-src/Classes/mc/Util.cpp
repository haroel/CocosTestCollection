//
//  Util.cpp
//  MyTestCollection
//
//  Created by Howe on 16/1/2.
//
//

#include "Util.hpp"
#include<sys/time.h>

uint64_t getTickCount()
{
    struct timeval tv;
    gettimeofday((struct timeval *)&tv,  0);
    uint64_t cur_ticktime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    
    return cur_ticktime;
}