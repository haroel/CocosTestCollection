//
//  PolygonSprite.hpp
//  MyGameCpp
//
//  Created by howe on 15/6/17.
//
//

#ifndef PolygonSprite_hpp
#define PolygonSprite_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
/**
 使用方式：
 
 auto ppp = PolygonSprite::create("res/img_4.png");
 ppp->setCCRotation(1); // 逆时针旋转
 auto pNode = ParticleSystemQuad::create("res/cc.plist");
 pNode->setScale(0.6);
 ppp->setActionNode( pNode );
 ppp->setPosition(100, 130);
 ppp->setTimeScale(120);
 this->addChild(ppp);

 */
class PolygonSprite : public Sprite
{
public:
    PolygonSprite()
    :_ccRotation(1),
    _timeScale(100),
    _actionNode(nullptr),
    _isInvaildDisplay(false)
    {}
    
    static PolygonSprite* create(const std::string& filename);
    
    /** 设定运动方向 0表示顺时针，1表示逆时针 */
    void setCCRotation(int value);
    
    /** 设定运动目标速度，默认值100 ，速度越大运动越快*/
    void setTimeScale(int timeScale);
    
    /** 设定运动目标对象，可以是粒子，序列帧等可视化对象 */
    void setActionNode(Node * node);
    
    /** 运动目标粒子对象文件名路径 */
    ParticleSystem* setParticleNode(const std::string &praticleFile);

    /** 判断点是否在Sprite有效像素区域内 */
    bool pointInSprite(const Vec2& point);
    
    /*** update sprite verts **/
    void updateVerts();
    
    void invalidateDisplayList();
    void updateDisplayList();
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
private:
    int _timeScale;
    int _ccRotation;
    bool _isInvaildDisplay;
    
    Node * _actionNode;
    
    std::vector<Vec3> _spVerts;
    
};
/**********************************************************************************************************/

class PolygonSpriteTest : public Layer
{
public:
    CREATE_FUNC(PolygonSpriteTest);
    
    
    virtual void onEnter() override
    {
        Layer::onEnter();
        
        auto ppp1 = PolygonSprite::create("res/poly/img_n.png");
        ppp1->setCCRotation(0);
        auto pNode1 = ParticleSystemQuad::create("res/poly/cc.plist");
        pNode1->setScale(0.3);
        ppp1->setActionNode( pNode1 );
        ppp1->setTimeScale(50);
        this->addChild(ppp1);
    }
};
#endif /* PolygonSprite_h */
