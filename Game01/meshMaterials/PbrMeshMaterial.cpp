//
//  PbrMeshMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/04/30.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "PbrMeshMaterial.hpp"

PbrMeshMaterial::PbrMeshMaterial(){
    GLubyte whiteTexColor[] = { 255, 255, 255, 255 };
    glGenTextures(1, &mainTex);
    glBindTexture(GL_TEXTURE_2D,mainTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,whiteTexColor);
    
}

void PbrMeshMaterial::setUniforms(RenderPass* renderPass){
    renderPass-> setUniform("Metallic", metallic);
    renderPass->setUniform("Roughness", roughness);
    renderPass-> setTextureUniform("Texture", 1, mainTex);
}

PbrMeshMaterial::~PbrMeshMaterial(){
    
}
