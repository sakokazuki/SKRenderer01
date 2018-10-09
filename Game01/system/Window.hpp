//
//  Window.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp


#include <iostream>
#include <GL/glew.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

    
class Window{
private:
    GLFWwindow *const window;
    
    GLfloat size[2];
	
    GLfloat scale;
    GLfloat location[2];
    
public:
    Window(int width = 640, int height = 480, const char *title = "Hello!");
    const GLfloat *getSize();
    const GLfloat getScale();
    const GLfloat *getLocation();
	const GLint *getViewport();
    static void resize(GLFWwindow *const window, int width, int height);
    virtual ~Window();
    const int shouldClose();
    void swapBuffers();
};
    

#endif /* Window_hpp */
