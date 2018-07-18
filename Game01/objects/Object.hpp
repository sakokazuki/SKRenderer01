//
//  Object.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <GL/glew.h>

static constexpr float solidCubeVertexNormal[][3] =
{
    // 左
    { -1.0f, 0.0, 0.0f},
    { -1.0f, 0.0f, 0.0f},
    { -1.0f, 0.0f, 0.0f},
    { -1.0f, 0.0f, 0.0f},
    // 裏
    { 0.0f, 0.0f, -1.0f},
    { 0.0f, 0.0f, -1.0f},
    { 0.0f, 0.0f, -1.0f},
    { 0.0f, 0.0f, -1.0f},
    // 下
    { 0.0f, -1.0f, 0.0f},
    { 0.0f, -1.0f, 0.0f},
    { 0.0f, -1.0f, 0.0f},
    { 0.0f, -1.0f, 0.0f},
    // 右
    { 1.0f, 0.0, 0.0f},
    { 1.0f, 0.0f, 0.0f},
    { 1.0f, 0.0f, 0.0f},
    { 1.0f, 0.0f, 0.0f},
    // 上
    { 0.0f, 1.0f, 0.0f},
    { 0.0f, 1.0f, 0.0f},
    { 0.0f, 1.0f, 0.0f},
    { 0.0f, 1.0f, 0.0f},
    // 前
    { 0.0f, 0.0f, 1.0f},
    { 0.0f, 0.0f, 1.0f},
    { 0.0f, 0.0f, 1.0f},
    { 0.0f, 0.0f, 1.0f},
};


class Object{
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint normalBufferObject;
    
public:
    struct Vertex{
        GLfloat position[3];
    };
    Object(GLint size, GLsizei vertexcount, const Vertex *vertex, GLsizei indexcount = 0, const GLuint *index = NULL){
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
                
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexcount*sizeof(Vertex), vertex, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
        glEnableVertexAttribArray(0);
        
        glGenBuffers(1, &normalBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferObject);
        glBufferData(GL_ARRAY_BUFFER, (3 * vertexcount)*sizeof(float), solidCubeVertexNormal, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
        glEnableVertexAttribArray(1);
        
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexcount * sizeof (GLuint), index, GL_STATIC_DRAW);
        
        glBindVertexArray(0);
    }
    
    void bind() const{
        glBindVertexArray(vao);
    }
    
    virtual ~Object(){
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &normalBufferObject);
    }
private:
    Object(const Object &o);
    Object &operator=(const Object &o);
};
#endif /* Object_hpp */
