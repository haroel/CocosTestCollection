//
//  MainScene.cpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#include "MainScene.hpp"
#include "mc/UINumberPicker.h"

#include "mc/TwistNode.h"
#include "mc/PolygonSprite.h"
#include "mc/SwipItemView.hpp"
#include "mc/GLVBOTest.hpp"
#include "mc/CppTestLayer.hpp"
#include "mc/ShaderTest.hpp"


using namespace cocos2d;

std::map<std::string,int> g_MenuItemMap;

void MainScene::onEnter()
{
    Scene::onEnter();
    
    std::vector<std::string> list = {"picker","TwistNode","侧滑按钮","PolygonSprite","GLTest","c++测试","Shader测试"};
    
    for (auto ss : list)
    {
        g_MenuItemMap[ss] = (int)g_MenuItemMap.size();
    }

    //Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::AUTO);
    Size winsize = Director::getInstance()->getWinSize();
    MenuItemFont::setFontName("Arial");
    Vector<MenuItem*> items;
    for (auto ite : g_MenuItemMap)
    {
        auto item =  MenuItemFont::create(ite.first.c_str(), CC_CALLBACK_1(MainScene::menuClickHandler, this) );
        item->setTag(ite.second);
        items.pushBack(item);
        item->getLabel()->setColor({22,22,22});
    }
    auto layer = LayerColor::create(ccc4(255,255,255,255));
    this->addChild(layer);
    
//    auto bgSprite = Sprite::create("res/Frog.jpg");
//    bgSprite->setPosition({winsize.width/2,winsize.height/2});
//    this->addChild(bgSprite);
//    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(items);
    menu->setPosition({100,winsize.height/2});
    menu->alignItemsVerticallyWithPadding(2);
    this->addChild(menu);
    
    _contentNode = Node::create();
    this->addChild(_contentNode);
    
    CCLOG( Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str() );
    
//    this->schedule(schedule_selector(MainScene::delayDoHandler), 4.0);
}
void MainScene::delayDoHandler(float t)
{
    Size winsize = Director::getInstance()->getWinSize();

    _contentNode->removeAllChildrenWithCleanup(true);
    auto container = _contentNode;
    auto pNode = TwistNode::create();
    pNode->setPosition(winsize.width/2, winsize.height/2);
    container->addChild(pNode);
}
void MainScene::menuClickHandler(Ref* pSender)
{
    _contentNode->removeAllChildrenWithCleanup(true);
    auto container = _contentNode;
    int tag = dynamic_cast<Node*>(pSender)->getTag();
    
    Size winsize = Director::getInstance()->getWinSize();
    
    switch (tag) {
        case 0:
        {
            auto pNode = PickerTest::create();
            pNode->setPosition(winsize.width/2, winsize.height/2);
            container->addChild(pNode);
            break;
        }
        case 1:
        {
            auto pNode = TwistNode::create();
            pNode->setPosition(winsize.width/2, winsize.height/2);
            container->addChild(pNode);
            break;
        }
        case 2:
        {
            auto pNode = SwipItemView::create();
            pNode->setPosition(winsize.width/2, winsize.height/2);
            container->addChild(pNode);
            break;
        }
        case 3:
        {
            auto ppp = PolygonSpriteTest::create();
            ppp->setPosition(winsize.width/2, winsize.height/2);
            container->addChild(ppp);
            break;
        }
        case 4:
        {
            auto ppp = GLVBOTest::create();
            ppp->setPosition(winsize.width/2, winsize.height/2);
            container->addChild(ppp);
            break;
        }
        case 5:
        {
            auto ppp = CppTestLayer::create();
            ppp->setPosition(winsize.width/2, winsize.height/2);
            container->addChild(ppp);
            break;
        }
        case 6:
        {
            auto ppp = ShaderTest::create();
            ppp->setPosition(winsize.width/2, winsize.height/2);
            container->addChild(ppp);
            break;
        }
        default:
            break;
    }
    
}