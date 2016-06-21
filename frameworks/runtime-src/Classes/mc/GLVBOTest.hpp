//
//  GLVBOTest.hpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#ifndef GLVBOTest_hpp
#define GLVBOTest_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class GLVBOTest : public Layer
{
public:
    
    CREATE_FUNC(GLVBOTest);
    
    virtual bool init() override;
    
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
private:
    void onDraw();
    
    void initGLConfig();
    
    void initGLConfigWithIndex();
    
private:
    CustomCommand _renderCommand;

};

#endif /* GLVBOTest_hpp */
