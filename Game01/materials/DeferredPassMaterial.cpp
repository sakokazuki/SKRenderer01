//
//  DeferredPassMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/04.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "DeferredPassMaterial.hpp"
#include <glm/gtc/type_ptr.hpp>

DeferredPassMaterial::DeferredPassMaterial(): shadername_vert("deferredpass.vert"), shadername_frag("deferredpass.frag"){
    complieShader();
    KdLoc = glGetUniformLocation(prog, "Material.Kd");
    ShininessLoc = glGetUniformLocation(prog, "Material.Shininess");
    lightPositionLoc = glGetUniformLocation(prog, "Light.Position");
    lightIntensityLoc = glGetUniformLocation(prog, "Light.Intensity");
    
    postexloc = glGetUniformLocation(prog, "PositionTex");
    normtexloc= glGetUniformLocation(prog, "NormalTex");
    coltexloc = glGetUniformLocation(prog, "ColorTex");
    shadowtexloc = glGetUniformLocation(prog, "ShadowmapTex");
    
    
    modelviewloc = glGetUniformLocation(prog, "ModelViewMatrix");
    mvploc = glGetUniformLocation(prog, "MVP");
    normalloc = glGetUniformLocation(prog, "NormalMatrix");
    
    float angle = 0.957283;
    lightPosition = glm::vec4(10.0f * cos(angle), 3.0f, 10.0f * sin(angle), 1.0f);
    
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    pass1Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "pass1");
    pass2Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "pass2");

}



void DeferredPassMaterial::setmvp() const{
    glm::mat4 mv = viewMatrix * tMatrix * rMatrix * sMatrix;
    glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
    glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
    glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
    glm::mat4 mvp = projectionMatrix * mv;
    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
}

void DeferredPassMaterial::pass1(){
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass1Index);
    setmvp();

    setUniform("Material.Kd", Kd);

}

void DeferredPassMaterial::pass2(){
    setUniform("Light.Intensity", lihgtIntensity);
    setUniform("Light.Position", lightPosition);
    setUniform("Material.Shininess", Shininess);
    
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass2Index);
    glm::mat4 mv = glm::mat4(1.0);
    glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
    glm::mat3 normal = glm::mat3(1.0);
    glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
    glm::mat4 mvp = glm::mat4(1.0);
    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
    
    glUniform1i(postexloc, 0);
    glUniform1i(normtexloc, 1);
    glUniform1i(coltexloc, 2);
    glUniform1i(shadowtexloc, 3);

}


void DeferredPassMaterial::setUniform(const char *name, glm::vec4 data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniform4fv(loc, 1, glm::value_ptr(data));
}

void DeferredPassMaterial::setUniform(const char *name, glm::vec3 data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniform3fv(loc, 1, glm::value_ptr(data));
}

void DeferredPassMaterial::setUniform(const char *name, glm::mat4 data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
}

void DeferredPassMaterial::setUniform(const char *name, float data) const{
    GLint loc = glGetUniformLocation(prog, name);
    glUniform1f(loc, data);
}


void DeferredPassMaterial::complieShader(){
    GLuint frag, vert;
    if(!CreateCompileShader(shadername_vert, GL_VERTEX_SHADER, vert)){
        throw "vertexshader compile error";
    }
    if(!CreateCompileShader(shadername_frag, GL_FRAGMENT_SHADER, frag)){
        throw "fragmentshader compile error";
    }
    prog = LinkShader(vert, frag);
}

