//
//  PhongMat.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "PhongMaterial.hpp"

PhongMaterial::PhongMaterial():ShaderMaterial("rendertotex.vert", "rendertotex.frag"){
    
    KdLoc = glGetUniformLocation(prog, "Material.Kd");
    KsLoc = glGetUniformLocation(prog, "Material.Ks");
    KaLoc = glGetUniformLocation(prog, "Material.Ka");
    ShininessLoc = glGetUniformLocation(prog, "Material.Shininess");
    lightPositionLoc = glGetUniformLocation(prog, "Light.Position");
    lightIntensityLoc = glGetUniformLocation(prog, "Light.Intensity");
    
    float angle = 0.957283;
    lightPosition = glm::vec4(10.0f * cos(angle), 3.0f, 10.0f * sin(angle), 1.0f);
    
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
}

void PhongMaterial::update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
    ShaderMaterial::update(viewMatrix, projectionMatrix);
    
    glUniform3fv(lightIntensityLoc, 1, lightIntensity);
    glUniform4fv(lightPositionLoc, 1, &lightPosition[0]);
    glUniform3fv(KdLoc, 1, Kd);
    glUniform3fv(KsLoc, 1, Ks);
    glUniform3fv(KaLoc, 1, Ka);
    glUniform1f(ShininessLoc, Shininess);
}

