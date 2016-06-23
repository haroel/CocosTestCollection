//
//  MProgressTimer.cpp
//  MyTestCollection
//
//  Created by Howe on 16/6/22.
//
//

#include "MProgressTimer.hpp"
#include "ProgressAction.hpp"

void MProgressTimer::setTexture(const std::string &source,float duration)
{
    this->initWithFile(source);
    
    auto fragStr = FileUtils::getInstance()->getStringFromFile("res/gltest/progreetimer.fsh");
    auto pstate = GLProgramState::create( GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragStr.c_str()) );
    //    pstate->setUniformTexture("u_textureTo", texture);
    pstate->setUniformFloat("u_progress", 0);
    pstate->setUniformFloat("u_start", 0.11);
    
    this->setGLProgramState(pstate);
    
    auto act = new ProgressAction();
    act->initWithDuration(duration);
    act->autorelease();
    act->callBack = std::bind(&MProgressTimer::_callHandler, this,std::placeholders::_1);
    this->runAction(act);
    
}

void MProgressTimer::_callHandler(float t)
{    auto pstate = this->getGLProgramState();
    pstate->setUniformFloat("u_progress", t);
}
