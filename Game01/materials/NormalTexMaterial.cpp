//
//  NormalTexMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/25.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "NormalTexMaterial.hpp"

NormalTexMaterial::NormalTexMaterial(const char* texname, const char* normalTexname):ShaderMaterial("texture.vert", "texture.frag"){
    KdLoc = glGetUniformLocation(prog, "Material.Kd");
    KsLoc = glGetUniformLocation(prog, "Material.Ks");
    KaLoc = glGetUniformLocation(prog, "Material.Ka");
    ShininessLoc = glGetUniformLocation(prog, "Material.Shininess");
    lightPositionLoc = glGetUniformLocation(prog, "Light.Position");
    lightIntensityLoc = glGetUniformLocation(prog, "Light.Intensity");
    
    texloc = glGetUniformLocation(prog, "Tex1");
    normalTexloc = glGetUniformLocation(prog, "Tex2");
    if(!tex.loadTexture(texname)){
        std::cout << "texture load is failed" << std::endl;
    }

    if(!normalTex.loadTexture(normalTexname)){
        std::cout << "texture load is failed" << std::endl;
    }
    
    float angle = 0.957283;
    lightPosition = glm::vec4(10.0f * cos(angle), 3.0f, 10.0f * sin(angle), 1.0f);
    
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
}

void NormalTexMaterial::update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
    ShaderMaterial::update(viewMatrix, projectionMatrix);
    
    glUniform3fv(lightIntensityLoc, 1, lightIntensity);
    glUniform4fv(lightPositionLoc, 1, &lightPosition[0]);
    glUniform3fv(KdLoc, 1, Kd);
    glUniform3fv(KsLoc, 1, Ks);
    glUniform3fv(KaLoc, 1, Ka);
    glUniform1f(ShininessLoc, Shininess);
    
    tex.render(GL_TEXTURE0);
    normalTex.render(GL_TEXTURE1);
    glUniform1i(texloc, 0);
    glUniform1i(normalTexloc, 1);
}

