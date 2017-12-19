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

GLuint LinkShader( GLint shader1, GLint shader2 )
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
        glDeleteProgram(programHandle);
        return 0;
        
    }
    return programHandle;
}

struct Vertex{
    GLfloat position[2];
};



class Object{
    GLuint vao;
    GLuint vbo;
    
public:
    struct Vertex{
        GLfloat position[2];
    };
    
    Object(GLint size, GLsizei vertexcount, const Vertex *vertex){
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexcount*sizeof(Vertex), vertex, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
    }
    
    void bind() const{
        glBindVertexArray(vao);
    }
    
    virtual ~Object(){
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &vbo);
        
    }
private:
    Object(const Object &o);
    Object &operator=(const Object &o);
};

class Shape{
    std::shared_ptr<const Object> object;
    
protected:
    const GLsizei vertexcount;
public:
    Shape(GLint size, GLsizei vertexcount, const Object::Vertex *vertex):object(new Object(size, vertexcount, vertex)), vertexcount(vertexcount){
        
        
    }
    
    void draw() const{
        object->bind();
        execute();
    }
    
    virtual void execute() const{
        glDrawArrays(GL_LINE_LOOP, 0, vertexcount);
    }
};

class Window{
    GLFWwindow *const window;
    
    GLfloat size[2];
    GLfloat scale;
    GLfloat location[2];
    
public:
    Window(int width = 640, int height = 480, const char *title = "Hello!"): window(glfwCreateWindow(width, height, title, NULL, NULL)), scale(100.0f){
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
    
    const GLfloat *getSize() const { return size; }
    GLfloat getScale() const { return scale; }
    const GLfloat *getLocation() const { return location; }
    
    static void resize(GLFWwindow *const window, int width, int height)
    {
        glViewport(0, 0, width, height);
        
        // このインスタンスの this ポインタを得る
        Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
        
        if (instance != NULL)
        {
            instance->size[0] = static_cast<GLfloat>(width);
            instance->size[1] = static_cast<GLfloat>(height);
        }
    }
    
    virtual ~Window()
    {
        glfwDestroyWindow(window);
    }

    int shouldClose() const
    {
        return glfwWindowShouldClose(window);
    }
    
    void swapBuffers()
    {
        glfwSwapBuffers(window);
        glfwWaitEvents();
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)
        {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            
            location[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
            location[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];
        }
    }
};

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
    
    GLuint fragShader, vertShader;
    if(!CreateCompileShader("init.vert", GL_VERTEX_SHADER, vertShader)){
        return -1;
    }
    if(!CreateCompileShader("init.frag", GL_FRAGMENT_SHADER, fragShader)){
        return -1;
    }
    const GLuint program = LinkShader(vertShader, fragShader);
    const GLint sizeLoc(glGetUniformLocation(program, "size"));
    const GLint scaleLoc(glGetUniformLocation(program, "scale"));
    const GLint locationLoc(glGetUniformLocation(program, "location"));
    
    const Object::Vertex rectangleVertex[] =
    {
        { -0.5f, -0.5f },
        { 0.5f, -0.5f },
        { 0.5f, 0.5f },
        { -0.5f, 0.5f }
    };

    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

    while (window.shouldClose() == GL_FALSE)
    {
        /* Render here */
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        

        glUseProgram(program);
        glUniform2fv(sizeLoc, 1, window.getSize());
        glUniform1f(scaleLoc, window.getScale());
        glUniform2fv(locationLoc, 1, window.getLocation());
        shape->draw();
        glUseProgram(0);

        
        
        
        /* Swap front and back buffers */
        window.swapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }
}


/////////////////// Create the VBO ////////////////////
//float positionData[] = {
//    -0.8f, -0.8f, 0.0f,
//    0.8f, -0.8f, 0.0f,
//    0.0f,  0.8f, 0.0f };
//
//float colorData[] = {
//    1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 0.0f,
//    0.0f, 0.0f, 1.0f };
//
//
//GLuint vboHandles[2];
//glGenBuffers(2, vboHandles);
//GLuint positionBufferHandle = vboHandles[0];
//GLuint colorBufferHandle = vboHandles[1];
//
//glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
//glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), positionData, GL_STATIC_DRAW);
//
//glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
//glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), colorData, GL_STATIC_DRAW);
//
//GLuint vaoHandle;
//glGenVertexArrays(1, &vaoHandle);
//glBindVertexArray(vaoHandle);
//
//glEnableVertexAttribArray(0);
//glEnableVertexAttribArray(1);
//
//glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
//
//glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
//glBindVertexArray(0);

