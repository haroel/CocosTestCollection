//
//  MProgressTimer.hpp
//  MyTestCollection
//
//  Created by Howe on 16/6/22.
//
//

#ifndef MProgressTimer_hpp
#define MProgressTimer_hpp

#include <stdio.h>


#include "cocos2d.h"

#include <iostream>

using namespace cocos2d;
using namespace std;

class MProgressTimer : public Sprite
{
public:
    CREATE_FUNC(MProgressTimer);
    
    
    void setTexture(const std::string &source,float duration);

private:
    
    void _callHandler(float t);
    
};


#endif /* MProgressTimer_hpp */
