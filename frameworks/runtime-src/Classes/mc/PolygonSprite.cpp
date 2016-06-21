//
//  PolygonSprite.cpp
//  MyGameCpp
//
//  Created by howe on 15/6/17.
//
//

#include "PolygonSprite.h"

#define DIS_PRECISION      6.0f    /**** 顶点距离差异的精度 **/

float getVect3Angle(const Vec3 &vet1)
{
    return atan2f(vet1.x, vet1.y);
}

float getVect3Angle(const Vec3 &vet1,const Vec3 &vet2)
{
    return atan2f(vet1.x -vet2.x, vet1.y -vet2.y);
}

float getDistance(const Vec3 &vet1,const Vec3 &vet2)
{
    float dx = vet1.x - vet2.x;
    float dy = vet1.y - vet2.y;
    return sqrt(dx * dx + dy * dy);
}

//*** BEGIN ****/
inline int chg_sign(int x, int sign)
{
    return (x + sign) ^ sign;
}
bool is_point_in_triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Vec2& p)
{
    Vec2 ab(b.x -a.x,b.y-a.y), ac(c.x - a.x,c.y-a.y), ap(p.x - a.x,p.y-a.y);
    int abc = ab.cross(ac);
    int abp = ab.cross(ap);
    int apc = ap.cross(ac);
    int pbc = abc - abp - apc;
    const int sign = (abc >= 0) - 1;
    
    return (chg_sign(abp, sign) | chg_sign(apc, sign) | chg_sign(pbc, sign)) >= 0;
}
//*** END ****/


#pragma mark - PolygonSprite -
PolygonSprite* PolygonSprite::create(const std::string& filename)
{
    PolygonSprite *reSprite = new (std::nothrow) PolygonSprite();
    if(reSprite && reSprite->initWithPolygon(AutoPolygon::generatePolygon(filename,Rect::ZERO,1.4)))
    {
        reSprite->autorelease();
//        reSprite->debugDraw(false);
        return reSprite;
    }
    CC_SAFE_DELETE(reSprite);
    return nullptr;
}

bool PolygonSprite::pointInSprite(const cocos2d::Vec2 &point)
{
    const auto &polyInfo = getPolygonInfo();

    auto last = polyInfo.triangles.indexCount/3;
    auto _indices = polyInfo.triangles.indices;
    auto _verts = polyInfo.triangles.verts;
    // 判断点是否在三角形组内
    for(unsigned int i = 0; i < last; i++)
    {
        const Vec3 &pot1 =_verts[_indices[i*3]].vertices;
        const Vec3 &pot2 = _verts[_indices[i*3+1]].vertices;
        const Vec3 &pot3 = _verts[_indices[i*3+2]].vertices;
        
        if (is_point_in_triangle(pot1,pot2,pot3,point))
        {
            return true;
        }
    }
    return false;
}

void PolygonSprite::setCCRotation(int value)
{
    _ccRotation = value;
    this->updateVerts();
}
void PolygonSprite::setActionNode(Node * node)
{
    if (_actionNode)
    {
        node->setPosition(_actionNode->getPosition());
        _actionNode->removeFromParentAndCleanup(true);
        _actionNode = node;
    }else
    {
        _actionNode = node;
        _actionNode->setPosition(_spVerts.at(0).x, _spVerts.at(0).y);
    }
    this->addChild(_actionNode);
    invalidateDisplayList();
}

ParticleSystem* PolygonSprite::setParticleNode(const std::string &praticleFile)
{
    auto pNode = ParticleSystemQuad::create(praticleFile);
    setActionNode(pNode);
    return pNode;
}

void PolygonSprite::invalidateDisplayList()
{
    _isInvaildDisplay = true;// 下一帧绘制前将更新UI
    
}

void PolygonSprite::setTimeScale(int timeScale)
{
    _timeScale = timeScale;
    invalidateDisplayList();
}

void PolygonSprite::updateVerts()
{
    //
    const auto &polyInfo = getPolygonInfo();
    
    auto _verts = polyInfo.triangles.verts;
    auto vertCount = polyInfo.triangles.vertCount;
    
    _spVerts.clear();
    
    float min_x = 10000;
    float min_y = 10000;
    float max_x = 0;
    float max_y = 0; // 像素区域边缘
    
    for (int i = 0; i < vertCount; i++)
    {
        const Vec3 &p3 = _verts[i].vertices;
        if (p3.x < min_x)
        {
            min_x = p3.x;
        }
        if (p3.y < min_y)
        {
            min_y = p3.y;
        }
        if (p3.x > max_x)
        {
            max_x = p3.x;
        }
        if (p3.y > max_y)
        {
            max_y = p3.y;
        }
        bool hasNearest = false;
        for (auto &pvert : _spVerts)
        {
            if ( getDistance( pvert,p3 ) < DIS_PRECISION) // 若两点过近则只保留一个值
            {
                hasNearest = true;
                break;
            }
        }
        if (!hasNearest)
        {
            _spVerts.push_back(_verts[i].vertices);
        }
    }
    
    /** middle point in visible pixcels */
    Vec3 mid( ( min_x + max_x )/2, (min_y + max_y)/2,0);
    // 顶点排序
    int len = (int)_spVerts.size();
    if (_ccRotation == 0)
    {
        for(int i = 0;i < len;i++)
        {
            //比较两个相邻的元素
            for(int j = 0;j < len-i-1;j++)
            {
                if(getVect3Angle( _spVerts[j],mid) > getVect3Angle( _spVerts[j+1],mid))
                {
                    Vec3 temp = std::move( _spVerts[j]);
                    _spVerts[j] = std::move( _spVerts[j+1] );
                    _spVerts[j+1] = std::move(temp);
                }
            }
        }
        //
        //        std::sort(_spVerts.begin(), _spVerts.end(),
        //                  [&](const Vec3 & a,const Vec3 & b)->bool
        //                  {
        //                      if ( getVect3Angle(a,mid) < getVect3Angle(b,mid) )
        //                      {
        //                          return false;
        //                      }
        //                      return true;
        //                  }
        //                  );
    }else
    {
        for(int i = 0;i < len;i++)
        {
            for(int j = 0;j < len-i-1;j++)
            {
                if(getVect3Angle( _spVerts[j],mid) < getVect3Angle( _spVerts[j+1],mid))
                {
                    Vec3 temp = std::move( _spVerts[j]);
                    _spVerts[j] = std::move( _spVerts[j+1] );
                    _spVerts[j+1] = std::move(temp);
                }
            }
        }
    }
    
    for (int i = 0;i < len;i++)
    {
        // 计算相邻两顶点的距离
        if (i < (len -1))
        {
            float dis = getDistance(_spVerts[i], _spVerts[i+1]);
            //            float dis = verts[i].distance(verts[i+1]);
            _spVerts[i].z = dis;
        }else
        {
            float dis = getDistance(_spVerts[i], _spVerts[0]);
            _spVerts[i].z = dis;
        }
        
    }
    /**** 顶点调试 **/
//    this->debugDraw(true);
//    int i = 0;
//    for (auto &pos : _spVerts)
//    {
//        char ss[256] = {0};
//        sprintf(ss, "%d (%.0f,%.0f) z %.0f",i,pos.x,pos.y,pos.z);
//        auto l =LabelTTF::create(ss, "Arial", 8);
//        l->setPosition(pos.x, pos.y);
//        this->addChild(l);
//        
//        sprintf(ss, "%d  angle %f time %f",i, getVect3Angle(pos,mid),pos.z );
//        CCLOG(ss);
//        i++;
//    }
//    auto l =LabelTTF::create("M", "Arial", 8);
//    l->setPosition(mid.x, mid.y);
//    this->addChild(l);
}

void PolygonSprite::updateDisplayList()
{
    // update Actions
    if (_actionNode && _spVerts.size() > 0)
    {
        const static int _actTag = -999;
        _actionNode->stopActionByTag(_actTag);
        size_t len = _spVerts.size();

        float time = 0;
        auto array = PointArray::create(len);
        for (auto &p : _spVerts)
        {
            array->addControlPoint({p.x,p.y});
            time += p.z;
        }
        
        auto act = RepeatForever::create( CardinalSplineTo::create(time/_timeScale, array, 0) );
        act->setTag(_actTag);
        this->_actionNode->runAction(act);
        
        auto drawNode = DrawNode::create();
        drawNode->drawCatmullRom(array, 50, Color4F(1.0, 0.0, 0.0, 1.0));
        this->addChild(drawNode);
        
//        Vector<cocos2d::FiniteTimeAction *> arrayOfActions;
//        
//        float dis = getDistance(_actionNode->getPosition3D(), _spVerts[0]);
//        if (dis > DIS_PRECISION/2 )
//        {
//            arrayOfActions.pushBack(MoveTo::create(dis/_timeScale, Vec2(_spVerts[0].x, _spVerts[0].y)));
//        }
//        for (size_t i = 1; i < len; i++)
//        {
//            const Vec3 &pos = _spVerts[i];
//            float tt = _spVerts[i-1].z/_timeScale;
//            arrayOfActions.pushBack( MoveTo::create(tt, Vec2(pos.x, pos.y)) );
//        }
//        dis = _spVerts[len-1].z;
//        arrayOfActions.pushBack( MoveTo::create(dis/_timeScale, Vec2(_spVerts[0].x, _spVerts[0].y)) );
//
//        auto act = RepeatForever::create(Sequence::create(arrayOfActions));
//        act->setTag(_actTag);
//        this->_actionNode->runAction( act );
    }
}

void PolygonSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_isInvaildDisplay)
    {
        updateDisplayList();
        _isInvaildDisplay = false;
    }
    
    Sprite::draw(renderer, transform, flags);
}

