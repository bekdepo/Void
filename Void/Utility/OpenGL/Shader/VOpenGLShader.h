#pragma once
#ifndef _VOID_DISABLE_OPENGL_
#ifndef _V_OPENGLSHADER_H_
#define _V_OPENGLSHADER_H_
#include "../../../Memory/SmartPtr/VSmartPtr.h"
#define GLFW_INCLUDE_GLCOREARB
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLShaderData
    //----------------------------------------------------------------------------------------------------
    class VOpenGLShaderData
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VOpenGLShaderData()
            :
            shader(0)
        {
        }
        
        inline VOpenGLShaderData(const GLuint& _shader)
            :
            shader(_shader)
        {
        }
        
        virtual ~VOpenGLShaderData()
        {
            if (shader)
            {
                glDeleteShader(shader);
                shader = 0;
            }
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        GLuint shader;
    };
    
    // VOpenGLShader
    //----------------------------------------------------------------------------------------------------
    class VOpenGLShader : protected VSmartPtr<VOpenGLShaderData>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VOpenGLShader(const std::string& _shader, GLenum _shaderType, bool _isFromFile=false);
        VOpenGLShader(const VOpenGLShader& _shader);
        virtual ~VOpenGLShader();
        
        //----------------------------------------------------------------------------------------------------
        GLuint Shader();
    };
}

#endif
#endif
