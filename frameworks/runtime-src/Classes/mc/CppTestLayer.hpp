//
//  CppTestLayer.hpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#ifndef CppTestLayer_hpp
#define CppTestLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

#include <iostream>

using namespace cocos2d;
using namespace std;

class CppTestLayer : public Layer
{
public:
    
    CREATE_FUNC(CppTestLayer);
    
    virtual void onEnter() override;
    
private:
    
private:
    
};


class Base
{
    
public:
    Base()
    {}
    ~Base()
    {
        cout << "Base::~Base" << endl;
    }
    
    void func2() const
    {};
    void doWithTarget( Base * const pTarget)
    {
        pTarget->testI = 10;
    }
    
    int testI;
private:
    
    virtual void f()
    {
        cout << "Base::f" << endl;
    }
    virtual void g()
    {
        cout << "Base::g" << endl;
    }
    virtual void h()
    {
        cout << "Base::h" << endl;
    }
};

class InstanceBase : public Base
{
    
public:
    InstanceBase()
    {}
    
    ~InstanceBase()
    {
        cout << "InstanceBase::~InstanceBase" << endl;
    }
};

#endif /* CppTestLayer_hpp */
