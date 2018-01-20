//
//  zTexture.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/16.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef zTexture_hpp
#define zTexture_hpp

#include <stdio.h>

#include <GL/glew.h>
#include <gli/gli.hpp>

class zTexture {
private:
    GLuint texture;
    
public:
    zTexture();
    bool loadTexture(const char* fileName);
    void render(GLenum target);
    GLuint getID(void);
};


#endif /* zTexture_hpp */
