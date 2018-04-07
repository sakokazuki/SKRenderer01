//
//  DeferrdMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/25.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "DeferredMaterial.hpp"


DeferredMaterial::DeferredMaterial():ShaderMaterial("deferred.vert", "deferred.frag"){
    KdLoc = glGetUniformLocation(prog, "Material.Kd");
    ShininessLoc = glGetUniformLocation(prog, "Material.Shininess");
    lightPositionLoc = glGetUniformLocation(prog, "Light.Position");
    lightIntensityLoc = glGetUniformLocation(prog, "Light.Intensity");
    
    postexloc = glGetUniformLocation(prog, "PositionTex");
    normtexloc= glGetUniformLocation(prog, "NormalTex");
    coltexloc = glGetUniformLocation(prog, "ColorTex");

    
    float angle = 0.957283;
    lightPosition = glm::vec4(10.0f * cos(angle), 3.0f, 10.0f * sin(angle), 1.0f);
    
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    pass1Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "pass1");
    pass2Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "pass2");
    
}

void DeferredMaterial::update(int passindex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
    if(passindex == 1){
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass1Index);
        ShaderMaterial::update(viewMatrix, projectionMatrix);
        
        glUniform3fv(lightIntensityLoc, 1, lightIntensity);
        glUniform4fv(lightPositionLoc, 1, &lightPosition[0]);
        glUniform3fv(KdLoc, 1, Kd);
        glUniform1f(ShininessLoc, Shininess);
        
    }else if(passindex == 2){
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
        
        
    }
    
}

