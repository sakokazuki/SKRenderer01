//
//  ShadowmapMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/30.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "ShadowmapMaterial.hpp"
#include "glm/ext.hpp"

ShadowmapMaterial::ShadowmapMaterial():ShaderMaterial("shadowmap.vert", "shadowmap.frag"){
    KdLoc = glGetUniformLocation(prog, "Material.Kd");
    KsLoc = glGetUniformLocation(prog, "Material.Ks");
    KaLoc = glGetUniformLocation(prog, "Material.Ka");
    ShininessLoc = glGetUniformLocation(prog, "Material.Shininess");
    lightPositionLoc = glGetUniformLocation(prog, "Light.Position");
    lightIntensityLoc = glGetUniformLocation(prog, "Light.Intensity");
    shadowmapLoc = glGetUniformLocation(prog, "ShadowMap");
    shadowMatrixLoc = glGetUniformLocation(prog, "ShadowMatrix");
    
    
    shadowBias = mat4(vec4(0.5f,0.0f,0.0f,0.0f),
                      vec4(0.0f,0.5f,0.0f,0.0f),
                      vec4(0.0f,0.0f,0.5f,0.0f),
                      vec4(0.5f,0.5f,0.5f,1.0f)
                      );
    
    lightFrustum = new Frustum(Projection::PERSPECTIVE);

    float angle = 0.957283;
    lightPosition = glm::vec4(10.0f * cos(angle), 3.0f, 10.0f * sin(angle), 1.0f);
    lightFrustum->orient(lightPosition, vec3(0.0f), vec3(0.0f,1.0f,0.0f));
    lightFrustum->setPerspective( 50.0f, 1.0f, 1.0f, 25.0f);
    lightPV = shadowBias * lightFrustum->getProjectionMatrix() * lightFrustum->getViewMatrix();
    
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    pass1Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "recordDepth");
    pass2Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "shadeWithShadow");
    
    
    
}

void ShadowmapMaterial::update(int passIndex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
    
    if(passIndex == 1){
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass1Index);
        viewMatrix = lightFrustum->getViewMatrix();
        projectionMatrix = lightFrustum->getProjectionMatrix();

    }else if(passIndex == 2){
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass2Index);
//        viewMatrix = lightFrustum->getViewMatrix();
//        projectionMatrix = lightFrustum->getProjectionMatrix();
    }
    ShaderMaterial::update(viewMatrix, projectionMatrix);
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(shadowmapLoc, 0);
    glUniform3fv(lightIntensityLoc, 1, lightIntensity);
    glm::vec4 lightpos = viewMatrix * vec4(lightFrustum->getOrigin(),1.0f);
    glUniform4fv(lightPositionLoc, 1, &lightpos[0]);
    glUniform3fv(KdLoc, 1, Kd);
    glUniform3fv(KsLoc, 1, Ks);
    glUniform3fv(KaLoc, 1, Ka);
    glUniform1f(ShininessLoc, Shininess);
    glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &(lightPV*tMatrix * rMatrix * sMatrix)[0][0]);
}
    



