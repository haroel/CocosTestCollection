//
//  M2DRotation.cpp
//  MyTestCollection
//
//  Created by Howe on 2017/3/1.
//
//

#include "M2DRotation.hpp"

void M2DRotation::setTexture(const std::string &source)
{
    this->initWithFile(source);
//    this->setAnchorPoint(Vec2(0.5, 0));
    this->getTexture()->setAntiAliasTexParameters();
    auto vertStr = FileUtils::getInstance()->getStringFromFile("res/gltest/2dper.vert");
    auto fragStr = FileUtils::getInstance()->getStringFromFile("res/gltest/2dper.fsh");

    auto pstate = GLProgramState::create( GLProgram::createWithByteArrays(vertStr.c_str(), fragStr.c_str()) );
    
    Mat4 rmat;
    Mat4::createRotationX(-3.1415926/6, &rmat);
    pstate->setUniformMat4("u_rotation", rmat);
    //    pstate->setUniformTexture("u_textureTo", texture);
//    pstate->setUniformFloat("u_progress", 0);
//    pstate->setUniformFloat("u_start", 0.11);
    
    this->setGLProgramState(pstate);
    
    
}
