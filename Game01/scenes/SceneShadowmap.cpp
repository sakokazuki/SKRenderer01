//
//  SceneShadowmap.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/29.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "SceneShadowmap.hpp"



SceneShadowmap::SceneShadowmap(int ww, int wh):Scene(ww, wh){
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    quad = new Quad();
    deferredMat = new DeferredMaterial();
    shadowmapMat = new ShadowmapMaterial();
    torus = new Torus(0.7f * 2, 0.3f * 2, 50, 50);
    
    plane = new Plane(1, 1, 1, 1);
    
    viewMatrix = glm::lookAt(glm::vec3(2.0, 3.0f, 5.0f),
                             glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));
    
    const GLfloat w(windowW), h(windowH);
    const GLfloat fovy(100.0 * 0.01f);
    const GLfloat aspect(w / h);
    projectionMatrix = glm::perspective(fovy, aspect, 1.0f, 100.0f);
    
    
    GLfloat border[] = {1.0f, 0.0f, 0.0f, 0.0f};
    glGenTextures(1, &depthTex);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, windowW*2, windowH*2, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    
    glGenFramebuffers(1, &shadowFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
    
    

    GLenum drawBuffers[] = {GL_NONE};
    glDrawBuffers(1, drawBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
}

void SceneShadowmap::render() const{
    glUseProgram(shadowmapMat->prog);
    
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    
//    shadowmapMat->update(1, viewMatrix, projectionMatrix);
    
    drawScene(1);
    
    glFlush();
    glFinish();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    
    drawScene(2);

    //
    glUseProgram(0);
    
}

void SceneShadowmap::drawScene(int pass) const{
    shadowmapMat->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0));
    shadowmapMat->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
    shadowmapMat->update(pass, viewMatrix, projectionMatrix);
    torus->render();
    shadowmapMat->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, -2, 0));
    shadowmapMat->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0));
    shadowmapMat->update(pass, viewMatrix, projectionMatrix);
    plane->render();
    
}









