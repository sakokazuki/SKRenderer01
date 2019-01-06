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
#include "../system/Object3D.hpp"

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

void RenderPass::drawPass(){

}

void RenderPass::drawPass(GLuint prevPassTex) {

}

void RenderPass::compileShader(){
    GLuint frag, vert;
	
    if(!CreateCompileShaderTest(shadername_vert, GL_VERTEX_SHADER, vert)){
        throw "vertexshader compile error";
    }

	if(!CreateCompileShaderTest(shadername_frag, GL_FRAGMENT_SHADER, frag)){
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


void RenderPass::setVertexSubRoutine(const char *name) const{
	GLuint index = glGetSubroutineIndex(prog, GL_VERTEX_SHADER, name);
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &index);
}


void RenderPass::setFragmentSubRoutine(const char *name) const {
	GLuint index = glGetSubroutineIndex(prog, GL_FRAGMENT_SHADER, name);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &index);
}
