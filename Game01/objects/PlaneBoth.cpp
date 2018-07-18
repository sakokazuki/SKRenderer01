//
//  PlaneBoth.cpp
//  Game01
//
//  Created by kazuki sako on 2018/06/17.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "PlaneBoth.hpp"
#include <GL/glew.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>


PlaneBoth::PlaneBoth(float xsize, float zsize, int xdivs, int zdivs)
{
    
    faces = xdivs * zdivs;
    float * v = new float[3 * (xdivs + 1) * (zdivs + 1) * 2];
    float * tex = new float[2 * (xdivs + 1) * (zdivs + 1) * 2];
    float * n = new float[3 * (xdivs + 1) * (zdivs + 1) * 2];
    unsigned int * el = new unsigned int[6 * xdivs * zdivs * 2];
    float *tang = new float[4 * (xdivs + 1) * (zdivs + 1) * 2];
    
    float x2 = xsize / 2.0f;
    float z2 = zsize / 2.0f;
    float iFactor = (float)zsize / zdivs;
    float jFactor = (float)xsize / xdivs;
    float texi = 1.0f / zdivs;
    float texj = 1.0f / xdivs;
    float x, z;
    int vidx = 0, tidx = 0;
    for( int k = 0; k < 2; k++){
        float nDir = k == 0 ? 1.0f : -1.0f;
        float yPos = k == 0 ? 0.0f : 0.00001f;
        for( int i = 0; i <= zdivs; i++ ) {
            z = iFactor * i - z2;
            for( int j = 0; j <= xdivs; j++ ) {
                x = jFactor * j - x2;
                v[vidx] = x;
                v[vidx+1] = yPos;
                v[vidx+2] = z;
                n[vidx] = 0.0f;
                n[vidx+1] = nDir;
                n[vidx+2] = 0.0f;
                vidx += 3;
                tex[tidx] = i * texi;
                tex[tidx+1] = j * texj;
                tidx += 2;
                
                
            }
        }
    }
    
    
    unsigned int rowStart, nextRowStart;
    int idx = 0;
    //front
    for( int i = 0; i < zdivs; i++ ) {
        rowStart = i * (xdivs+1);
        nextRowStart = (i+1) * (xdivs+1);
        for( int j = 0; j < xdivs; j++ ) {
            el[idx] = rowStart + j;
            el[idx+1] = nextRowStart + j;
            el[idx+2] = nextRowStart + j + 1;
            el[idx+3] = rowStart + j;
            el[idx+4] = nextRowStart + j + 1;
            el[idx+5] = rowStart + j + 1;
//            std::cout << "--" << std::endl;
//            std::cout << el[idx] << ", " << el[idx+1] << ", " << el[idx+2] << ", " << std::endl;
//            std::cout << el[idx+3] << ", " << el[idx+4] << ", " << el[idx+5] << ", " << std::endl;
            idx += 6;
        }
    }
    //back
    for( int i = 0; i < zdivs; i++ ) {
        rowStart = i * (xdivs+1);
        nextRowStart = (i+1) * (xdivs+1);
        for( int j = 0; j < xdivs; j++ ) {
            el[idx] = rowStart + j;
            el[idx+1] = nextRowStart + j + 1;
            el[idx+2] = nextRowStart + j;
            el[idx+3] = rowStart + j;
            el[idx+4] = rowStart + j + 1;
            el[idx+5] = nextRowStart + j + 1;
//            std::cout << "--" << std::endl;
//            std::cout << el[idx] << ", " << el[idx+1] << ", " << el[idx+2] << ", " << std::endl;
//            std::cout << el[idx+3] << ", " << el[idx+4] << ", " << el[idx+5] << ", " << std::endl;
            idx += 6;
        }
    }
    

    
    for(int i=0; i <6 * xdivs * zdivs * 2 ; i+=3){
        int p0 = el[i];
        int p1 = el[i+1];
        int p2 = el[i+2];
        float v0[5] = {v[p0*3], v[p0*3+1], v[p0*3+2], tex[p0*2], tex[p0*2+1]};
        float v1[5] = {v[p1*3], v[p1*3+1], v[p1*3+2], tex[p1*2], tex[p1*2+1]};
        float v2[5] = {v[p2*3], v[p2*3+1], v[p2*3+2], tex[p2*2], tex[p2*2+1]};
        
        glm::vec3 _cp0[3] = {
            glm::vec3(v0[0], v0[3], v0[4]),
            glm::vec3(v0[1], v0[3], v0[4]),
            glm::vec3(v0[2], v0[3], v0[4])
        };
        glm::vec3 _cp1[3] = {
            glm::vec3(v1[0], v1[3], v1[4]),
            glm::vec3(v1[1], v1[3], v1[4]),
            glm::vec3(v1[2], v1[3], v1[4])
        };
        glm::vec3 _cp2[3] = {
            glm::vec3(v2[0], v2[3], v2[4]),
            glm::vec3(v2[1], v2[3], v2[4]),
            glm::vec3(v2[2], v2[3], v2[4])
        };
        
        float _u[3], _v[3];
        for(int j=0; j<3; j++){
            glm::vec3 vert1 = _cp1[j] - _cp0[j];
            glm::vec3 vert2 = _cp2[j] - _cp0[j];
            glm::vec3 abc = glm::cross(vert1, vert2);
            _u[j] = -abc.y / abc.x;
            _v[j] = -abc.z / abc.x;
        }
        float _l = glm::sqrt(_u[0]*_u[0]+_u[1]*_u[1]+_u[2]*_u[2]);
        tang[p0*4] = _u[0]/_l;
        tang[p0*4+1] = _u[1]/_l;
        tang[p0*4+2] = _u[2]/_l;
        tang[p0*4+3] = 0.0f;
        tang[p1*4] = _u[0]/_l;
        tang[p1*4+1] = _u[1]/_l;
        tang[p1*4+2] = _u[2]/_l;
        tang[p1*4+3] = 0.0f;
        tang[p2*4] = _u[0]/_l;
        tang[p2*4+1] = _u[1]/_l;
        tang[p2*4+2] = _u[2]/_l;
        tang[p2*4+3] = 0.0f;
    }
    
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray(vaoHandle);
    
    unsigned int handle[5];
    glGenBuffers(5, handle);
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * (xdivs+1) * (zdivs+1) * sizeof(float) * 2, v, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * (xdivs+1) * (zdivs+1) * sizeof(float) * 2, n, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(1);  // Vertex normal
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
    glBufferData(GL_ARRAY_BUFFER, 2 * (xdivs+1) * (zdivs+1) * sizeof(float) * 2, tex, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(2);  // Texture coords
    
    glBindBuffer(GL_ARRAY_BUFFER, handle[3]);
    glBufferData(GL_ARRAY_BUFFER, 4 * (xdivs+1) * (zdivs+1) * sizeof(float) * 2, tang, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)3, 4, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(3); // Tangent vector;
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[4]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * xdivs * zdivs * sizeof(unsigned int) * 2, el, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    delete [] v;
    delete [] tex;
    delete [] tang;
    delete [] n;
    delete [] el;
    
}

void PlaneBoth::render() const {
    glBindVertexArray(vaoHandle);
    glDrawElements(GL_TRIANGLES, 6 * faces * 2, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
