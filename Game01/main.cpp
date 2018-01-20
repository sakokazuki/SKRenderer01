//
//  main.cpp
//  Game01
//
//  Created by kazuki sako on 2017/12/06.
//  Copyright © 2017年 kazuki sako. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>

#include <GL/glew.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "system/Window.hpp"
#include "system/ShaderFunc.hpp"
#include "objects/Box.hpp"
#include "objects/Torus.hpp"
#include "objects/Plane.hpp"
#include "objects/ObjMesh.hpp"
#include "system/zTexture.hpp"

#include <gli/gli.hpp>

int main(void)
{
    atexit(glfwTerminate);
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    Window window;
    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }
   
    
    std::unique_ptr<const Box> box(new Box());
    std::unique_ptr<const Torus> torus(new Torus(0.7f * 2, 0.3f * 2, 50, 50));
    std::unique_ptr<const Plane> plane(new Plane(0.7f * 2, 0.3f * 2, 5, 5));
    std::unique_ptr<const ObjMesh> mesh(new ObjMesh("./assets/objs/bs_ears.obj"));
    
    
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(2.0, 3.0f, 5.0f),
                                         glm::vec3(0.0f, 0.0f, 0.0f),
                                         glm::vec3(0.0f, 1.0f, 0.0f));
    
    const GLfloat *const size(window.getSize());
    const GLfloat scale(window.getScale());
    const GLfloat w(size[0] / scale), h(size[1] / scale);
    const GLfloat fovy(scale * 0.01f);
    const GLfloat aspect(w / h);
    glm::mat4 projectionMatrix = glm::perspective(fovy, aspect, 1.0f, 100.0f);
    
    GLuint torusfrag, torusvert;
    if(!ShaderFunc::CreateCompileShader("perfrag.vert", GL_VERTEX_SHADER, torusvert)){
        return -1;
    }
    if(!ShaderFunc::CreateCompileShader("perfrag.frag", GL_FRAGMENT_SHADER, torusfrag)){
        return -1;
    }
    const GLuint torus_prog = ShaderFunc::LinkShader(torusvert, torusfrag);

    const GLint KdLoc(glGetUniformLocation(torus_prog, "Kd"));
    const GLint KsLoc(glGetUniformLocation(torus_prog, "Ks"));
    const GLint KaLoc(glGetUniformLocation(torus_prog, "Ka"));
    const GLint ShininessLoc(glGetUniformLocation(torus_prog, "Shininess"));
    const GLint torusModelViewLoc(glGetUniformLocation(torus_prog, "ModelViewMatrix"));
    const GLint torusNormalLoc(glGetUniformLocation(torus_prog, "NormalMatrix"));
    const GLint torusMVPLoc(glGetUniformLocation(torus_prog, "MVP"));
    const GLint lightPositionLoc(glGetUniformLocation(torus_prog, "LightPosition"));
    const GLint lightIntensityLoc(glGetUniformLocation(torus_prog, "LightIntensity"));
    
    //secne setting
    GLfloat lightIntensity[3] = {0.9f, 0.9f, 0.9f};
    float angle = 0.957283;
    glm::vec4 lightPosition = glm::vec4(10.0f * cos(angle), 3.0f, 10.0f * sin(angle), 1.0f);
    GLfloat Kd[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Ks[3] = {0.1f, 0.1f, 0.1f};
    GLfloat Ka[3] = { 0.1f, 0.1f, 0.1f};
    GLfloat Shininess = 1.0f;
    
    glm::mat4 torus_tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 torus_sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    glm::mat4 torus_rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 box_tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.0f, 1.0f));
    glm::mat4 box_sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    glm::mat4 box_rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 plane_tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -2.0f, 0.0f));
    glm::mat4 plane_sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));
    glm::mat4 plane_rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 mesh_tMatrix = glm::translate(glm::mat4(), glm::vec3(2.0f, 1.0f, 2.0f));
    glm::mat4 mesh_sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    glm::mat4 mesh_rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    GLuint texfrag, texvert;
    if(!ShaderFunc::CreateCompileShader("texture.vert", GL_VERTEX_SHADER, texvert)){
        return -1;
    }
    if(!ShaderFunc::CreateCompileShader("texture.frag", GL_FRAGMENT_SHADER, texfrag)){
        return -1;
    }
    const GLuint tex_prog = ShaderFunc::LinkShader(texvert, texfrag);
    const GLuint mesh_prog = ShaderFunc::LinkShader(texvert, texfrag);

    zTexture myTex;
    if (!myTex.loadTexture("./assets/images/floor.dds")) {
        std::cout << "texture load is failed" << std::endl;
    }
    zTexture myTex2;
    if (!myTex2.loadTexture("./assets/images/floor_normal.dds")) {
        std::cout << "texture load is failed" << std::endl;
    }
    zTexture meshTex;
    if(!meshTex.loadTexture("./assets/images/ogre_diffuse.dds")){
        std::cout << "texture load is failed" << std::endl;
    }
    zTexture meshNormalTex;
    if(!meshNormalTex.loadTexture("./assets/images/ogre_normalmap.dds")){
        std::cout << "texture load is failed" << std::endl;
    }
    

    
    
    const GLint planeTexLoc(glGetUniformLocation(tex_prog, "Tex1"));
//    myTex.render(GL_TEXTURE0);
    const GLint planeNormalTexLoc(glGetUniformLocation(tex_prog, "Tex2"));
//    myTex2.render(GL_TEXTURE1);

    const GLint meshTexLoc(glGetUniformLocation(mesh_prog, "Tex1"));
//    meshTex.render(GL_TEXTURE0);
    const GLuint meshNormalTexLoc(glGetUniformLocation(mesh_prog, "Tex2"));
//    meshNormalTex.render(GL_TEXTURE1);
    
    

    const GLint texKdLoc(glGetUniformLocation(tex_prog, "Material.Kd"));
    const GLint texKsLoc(glGetUniformLocation(tex_prog, "Material.Ks"));
    const GLint texKaLoc(glGetUniformLocation(tex_prog, "Material.Ka"));
    const GLint texShininessLoc(glGetUniformLocation(tex_prog, "Material.Shininess"));
    const GLint texModelViewLoc(glGetUniformLocation(tex_prog, "ModelViewMatrix"));
    const GLint texNormalLoc(glGetUniformLocation(tex_prog, "NormalMatrix"));
    const GLint texMVPLoc(glGetUniformLocation(tex_prog, "MVP"));
    const GLint texlightPositionLoc(glGetUniformLocation(tex_prog, "Light.Position"));
    const GLint texlightIntensityLoc(glGetUniformLocation(tex_prog, "Light.Intensity"));
    
    const GLuint meshModelViewLoc(glGetUniformLocation(mesh_prog, "ModelViewMatrix"));
    const GLint meshNormalLoc(glGetUniformLocation(mesh_prog, "NormalMatrix"));
    const GLint meshMVPLoc(glGetUniformLocation(mesh_prog, "MVP"));
    
    
    glfwSetTime(0.0);
    
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
   
    
    while (window.shouldClose() == GL_FALSE)
    {

        /* Render here */
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
        glUseProgram(torus_prog);
        glUniform3fv(lightIntensityLoc, 1, lightIntensity);
        glUniform4fv(lightPositionLoc, 1, &lightPosition[0]);
        glUniform3fv(KdLoc, 1, Kd);
        glUniform3fv(KsLoc, 1, Ks);
        glUniform3fv(KaLoc, 1, Ka);
        glUniform1f(ShininessLoc, Shininess);
        
        glm::mat4 torus_mv = viewMatrix * torus_tMatrix * torus_rMatrix * torus_sMatrix;
        glUniformMatrix4fv(torusModelViewLoc, 1, GL_FALSE, &torus_mv[0][0]);
        glm::mat3 mv_normal = glm::mat3(glm::vec3(torus_mv[0]), glm::vec3(torus_mv[1]), glm::vec3(torus_mv[2]));
        glUniformMatrix3fv(torusNormalLoc, 1, GL_FALSE, &mv_normal[0][0]);
        glm::mat4 torus_mvp = projectionMatrix *torus_mv;
        glUniformMatrix4fv(torusMVPLoc, 1, GL_FALSE, &torus_mvp[0][0]);
        torus->render();
        
        glm::mat4 r = glm::rotate(glm::mat4(), float(glfwGetTime()), glm::vec3(0.0f, 1.0f, 1.0f));
        glm::mat4 box_mv = viewMatrix * box_tMatrix * r * box_sMatrix;
        glUniformMatrix4fv(torusModelViewLoc, 1, GL_FALSE, &box_mv[0][0]);
        glm::mat3 box_normal = glm::mat3(glm::vec3(box_mv[0]), glm::vec3(box_mv[1]), glm::vec3(box_mv[2]));
        glUniformMatrix3fv(torusNormalLoc, 1, GL_FALSE, &box_normal[0][0]);
        glm::mat4 box_mvp = projectionMatrix * box_mv;
        glUniformMatrix4fv(torusMVPLoc, 1, GL_FALSE, &box_mvp[0][0]);
        box->draw();
        
        glUseProgram(0);

        
        glUseProgram(tex_prog);
        glUniform3fv(texlightIntensityLoc, 1, lightIntensity);
        glUniform4fv(texlightPositionLoc, 1, &lightPosition[0]);
        glUniform3fv(texKdLoc, 1, Kd);
        glUniform3fv(texKsLoc, 1, Ks);
        glUniform3fv(texKaLoc, 1, Ka);
        glUniform1f(texShininessLoc, Shininess);
        
        glm::mat4 plane_mv = viewMatrix * plane_tMatrix * plane_rMatrix * plane_sMatrix;
        glUniformMatrix4fv(texModelViewLoc, 1, GL_FALSE, &plane_mv[0][0]);
        glm::mat3 plane_normal = glm::mat3(glm::vec3(plane_mv[0]), glm::vec3(plane_mv[1]), glm::vec3(plane_mv[2]));
        glUniformMatrix3fv(texNormalLoc, 1, GL_FALSE, &plane_normal[0][0]);
        glm::mat4 plane_mvp = projectionMatrix * plane_mv;
        glUniformMatrix4fv(texMVPLoc, 1, GL_FALSE, &plane_mvp[0][0]);
        
        
        myTex.render(GL_TEXTURE0);
        myTex2.render(GL_TEXTURE1);
        glUniform1i(planeTexLoc, 0);
        glUniform1i(planeNormalTexLoc, 1);
        plane->render();
        
        glm::mat4 mesh_mv = viewMatrix * mesh_tMatrix * mesh_rMatrix * mesh_sMatrix;
        glUniformMatrix4fv(meshModelViewLoc, 1, GL_FALSE, &mesh_mv[0][0]);
        glm::mat3 mesh_normal = glm::mat3(glm::vec3(mesh_mv[0]), glm::vec3(mesh_mv[1]), glm::vec3(mesh_mv[2]));
        glUniformMatrix3fv(meshNormalLoc, 1, GL_FALSE, &mesh_normal[0][0]);
        glm::mat4 mesh_mvp = projectionMatrix * mesh_mv;
        glUniformMatrix4fv(meshMVPLoc, 1, GL_FALSE, &mesh_mvp[0][0]);
        
        meshTex.render(GL_TEXTURE0);
        meshNormalTex.render(GL_TEXTURE1);
        glUniform1i(meshTexLoc, 0);
        glUniform1i(meshNormalTexLoc, 1);
        mesh->render();
        
        
        glUseProgram(0);
        


//
        /* Swap front and back buffers */
        window.swapBuffers();

       
    }
}
