//
//  Quad.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Quad.hpp"

#include <GL/glew.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>


Quad::Quad()
{
    GLfloat verts[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f
    };
    GLfloat tc[] = {
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    
    unsigned int handle[2];
    glGenBuffers(2, handle);
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);
    
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray(vaoHandle);
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glVertexAttribPointer( (GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(2);  // Texture coordinates
    
    glBindVertexArray(0);
    
    
}

void Quad::render() const {
    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
