//
//  SwipItemView.cpp
//  MyGameCpp
//
//  Created by howe on 15/10/28.
//
//

#include "SwipItemView.hpp"

void SwipItemView::onEnter()
{
    Layer::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(SwipItemView::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(SwipItemView::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(SwipItemView::onTouchEnded, this);
    
    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
 
    _contentContainer =Node::create();
    this->addChild(_contentContainer,1);
    
    _sp = Sprite::create("res/swip/swipItemBg.png");
    _sp->setAnchorPoint(Size::ZERO);
    _contentContainer->addChild(_sp);
    this->setContentSize( _sp->getContentSize() );
    
    _deleteBtn = Sprite::create("res/swip/swip_dele.png");
    _deleteBtn->setPosition( getContentSize().width - _deleteBtn->getContentSize().width/2 , getContentSize().height/2);
    this->addChild(_deleteBtn,-1);
    
}

void SwipItemView::onExit()
{
    this->unschedule(schedule_selector(SwipItemView::touchDelayHandler));
    Layer::onExit();
}

void SwipItemView::runBackToStartPoint()
{
    _contentContainer->stopAllActions();
    _contentContainer->runAction(MoveTo::create(fabsf(_contentContainer->getPositionX())/200, Vec2(0, 0)));
}

void SwipItemView::runToDeleteState()
{
    Vec2 desPoint(-_deleteBtn->getContentSize().width,0);
    _contentContainer->stopAllActions();
    float dis = desPoint.getDistance(_contentContainer->getPosition());
    if (dis > 0.1)
    {
        _contentContainer->runAction(MoveTo::create( dis /100, desPoint));
    }
}

void SwipItemView::setSelected(bool value)
{
    if (m_isSelected == value)
    {
        return;
    }
    m_isSelected = value;
    if (m_isSelected)
    {
        _sp->setColor(Color3B(100, 100, 100));
        
    }else
    {
        _sp->setColor(Color3B(255, 255, 255));
    }
}
bool SwipItemView::isInSwip()
{
    return _contentContainer->getPositionX() <= -_deleteBtn->getContentSize().width;
}

bool SwipItemView::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    this->unschedule(schedule_selector(SwipItemView::touchDelayHandler));
    do
    {
        m_bTouchMoved = false;
        m_tTouchPoint = std::move(convertTouchToNodeSpace(touch));
        
        auto &size = getContentSize();
        Rect rect(0,0,size.width,size.height);
        
        if (rect.containsPoint(m_tTouchPoint))
        {
            if (_contentContainer->getPositionX() == 0)
            {
                this->schedule(schedule_selector(SwipItemView::touchDelayHandler), 0.1f);
            }else
            {
                Rect delRect(0,0,size.width + _contentContainer->getPositionX(),size.height );
                if ( delRect.containsPoint( m_tTouchPoint ) )
                {
                    runBackToStartPoint();
                    break;
                }
            }
            return true;
        }
    } while (0);
    setSelected(false);
    return false;

}
void SwipItemView::touchDelayHandler(float dt)
{
    this->unschedule(schedule_selector(SwipItemView::touchDelayHandler));
    setSelected(true);
    
}
void SwipItemView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    m_bTouchMoved = true;
    setSelected(false);

    this->unschedule(schedule_selector(SwipItemView::touchDelayHandler));
    
    const Vec2 &newPoint = convertTouchToNodeSpace(touch);
    const static float PRE_CI_SION = 12;
    if (_contentContainer->getPositionX() > PRE_CI_SION)
    {
        return;
    }
    
    float max_x = -_deleteBtn->getContentSize().width - PRE_CI_SION;
    if (max_x < _contentContainer->getPositionX())
    {
        float dx = newPoint.x - m_tTouchPoint.x;
        _contentContainer->setPositionX( _contentContainer->getPositionX() + dx );
        m_tTouchPoint = std::move( newPoint );
    }
}
bool isInInterval(float min,float max,float z)
{
    return z > min && z < max;
}
void SwipItemView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    this->unschedule(schedule_selector(SwipItemView::touchDelayHandler));

    if (m_isSelected)
    {
        CCLOG("你选中了item！");
        m_bTouchMoved = false;
        return;
    }
    
    const Vec2 &startPoint = convertToNodeSpace(touch->getStartLocation());
    const Vec2 &newPoint = convertTouchToNodeSpace(touch);
    
    float contentXPos = _contentContainer->getPositionX();
    const Size &allSize = getContentSize();
    const Size &delSize = _deleteBtn->getContentSize();
    
    if (isInSwip() &&
        isInInterval(allSize.width-delSize.width,allSize.width,startPoint.x) &&
        isInInterval(allSize.width-delSize.width,allSize.width,newPoint.x))
    {
        CCLOG("删除Item！！");
        this->resetItemView();
        MessageBox("删除Item", "提示");
        return;
    }
    if (startPoint.x > newPoint.x)
    {
        // 向左滑动
        if ( contentXPos < -delSize.width/2)
        {
            this->runToDeleteState();
        }else
        {
            this->runBackToStartPoint();
        }
    }else
    {
        // 向左滑动
        this->runBackToStartPoint();
    }
}
void SwipItemView::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    runBackToStartPoint();
    resetItemView();
}

void SwipItemView::resetItemView()
{
    m_bTouchMoved = false;
    setSelected(false);
    this->unschedule(schedule_selector(SwipItemView::touchDelayHandler));
}

