//
//  TwistNode.cpp
//  MyGameCpp
//
//  Created by howe on 15/8/25.
//
//

#include "TwistNode.h"
#include "ProgressAction.hpp"

using namespace cocos2d;


void TwistNode::setTexture(const std::string &path1,const std::string &path2,float duration)
{
    this->initWithFile(path1);
    
    
    auto texture = Director::getInstance()->getTextureCache()->addImage(path2);
    
    auto fragStr = FileUtils::getInstance()->getStringFromFile("res/twist/twist.fsh");
    auto vertStr = FileUtils::getInstance()->getStringFromFile("res/twist/twist.vert");
    
    auto pstate = GLProgramState::create( GLProgram::createWithByteArrays(vertStr.c_str(), fragStr.c_str()) );
    pstate->setUniformTexture("u_textureTo", texture);
    pstate->setUniformFloat("u_progress", 0);
    
    this->setGLProgramState(pstate);
    
    auto act = new ProgressAction();
    act->initWithDuration(duration);
    
    act->callBack = std::bind(&TwistNode::_callHandler, this,std::placeholders::_1);
    this->runAction(act);

}

void TwistNode::_callHandler(float t)
{
//    CCLOG("progress %f",t);
    auto pstate = this->getGLProgramState();
    pstate->setUniformFloat("u_progress", t);
}