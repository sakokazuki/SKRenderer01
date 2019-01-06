//
//  ShaderFuncNew.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "ShaderFunc.hpp"
#include <string>
#include <iostream>
bool CreateCompileShaderTest(const std::string filename, GLenum shaderType, GLuint& shader)
{
	std::cout << filename << std::endl;
	//create shader
	shader = glCreateShader(shaderType);
	if (0 == shader)
	{
		fprintf(stderr, "Error creating shader.\n");
		exit(1);
	}	
	std::ifstream shaderFile("./shaders/" + filename, ifstream::ate | ifstream::binary);

	if (!shaderFile) {
		fprintf(stderr, "Error opening shader file\n");
		exit(1);
	}

	int len = shaderFile.tellg();
	GLchar* shaderSource = new GLchar[len + 1];
	shaderFile.clear();
	shaderFile.seekg(0, shaderFile.beg);
	for (int i = 0; i < len; i++) {
		shaderFile.get(shaderSource[i]);
	}
	shaderSource[len] = '\0';
	std::cout << "len: " << len << std::endl;
	std::cout << shaderSource[len-1] << std::endl;
	std::cout << shaderSource << std::endl;

	//compile shader
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	// Check compilation status
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) {
		std::cout << filename << std::endl;
		fprintf(stderr, "shader compilation failed!! \n");

		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = new char[logLen];

			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			delete[] log;
		}

		return false;
	}
	return true;
}

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
    ifstream fragFile( "./shaders/"+filename, ifstream::in | ifstream::binary);
    
    if( !fragFile ) {
        fprintf(stderr, "Error opening shader file\n" );
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
        fprintf( stderr, "shader compilation failed! \n");
        
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
