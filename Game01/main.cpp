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

std::string shader_basic_vert =
R"(
#version 410
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
out vec3 Color;
void main()
{
    Color = VertexColor;
    gl_Position = vec4(VertexPosition,1.0);
}
)";


std::string shader_basic_frag =
R"(
#version 410
in vec3 Color;
layout (location=0) out vec4 FragColor;
void main() {
    FragColor = vec4(Color, 1.0);
}
)";


bool CreateCompileShader( std::string code, GLenum shaderType, GLuint& shader )
{
    // Create the shader object
    shader = glCreateShader( shaderType );
    
    if( 0 == shader ) {
        fprintf( stderr, "Error creating shader\n" );
        return false;
    }
    
    // Load the source code into the shader object
    const GLchar* codeArray[] = { code.c_str() };
    std::cout << "----- old -----" << code.c_str() << "----------" << std::endl;
    glShaderSource( shader, 1, codeArray, NULL );
    
    // Compile the shader
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

bool CreateCompileShaderFromFile(){
    return false;
}

GLint test(){
    // Create the shader object
    GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    if( 0 == fragShader )
    {
        fprintf(stderr, "Error creating vertex shader.\n");
        exit(1);
    }
    const GLchar* codeArray[] = {shader_basic_frag.c_str()};
    glShaderSource( fragShader, 1, codeArray, NULL );
    
    // Compile the shader
    glCompileShader( fragShader );
    
    // Check compilation status
    GLint result;
    glGetShaderiv( fragShader, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result )
    {
        
        fprintf( stderr, "Vertex shader compilation failed!\n" );
        
        GLint logLen;
        glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 )
        {
            char * log = (char *)malloc(logLen);
            
            GLsizei written;
            glGetShaderInfoLog(fragShader, logLen, &written, log);
            
            fprintf(stderr, "Shader log: \n%s", log);
            
            free(log);
        }
    }
    return result;
}

GLint bothShader(std::string filename, GLenum shaderType){
    GLchar * shaderCode;
    
    // Load contents of file into shaderCode here…
    ifstream inFile( "/Users/kazukisako/Documents/practice/game/Game01/Game01/shaders/"+filename, ifstream::in );
    if( !inFile ) {
        fprintf(stderr, "Error opening file: shaders/point.vert\n" );
        exit(1);
    }
    
    shaderCode = (char *)malloc(10000);
    int i = 0;
    while( inFile.good() ) {
        int c = inFile.get();
        
        if(c == -1){
            break;
        }
        shaderCode[i++] = c;
    }
    inFile.close();
    shaderCode[i++] = '\0';
    
    // Create the shader object
    GLuint vertShader = glCreateShader( shaderType );
    if( 0 == vertShader )
    {
        fprintf(stderr, "Error creating vertex shader.\n");
        exit(1);
    }
    
    // Load the source code into the shader object
    const GLchar* codeArray[] = {shaderCode};
    glShaderSource( vertShader, 1, codeArray, NULL );
    free(shaderCode); // can be removed from book.
    
    // Compile the shader
    glCompileShader( vertShader );
    
    // Check compilation status
    GLint result;
    glGetShaderiv( vertShader, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result )
    {
        
        fprintf( stderr, "Vertex shader compilation failed!\n" );
        
        GLint logLen;
        glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 )
        {
            char * log = (char *)malloc(logLen);
            
            GLsizei written;
            glGetShaderInfoLog(vertShader, logLen, &written, log);
            
            fprintf(stderr, "Shader log: \n%s", log);
            
            free(log);
        }
    }
    return result;
}



GLint fragshader(){
    GLchar * shaderCode;
    
    // Load contents of file into shaderCode here…
    ifstream fragFile( "/Users/kazukisako/Documents/practice/game/Game01/Game01/shaders/point.frag", ifstream::in );
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
    std::cout << shaderCode << std::endl;
    ////////////////////////////////////////////
    
    // Create the shader object
    GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    if( 0 == fragShader )
    {
        fprintf(stderr, "Error creating fragment shader.\n");
        exit(1);
    }
    
    // Load the source code into the shader object
    
    const GLchar* codeArray[] = {shaderCode};
    glShaderSource( fragShader, 1, codeArray, NULL );
    free(shaderCode); // can be removed from book.
    
    // Compile the shader
    glCompileShader( fragShader );
    
    // Check compilation status
    GLint result;
    glGetShaderiv( fragShader, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result )
    {
        
        fprintf( stderr, "Fragment shader compilation failed!\n" );
        
        GLint logLen;
        glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 )
        {
            char * log = (char *)malloc(logLen);
            
            GLsizei written;
            glGetShaderInfoLog(fragShader, logLen, &written, log);
            
            fprintf(stderr, "Shader log: \n%s", log);
            
            free(log);
        }
    }
    return result;
}

GLint vertshader(){
    GLchar * shaderCode;
    
    // Load contents of file into shaderCode here…
    ifstream inFile( "/Users/kazukisako/Documents/practice/game/Game01/Game01/shaders/point.vert", ifstream::in );
    if( !inFile ) {
        fprintf(stderr, "Error opening file: shaders/point.vert\n" );
        exit(1);
    }
    
    shaderCode = (char *)malloc(10000);
    int i = 0;
    while( inFile.good() ) {
        int c = inFile.get();
        
        if(c == -1){
            break;
        }
        shaderCode[i++] = c;
    }
    inFile.close();
    shaderCode[i++] = '\0';
    
    // Create the shader object
    GLuint vertShader = glCreateShader( GL_VERTEX_SHADER );
    if( 0 == vertShader )
    {
        fprintf(stderr, "Error creating vertex shader.\n");
        exit(1);
    }
    
    // Load the source code into the shader object
    const GLchar* codeArray[] = {shaderCode};
    glShaderSource( vertShader, 1, codeArray, NULL );
    free(shaderCode); // can be removed from book.
    
    // Compile the shader
    glCompileShader( vertShader );
    
    // Check compilation status
    GLint result;
    glGetShaderiv( vertShader, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result )
    {
        
        fprintf( stderr, "Vertex shader compilation failed!\n" );
        
        GLint logLen;
        glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen );
        
        if( logLen > 0 )
        {
            char * log = (char *)malloc(logLen);
            
            GLsizei written;
            glGetShaderInfoLog(vertShader, logLen, &written, log);
            
            fprintf(stderr, "Shader log: \n%s", log);
            
            free(log);
        }
    }
    return result;
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
    
    GLuint vertShader = bothShader("point.vert", GL_VERTEX_SHADER);
//    GLuint fragShader = fragshader();
    // Create a Shader and Compile a Shader
    /////////////////// Create the VBO ////////////////////
    GLuint fragShader = bothShader("point.frag", GL_FRAGMENT_SHADER);
    fragShader = test();
////    vertShader = vertshader();
//    if(!CreateCompileShader(shader_basic_vert, GL_VERTEX_SHADER, vertShader)){
//        return -1;
//    }
//    if(!CreateCompileShader(shader_basic_frag, GL_FRAGMENT_SHADER, fragShader)){
//        return -1;
//    }

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


