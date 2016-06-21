//
//  MainScene.hpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(MainScene);
    
    virtual void onEnter() override;
    
    void menuClickHandler(Ref* pSender);
    void delayDoHandler(float t);
private:
    
    cocos2d::Node * _contentNode;
};


#endif /* MainScene_hpp */
