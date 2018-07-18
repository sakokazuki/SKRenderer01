//
//  Box.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/11.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>
#include <memory>
#include <GL/glew.h>
#include "Shape.hpp"

static constexpr Object::Vertex solidCubeVertex[] =
{
    // 左
    { -1.0f, -1.0f, -1.0f},
    { -1.0f, -1.0f, 1.0f},
    { -1.0f, 1.0f, 1.0f},
    { -1.0f, 1.0f, -1.0f},
    // 裏
    { 1.0f, -1.0f, -1.0f},
    { -1.0f, -1.0f, -1.0f},
    { -1.0f, 1.0f, -1.0f},
    { 1.0f, 1.0f, -1.0f},
    // 下
    { -1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f, 1.0f},
    { -1.0f, -1.0f, 1.0f},
    // 右
    { 1.0f, -1.0f, 1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f, 1.0f, -1.0f},
    { 1.0f, 1.0f, 1.0f},
    // 上
    { -1.0f, 1.0f, -1.0f},
    { -1.0f, 1.0f, 1.0f},
    { 1.0f, 1.0f, 1.0f},
    { 1.0f, 1.0f, -1.0f},
    // 前
    { -1.0f, -1.0f, 1.0f},
    { 1.0f, -1.0f, 1.0f},
    { 1.0f, 1.0f, 1.0f},
    { -1.0f, 1.0f, 1.0f}
};

static constexpr GLuint solidCubeIndex[] = {
    0, 1, 2, 0, 2, 3, // 左
    4, 5, 6, 4, 6, 7, // 裏
    8, 9,10, 8,10,11,//下
    12, 13, 14, 12, 14, 15,// 右
    16, 17, 18, 16, 18, 19, // 上
    20,21,22,20,22,23 //前
};
class Box: public Shape{
private:
    

public:
    Box(): Shape(3, 24, solidCubeVertex, 36, solidCubeIndex){
        
    }
};


#endif /* Box_hpp */

