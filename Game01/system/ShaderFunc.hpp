//
//  ShaderFuncNew.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ShaderFuncNew_hpp
#define ShaderFuncNew_hpp

#include <cstdlib>
#include <iostream>
#include <fstream>
using std::ifstream;

#include <stdio.h>
#include <GL/glew.h>


bool CreateCompileShader( std::string filename, GLenum shaderType, GLuint& shader );
GLuint LinkShader( GLint shader1, GLint shader2 );

#endif /* ShaderFuncNew_hpp */

