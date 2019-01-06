//
//  main.cpp
//  Game01
//
//  Created by kazuki sako on 2017/12/06.
//  Copyright © 2017年 kazuki sako. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <format.cc>
#include <fmt/format.h>


#include <GL/glew.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "system/Window.hpp"
#include "./system/defines.h"

#include "./system/ShaderFunc.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include "apps/TestApp.hpp"
#include "apps/TestApp2.h"
#include "apps/AppBase.hpp"
#include "system/Object3DBehaviourList.h"
#include <sstream>


int main()
{
	atexit(glfwTerminate);

	DefineBehaviours::define();



	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	Window window(WINDOW_W, WINDOW_H, "main.cpp");
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
	

	
	//app::AppBase* app = new app::TestApp2(&window);

    app::AppBase* app = new app::TestApp(&window);
	
    while (window.shouldClose() == GL_FALSE)
    {
		glClear(GL_COLOR_BUFFER_BIT);

		app->loop();
        /* Swap front and back buffers */
        window.swapBuffers();
    }
    return 0;
}
