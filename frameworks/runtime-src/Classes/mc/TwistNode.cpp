//
//  TwistNode.cpp
//  MyGameCpp
//
//  Created by howe on 15/8/25.
//
//

#include "TwistNode.h"
using namespace cocos2d;

float width = 200;
float height = 100;

void TwistNode::onEnter()
{
    Sprite::onEnter();
    
    
    this->initWithFile("res/twist/a1.jpg");
    
    
    auto texture = Director::getInstance()->getTextureCache()->addImage("res/twist/a2.jpg");
    
    auto fragStr = FileUtils::getInstance()->getStringFromFile("res/twist/twist.fsh");
    auto vertStr = FileUtils::getInstance()->getStringFromFile("res/twist/twist.vert");

    auto pstate = GLProgramState::create( GLProgram::createWithByteArrays(vertStr.c_str(), fragStr.c_str()) );
    pstate->setUniformTexture("u_textureTo", texture);    
    pstate->setUniformFloat("u_progress", 0);

    this->setGLProgramState(pstate);
    
    auto act = new ProgressAction();
    act->initWithDuration(1.5);
    
    act->callBack = std::bind(&TwistNode::_callHandler, this,std::placeholders::_1);
    this->runAction(act);
    
}
void TwistNode::_callHandler(float t)
{
    CCLOG("progress %f",t);
    auto pstate = this->getGLProgramState();
    pstate->setUniformFloat("u_progress", t);
}