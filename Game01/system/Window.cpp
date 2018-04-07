//
//  Window.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Window.hpp"

Window::Window(int width, int height, const char *title): window(glfwCreateWindow(width, height, title, NULL, NULL)), scale(100.0f){
    if(window==NULL){
        std::cerr << "Can't create GLFW window." << std::endl;
        exit(1);
    }
    
    glfwMakeContextCurrent(window);
    
    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Can't initialize GLEW" << std::endl;
        exit(1);
    }
    // 垂直同期のタイミングを待つ
    glfwSwapInterval(1);
    
    glfwSetWindowUserPointer(window, this);
    // ウィンドウのサイズ変更時に呼び出す処理の登録
    glfwSetWindowSizeCallback(window, resize);
    resize(window, width, height);
    
    location[0] = location[1] = 0.0f;
}

void Window::resize(GLFWwindow *const window, int width, int height)
{
    glViewport(0, 0, width*2, height*2);
    // このインスタンスの this ポインタを得る
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
    
    if (instance != NULL)
    {
        instance->size[0] = static_cast<GLfloat>(width);
        instance->size[1] = static_cast<GLfloat>(height);
    }
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
//    glfwWaitEvents();
    glfwPollEvents();
    
    //        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)
    //        {
    //            double x, y;
    //            glfwGetCursorPos(window, &x, &y);
    //
    //            location[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
    //            location[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];
    //        }
}


const GLfloat *Window::getSize(){
    return size;
}
const GLfloat Window::getScale(){
    return scale;
}
const GLfloat *Window::getLocation(){
    return location;
}

const int Window::shouldClose(){
    return glfwWindowShouldClose(window);
}


Window::~Window(){
    glfwDestroyWindow(window);
}


