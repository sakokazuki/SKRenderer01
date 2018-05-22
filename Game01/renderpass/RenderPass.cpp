//
//  RenderPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "RenderPass.hpp"
#include "../meshes/Mesh.hpp"
#include "../lights/Light.hpp"

RenderPass::RenderPass(std::string vert, std::string frag): shadername_vert(vert), shadername_frag(frag){
    compileShader();
    
    modelviewloc = glGetUniformLocation(prog, "ModelViewMatrix");
    mvploc = glGetUniformLocation(prog, "MVP");
    normalloc = glGetUniformLocation(prog, "NormalMatrix");

}

void RenderPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m){
    lights = l;
    camera = c;
    meshes = m;
}

void RenderPass::draw(){

}

void RenderPass::compileShader(){
    GLuint frag, vert;
    if(!CreateCompileShader(shadername_vert, GL_VERTEX_SHADER, vert)){
        throw "vertexshader compile error";
    }
    if(!CreateCompileShader(shadername_frag, GL_FRAGMENT_SHADER, frag)){
        throw "fragmentshader compile error";
    }
    prog = LinkShader(vert, frag);
}
//
void RenderPass::setTextureUniform(const char* name, int index, GLuint tex){
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(GL_TEXTURE_2D, tex);
    GLint loc = glGetUniformLocation(prog, name);
    glUniform1i(loc, index);
}


void RenderPass::setUniform(const char *name, glm::vec4 data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniform4fv(loc, 1, glm::value_ptr(data));
}

void RenderPass::setUniform(const char *name, glm::vec3 data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniform3fv(loc, 1, glm::value_ptr(data));
}

void RenderPass::setUniform(const char *name, glm::mat4 data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
}

void RenderPass::setUniform(const char *name, float data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniform1f(loc, data);
}

void RenderPass::setUniform(const char *name, int data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniform1i(loc, data);
}






