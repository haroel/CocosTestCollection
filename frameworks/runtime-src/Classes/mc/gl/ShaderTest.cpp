//
//  ShaderTest.cpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#include "ShaderTest.hpp"
#include "ProgressAction.hpp"

#include "cocos2d.h"
using namespace cocos2d;

void ShaderSprite::onEnter()
{
    Sprite::onEnter();
    

    this->initWithFile("res/HelloWorld.png");
    
    
//    auto texture = Director::getInstance()->getTextureCache()->addImage("res/twist/IMG_1825.PNG");
    
    auto fragStr = FileUtils::getInstance()->getStringFromFile("res/gltest/progreetimer.fsh");    
    auto pstate = GLProgramState::create( GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragStr.c_str()) );
//    pstate->setUniformTexture("u_textureTo", texture);
    pstate->setUniformFloat("u_progress", 0);
    pstate->setUniformFloat("u_start", 0.0);

    this->setGLProgramState(pstate);
    
    auto act = new ProgressAction();
    act->initWithDuration(5);
    
    act->callBack = std::bind(&ShaderSprite::_callHandler, this,std::placeholders::_1);
    this->runAction(act);
    
}

void ShaderSprite::_callHandler(float t)
{
    if (t > 0.1)
    {
//        return;
    }
    CCLOG("progress %f",t);
    auto pstate = this->getGLProgramState();
    pstate->setUniformFloat("u_progress", t);
}

