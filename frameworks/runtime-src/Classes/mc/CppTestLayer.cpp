//
//  CppTestLayer.cpp
//  MyTestCollection
//
//  Created by Howe on 15/12/30.
//
//

#include "CppTestLayer.hpp"
#include "Util.hpp"

void testVirtualFunc()
{
    CCLOG("测试虚函数");
    typedef void(*Fun)(void);
    
    Base b;
    
    Fun pFun = NULL;
    
    cout << "虚函数表地址：" << (uint64_t*)(&b) << endl;
    
    cout << "虚函数表 — 第一个函数地址：" << (uint64_t*)*(uint64_t*)(&b) << endl;
    pFun = (Fun)*( (uint64_t*)*(uint64_t*)(&b) + 1 );
    
    CCLOG("执行private的虚函数");
    pFun();
    
    // 测试const函数
    const Base b1{};
    b1.func2();
    // 父类的析构函数必须是virtual格式
    Base *ib = new InstanceBase();
    delete ib;
}

struct RGB
{
    int R;
    int G;
    int B;
};
void testCPUCaculate1()
{
    auto path = FileUtils::getInstance()->fullPathForFilename("res/twist/test.png");
    auto img = new Image();
    img->initWithImageFile(path);
    
    int width = img->getWidth();
    int height = img->getHeight();
    
    auto _data = img->getData();
    int IMGSIZE = width * height;
    
    std::vector<RGB> in;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            RGB temp;
            temp.R =_data[(i * width + j) * 3];
            temp.G =_data[(i * width + j) * 3 +1 ];
            temp.B =_data[(i * width + j) * 3 +2];
            in.push_back(temp);
        }
    }
    unsigned char testAA[10];
    int s = sizeof(testAA);
    
    unsigned char out[IMGSIZE];
    memset(out, 0, IMGSIZE);

    uint64_t t1 =0;
    // 方式1
    t1 = getTickCount();
    for (int i = 0; i < IMGSIZE; i++)
    {
        double r,g,b,y;
        unsigned char yy;
        r=in[i].R;
        g=in[i].G;
        b=in[i].B;
        y=0.299*r+0.587*g+0.114*b;
        yy=y;
        out[i]=yy;
    }
    t1 = getTickCount() - t1;
    CCLOG("A耗时cpu %llu\n",t1);
    
    t1 = getTickCount();
    // 方式2 不用除法运算
    for (int i = 0; i < IMGSIZE; i++)
    {
        int r,g,b,y;
        r=1224*in[i].R;
        g=2404*in[i].G;
        b=467*in[i].B;
        y=r+g+b;
        y=y>>12; //这里去掉了除法运算
        out[i]=y;
    }
    t1 = getTickCount() - t1;
    CCLOG("B耗时cpu %llu\n",t1);
}

void testCPUCaculate2()
{
    
    auto path = FileUtils::getInstance()->fullPathForFilename("res/twist/test.png");
    auto img = new Image();
    img->initWithImageFile(path);
    
    int width = img->getWidth();
    int height = img->getHeight();
    
    auto _data = img->getData();
    auto IMGSIZE = width * height;
    
    std::vector<RGB> in;
    int index = 0;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            RGB temp;
            temp.R =_data[(i * width + j) * 3];
            temp.G =_data[(i * width + j) * 3 +1 ];
            temp.B =_data[(i * width + j) * 3 +2];
            in.push_back(temp);
            index++;
        }
    }
    unsigned char out[IMGSIZE];
    memset(out, 0, IMGSIZE * sizeof(unsigned char));
    static unsigned int D[256],E[256],F[256]; //查表数组
    for (int i = 0;i < 256;i++)
    {
        D[i] = i *1224;
        D[i] = D[i]>>12;
        E[i] = i *2404;
        E[i] = E[i]>>12;
        F[i] = i *467;
        F[i] = F[i]>>12;
    }
    uint64_t t1 =0;
    // 方式1
    t1 = getTickCount();
    for (int i = 0; i < IMGSIZE; i++)
    {
        int r,g,b,y;
        r=D[in[i].R]; g=E[in[i].G]; b=F[in[i].B]; //查表
        y=r+g+b;
        out[i]=y;
    }
    
    t1 = getTickCount() - t1;
    CCLOG("查表耗时cpu %llu\n",t1);
}

void CppTestLayer::onEnter()
{
    Layer::onEnter();
    testVirtualFunc();
    
    testCPUCaculate1();
    testCPUCaculate2();
    
    std::map<int,string> mapHash;
    mapHash = { {1,"one"},{2,"two"} };
    
// 最简单的lambda
    auto simplestFunc = []{};

    const char str[] = "hi墨白";
    
    const char16_t str16[] = u"hi墨白";
    
    const char32_t str32[] = U"hi墨白";
}