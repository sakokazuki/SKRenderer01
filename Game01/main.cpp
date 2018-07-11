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
#include <fmt/format.cc>
#include <fmt/format.h>


#include <GL/glew.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "system/Window.hpp"

#include <gli/gli.hpp>


#include "renderers/Renderer01.hpp"

#include <glm/glm.hpp>

#include "apps/TestApp.hpp"
#include "apps/AppBase.hpp"
#include "system/Object3DBehaviourList.h"


int main(void)
{
    atexit(glfwTerminate);
    
    DefineBehaviours::define();
    

    
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

    glfwSetTime(0.0);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    app::AppBase* app = new app::TestApp(&window);

    while (window.shouldClose() == GL_FALSE)
    {
        app->loop();
        /* Swap front and back buffers */
        window.swapBuffers();
    }
    return 0;
}
