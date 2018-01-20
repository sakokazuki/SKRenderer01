//
//  zTexture.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/16.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "zTexture.hpp"

zTexture::zTexture() {
    
}

bool zTexture::loadTexture(const char* fileName) {
    gli::texture Texture = gli::load(fileName);
    if (Texture.empty())
        return false;
    
    gli::gl GL(gli::gl::PROFILE_GL33);
    gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
    GLenum Target = GL.translate(Texture.target());
    
    GLuint TextureName = 0;
    glGenTextures(1, &TextureName);
    GLenum e = glGetError();
    glBindTexture(Target, TextureName);
    e = glGetError();
    glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
    e = glGetError();
    glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
    e = glGetError();
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
    e = glGetError();
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
    e = glGetError();
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
    e = glGetError();
    glTexParameteri(Target, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);
    e = glGetError();
    glTexParameterf(Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    e = glGetError();
    glTexParameterf(Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    e = glGetError();
    
    glm::tvec3<GLsizei> const Extent(Texture.extent());
    GLsizei const FaceTotal = static_cast<GLsizei>(Texture.layers() * Texture.faces());
    
    switch (Texture.target())
    {
        case gli::TARGET_1D:
            glTexStorage1D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, Extent.x);
            e = glGetError();
            break;
        case gli::TARGET_1D_ARRAY:
        case gli::TARGET_2D:
        case gli::TARGET_CUBE:
            glTexStorage2D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, Extent.x, Texture.target() == gli::TARGET_2D ? Extent.y : FaceTotal);
            e = glGetError();
            break;
        case gli::TARGET_2D_ARRAY:
        case gli::TARGET_3D:
        case gli::TARGET_CUBE_ARRAY:
            glTexStorage3D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, Extent.x, Extent.y, Texture.target() == gli::TARGET_3D ? Extent.z : FaceTotal);
            e = glGetError();
            break;
        default:
            assert(0);
            break;
    }
    
    for (std::size_t Layer = 0; Layer < Texture.layers(); ++Layer){
        for (std::size_t Face = 0; Face < Texture.faces(); ++Face) {
            for (std::size_t Level = 0; Level < Texture.levels(); ++Level)
            {
                GLsizei const LayerGL = static_cast<GLsizei>(Layer);
                glm::tvec3<GLsizei> Extent(Texture.extent(Level));
                Target = gli::is_target_cube(Texture.target()) ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face) : Target;
                
                switch (Texture.target())
                {
                    case gli::TARGET_1D:
                        if (gli::is_compressed(Texture.format())) {
                            glCompressedTexSubImage1D(Target, static_cast<GLint>(Level), 0, Extent.x, Format.Internal, static_cast<GLsizei>(Texture.size(Level)), Texture.data(Layer, Face, Level));
                            e = glGetError();
                        }
                        else {
                            glTexSubImage1D(Target, static_cast<GLint>(Level), 0, Extent.x, Format.External, Format.Type, Texture.data(Layer, Face, Level));
                            e = glGetError();
                        }
                        break;
                    case gli::TARGET_1D_ARRAY:
                    case gli::TARGET_2D:
                    case gli::TARGET_CUBE:
                        if (gli::is_compressed(Texture.format())) {
                            glCompressedTexSubImage2D(Target, static_cast<GLint>(Level), 0, 0, Extent.x, Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y, Format.Internal, static_cast<GLsizei>(Texture.size(Level)), Texture.data(Layer, Face, Level));
                            e = glGetError();
                        }
                        else {
                            glTexSubImage2D(Target, static_cast<GLint>(Level), 0, 0, Extent.x, Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y, Format.External, Format.Type, Texture.data(Layer, Face, Level));
                            e = glGetError();
                        }
                        break;
                    case gli::TARGET_2D_ARRAY:
                    case gli::TARGET_3D:
                    case gli::TARGET_CUBE_ARRAY:
                        if (gli::is_compressed(Texture.format())) {
                            glCompressedTexSubImage3D(Target, static_cast<GLint>(Level), 0, 0, 0, Extent.x, Extent.y, Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL, Format.Internal, static_cast<GLsizei>(Texture.size(Level)), Texture.data(Layer, Face, Level));
                            e = glGetError();
                        }
                        else {
                            glTexSubImage3D(Target, static_cast<GLint>(Level), 0, 0, 0, Extent.x, Extent.y, Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL, Format.External, Format.Type, Texture.data(Layer, Face, Level));
                            e = glGetError();
                        }
                        break;
                    default:
                        assert(0);
                        break;
                }
            }
        }
    }
    e = glGetError();
    glBindTexture(Target, 0);
    e = glGetError();
    texture = TextureName;
    return true;
}

void zTexture::render(GLenum target){
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_2D, texture);
}

GLuint zTexture::getID() {
    return texture;
}





