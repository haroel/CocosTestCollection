//
//  ProgressAction.hpp
//  MyTestCollection
//
//  Created by Howe on 16/6/22.
//
//

#ifndef ProgressAction_hpp
#define ProgressAction_hpp

#include <stdio.h>

#include "cocos2d.h"
using namespace cocos2d;


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


#endif /* ProgressAction_hpp */
