#include "VOpenGLTexture.h"
#ifndef _VOID_DISABLE_OPENGL_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLTexture
    //----------------------------------------------------------------------------------------------------
    GLenum VOpenGLTexture::TextureFormatForVColorFormat(VColorFormat _format)
    {
        switch (_format)
        {
            case VColorFormat::None:
                break;
            case VColorFormat::RGBA256:
                return GL_RGBA;
            case VColorFormat::RGB256:
                return GL_RGB;
            case VColorFormat::Gray256:
                return GL_ALPHA;
           default:
                return 0;
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLTexture::VOpenGLTexture()
        :
        VSharePointer(nullptr)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLTexture::VOpenGLTexture(const VImage& _image, GLint _minMagFiler, GLint _wrapMode)
        :
        VSharePointer(nullptr)
    {
        SetTexture(_image, _minMagFiler, _wrapMode);
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLTexture::VOpenGLTexture(const VOpenGLTexture& _texture)
        :
        VSharePointer(_texture)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLTexture::~VOpenGLTexture()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLTexture::Texture()
    {
        if (mValue)
        {
            return mValue->texture;
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VOpenGLTexture::SetTexture(const VImage& _image, GLint _minMagFiler, GLint _wrapMode)
    {
        if (_image.Data())
        {
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minMagFiler);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _minMagFiler);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapMode);
            glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatForVColorFormat(_image.ColorFormat()), (GLsizei)_image.Width(), (GLsizei)_image.Height(), 0, TextureFormatForVColorFormat(_image.ColorFormat()), GL_UNSIGNED_BYTE, _image.Data());
            glBindTexture(GL_TEXTURE_2D, 0);
            
            VSharePointer::SetValue(new VOpenGLTextureData(texture));
            return true;
        }
        return false;
    }
}

#endif
