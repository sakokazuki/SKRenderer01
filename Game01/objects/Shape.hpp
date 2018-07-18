//
//  Shape.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>
#pragma once
#include <memory>
#include "Object.hpp"


class Shape{
    std::shared_ptr<const Object> object;
    
protected:
    const GLsizei vertexcount;
    const GLsizei indexcount;
    
public:
    Shape(GLint size, GLsizei vertexcount, const Object::Vertex *vertex, GLsizei indexcount = 0, const GLuint *index = NULL)
    : object(new Object(size, vertexcount, vertex, indexcount, index)), vertexcount(vertexcount), indexcount(indexcount){
    }
    
    void draw() const{
        object->bind();
        glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, 0);
    }
};

#endif /* Shape_hpp */
