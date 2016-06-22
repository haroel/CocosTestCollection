//
//  TwistNode.hpp
//  MyGameCpp
//
//  Created by howe on 15/8/25.
//
//

#ifndef TwistNode_hpp
#define TwistNode_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class TwistNode : public Sprite
{
public:
    CREATE_FUNC(TwistNode);
    
    
    void setTexture(const std::string &source,const std::string &destination,float duration);
    
private:
    void _callHandler(float t);
};

#endif /* TwistNode_hpp */
