//
//  RenderPass.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef RenderPass_hpp
#define RenderPass_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "../system/ShaderFunc.hpp"
//#include "../lights/Light.hpp"
#include "../camera/Camera.hpp"
//#include "../meshes/Mesh.hpp"

class Object3D;
class Light;
class Mesh;

class RenderPass{
private:
    void compileShader();
protected:
    const std::string shadername_vert;
    const std::string shadername_frag;
    
    
public:
    GLuint prog;
    GLint mvploc, modelviewloc, normalloc;
    glm::mat4 viewMatrix, projectionMatrix;
    RenderPass(std::string vert, std::string frag);
    virtual void drawPass();
    virtual void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m);
//    Light* light;
    Camera* camera;
    std::vector<Mesh*> meshes;
    std::vector<Light*> lights;
    
    void setUniform(const char* name, glm::vec3 data) const;
    void setUniform(const char* name, glm::vec4 data) const;
    void setUniform(const char* name, glm::mat4 data) const;
    void setUniform(const char* name, float data) const;
    void setUniform(const char* name, int data) const;

    
    //tmp
    void setTextureUniform(const char* name, int index, GLuint tex);
    
    
};

#endif /* RenderPass_hpp */
