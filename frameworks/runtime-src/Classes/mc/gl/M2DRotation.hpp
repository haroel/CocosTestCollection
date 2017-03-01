//
//  M2DRotation.hpp
//  MyTestCollection
//
//  Created by Howe on 2017/3/1.
//
//

#ifndef M2DRotation_hpp
#define M2DRotation_hpp

#include <stdio.h>

#include "cocos2d.h"

#include <iostream>

using namespace cocos2d;
using namespace std;

class M2DRotation : public Sprite
{
public:
    CREATE_FUNC(M2DRotation);
    
    
    void setTexture(const std::string &source);
    
    
};
#endif /* M2DRotation_hpp */
