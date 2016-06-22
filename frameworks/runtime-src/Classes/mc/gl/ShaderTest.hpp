//
//  ShaderTest.hpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#ifndef ShaderTest_hpp
#define ShaderTest_hpp

#include <stdio.h>
#include "cocos2d.h"

#include <iostream>

using namespace cocos2d;
using namespace std;

class ShaderSprite : public Sprite
{
public:
    CREATE_FUNC(ShaderSprite);
    
    virtual void onEnter() override;
    
    void _callHandler(float t);

};

class ShaderTest : public Layer
{
    
public:
    CREATE_FUNC(ShaderTest);
    
    virtual void onEnter() override
    {
        Layer::onEnter();
        auto sp = ShaderSprite::create();
//        "res/poly/img_n.png");
//        auto fragStr = FileUtils::getInstance()->getStringFromFile("res/gltest/shadertest.fsh");
//        
//        auto pstate = GLProgramState::create( GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert, fragStr.c_str()) );
//        sp->setGLProgramState(pstate);
        
        this->addChild(sp);
    }
};
#endif /* ShaderTest_hpp */
