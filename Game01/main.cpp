//
//  main.cpp
//  Game01
//
//  Created by kazuki sako on 2017/12/06.
//  Copyright © 2017年 kazuki sako. All rights reserved.
//

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
using std::ifstream;
#include <vector>
#include <algorithm>
#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

const int G_WIDTH = 640;
const int G_HEIGHT = 480;

bool CreateCompileShader( std::string filename, GLenum shaderType, GLuint& shader )
{
    //create shader
    shader = glCreateShader(shaderType);
    if( 0 == shader )
    {
        fprintf(stderr, "Error creating shader.\n");
        exit(1);
    }
    
    //read shader file
    GLchar * shaderCode;
    ifstream fragFile( "./shaders/"+filename, ifstream::in );
    
    if( !fragFile ) {
        fprintf(stderr, "Error opening file: shader/basic.frag\n" );
        exit(1);
    }
    shaderCode = (char *)malloc(10000);
    int i = 0;
    while( fragFile.good() ) {
        int c = fragFile.get();
        if(c == -1){
            break;
        }
        shaderCode[i++] = c;
    }
    fragFile.close();
    shaderCode[i++] = '\0';
    const GLchar* codeArray[] = {shaderCode};
    free(shaderCode);

    //compile shader
    glShaderSource( shader, 1, codeArray, NULL );
    glCompileShader( shader );
    
    // Check compilation status
    GLint result;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result ) {
        fprintf( stderr, "shader compilation failed!\n" );
        
        GLint logLen;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 ) {
            char * log = new char[logLen];
            
            GLsizei written;
            glGetShaderInfoLog( shader, logLen, &written, log );
            
            fprintf( stderr, "Shader log: \n%s", log );
            
            delete [] log;
        }
        
        return false;
    }
    return true;
}

bool LinkShader( GLint shader1, GLint shader2 )
{
    // Create the program object
    GLuint programHandle = glCreateProgram();
    if(0 == programHandle) {
        fprintf(stderr, "Error creating program object.\n");
        return false;
    }
    
    // Attach the shaders to the program object
    glAttachShader( programHandle, shader1 );
    glAttachShader( programHandle, shader2 );
    
    // Link the program
    glLinkProgram( programHandle );
    
    // Check for successful linking
    GLint status;
    glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
    
    if (GL_FALSE == status) {
        fprintf( stderr, "Failed to link shader program!\n" );
        GLint logLen;
        glGetProgramiv( programHandle, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 ) {
            char * log = new char[logLen];
            GLsizei written;
            glGetProgramInfoLog( programHandle, logLen, &written, log );
            fprintf( stderr, "Program log: \n%s", log );
            
            delete [] log;
        }
        return false;
        
    } else {
        glUseProgram( programHandle );
    }
    return true;
}


int main(void)
{
    GLFWwindow* window;
    
    atexit(glfwTerminate);

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(G_WIDTH, G_HEIGHT, "GAME WINDOW", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        // GLEW の初期化に失敗した
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }
    
    glfwSwapInterval(1);
    
    GLuint fragShader, vertShader;
    if(!CreateCompileShader("point.vert", GL_VERTEX_SHADER, vertShader)){
        return -1;
    }
    if(!CreateCompileShader("point.frag", GL_FRAGMENT_SHADER, fragShader)){
        return -1;
    }
    if(!LinkShader(vertShader, fragShader)){
        return -1;
    }

    /////////////////// Create the VBO ////////////////////
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f,  0.8f, 0.0f };

    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f };

    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), colorData, GL_STATIC_DRAW);

    GLuint vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray( vaoHandle );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


}


