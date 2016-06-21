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
    
    virtual void onEnter();
    
    void _callHandler(float t);
};

class ProgressAction : public cocos2d::ActionInterval
{
public:
    ProgressAction()
    :callBack(nullptr)
    {
        
    }
    bool initWithDuration(float duration)
    {
        return ActionInterval::initWithDuration(duration);
    }
    virtual void startWithTarget(Node *pTarget)
    {
        ActionInterval::startWithTarget(pTarget);
    }
    virtual void update(float time)
    {
        if (callBack)
        {
            callBack(time);
        }
    }
public:
    std::function<void(float progress)> callBack;
    
    
};

#endif /* TwistNode_hpp */
