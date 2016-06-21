//
//  GLVBOTest.cpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#include "GLVBOTest.hpp"


GLuint _gvao;
GLuint elementbuffer;

bool GLVBOTest::init()
{
    initGLConfigWithIndex();
    
    return Layer::init();
}

void GLVBOTest::initGLConfig()
{
//    auto size = Director::getInstance()->getWinSize();
//    float vertercies[] = { 0,0,   //第一个点的坐标
//        size.width, 0,   //第二个点的坐标
//        size.width / 2, size.height};  //第三个点的坐标
//    //指定每一个顶点的颜色，颜色值是RGBA格式的，取值范围是0-1
//    float color[] = { 0.0, 1.0,0.0, 1.0,    //第一个点的颜色，绿色
//        1.0,0.0,0.0, 1.0,  //第二个点的颜色, 红色
//        0.0, 0.0, 1.0, 1.0};  //第三个点的颜色， 蓝色
//    auto program = this->getGLProgram();
//    program->use();
//    program->setUniformsForBuiltins();
//    
//    glGenVertexArrays(1, &_gvao);
//    glBindVertexArray(_gvao);
//    
//    GLuint _vertexVBO;
//    glGenBuffers(1, &_vertexVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertercies), vertercies, GL_STATIC_DRAW);
//    
//    GLuint posLocation = glGetAttribLocation(program->getProgram(), "a_position");
//    glEnableVertexAttribArray(posLocation);
//    glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
//    
//    GLuint _colorVBO;
//    glGenBuffers(1, &_colorVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
//    
//    GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
//    glEnableVertexAttribArray(colorLocation);
//    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
//    
//    glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GLVBOTest::initGLConfigWithIndex()
{
    auto size = Director::getInstance()->getWinSize();
    
    float vertercies[] =
    { 0,0,
        200.0, 0,
        0, 250.0,
        200.0,200.0};
    //指定每一个顶点的颜色，颜色值是RGBA格式的，取值范围是0-1
    float color[] = { 1.0, 0.0,0.0, 1.0,    //第一个点的颜色，绿色
        0.0,1.0,0.0, 1.0,  //第二个点的颜色, 红色
        0.0, 0.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0
        //        1.0, 1.0, 1.0, 1.0,
        //        0.2,0.2,0.2,1.0
    };  //第三个点的颜色， 蓝色
    GLubyte indices [] = {
        0,1,2,
        2,3,1
    };
    auto fragStr = FileUtils::getInstance()->getStringFromFile("res/gltest/shadertest.fsh");
    
    auto pstate = GLProgramState::create( GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert, fragStr.c_str()) );
    this->setGLProgramState(pstate);
    
    auto program = this->getGLProgram();
    program->use();
    program->setUniformsForBuiltins();
    // ----------------------------------------------------
    GLuint _vertexVBO;
    glGenBuffers(1, &_vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertercies), vertercies, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &_gvao);
    glBindVertexArray(_gvao);
    
    
    GLuint posLocation = glGetAttribLocation(program->getProgram(), "a_position");
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    // ----------------------------------------------------
    
    GLuint _colorVBO;
    glGenBuffers(1, &_colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    
    GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLVBOTest::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags)
{
    Layer::visit(renderer, parentTransform, parentFlags);
    _renderCommand.init(_globalZOrder);
    _renderCommand.func = std::bind(&GLVBOTest::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_renderCommand);
}
void GLVBOTest::onDraw()
{
    auto program = this->getGLProgram();
    program->use();
    program->setUniformsForBuiltins();
    glBindVertexArray(_gvao);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
    
    
}

