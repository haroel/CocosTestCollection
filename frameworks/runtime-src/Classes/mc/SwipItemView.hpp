//
//  SwipItemView.hpp
//  MyGameCpp
//
//  Created by howe on 15/10/28.
//
//

#ifndef SwipItemView_hpp
#define SwipItemView_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class SwipItemView : public Layer
{
public:
    SwipItemView()
    :m_bTouchMoved(false),
    m_isSelected(false)
    {
    }
    CREATE_FUNC(SwipItemView);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool isInSwip();
    
    void touchDelayHandler(float dt);
    
private:
    
    void runBackToStartPoint();
    void runToDeleteState();

    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
    virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
    virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
    virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;
    
    void setSelected(bool value);
    void resetItemView();
private:
    bool m_bTouchMoved;
    bool m_isSelected;
    
    Vec2 m_tTouchPoint;
    Node * _contentContainer;
    Node * _deleteBtn;
    
private:
    Sprite * _sp;
    
};

#endif /* SwipItemView_hpp */
