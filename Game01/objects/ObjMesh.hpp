//
//  ObjMesh.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/20.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ObjMesh_hpp
#define ObjMesh_hpp

#include <stdio.h>
#include <vector>
using:: std::vector;
#include <glm/glm.hpp>
using glm:: vec3;
using glm:: vec2;
using glm:: vec4;
#include <string>
using std::string;

class ObjMesh{
private:
    unsigned int faces;
    unsigned int vaoHandle;
    
    void trimString( string & str );
    void storeVBO( const vector<vec3> & points,
                  const vector<vec3> & normals,
                  const vector<vec2> &texCoords,
                  const vector<vec4> &tangents,
                  const vector<int> &elements );
    void generateAveragedNormals(
                                 const vector<vec3> & points,
                                 vector<vec3> & normals,
                                 const vector<int> & faces );
    void generateTangents(
                          const vector<vec3> & points,
                          const vector<vec3> & normals,
                          const vector<int> & faces,
                          const vector<vec2> & texCoords,
                          vector<vec4> & tangents);
    void center(vector<vec3> &);
    
public:
    ObjMesh( const char * fileName, bool reCenterMesh = false );
    
    void render() const;
    
    void loadOBJ( const char * fileName, bool );
    
};

#endif /* ObjMesh_hpp */
