#pragma once
#include <glad/glad.h>

#include "fileman.hpp"


struct Shader
{
    Shader(const int& _type, const char* filepath)
    {
        type = _type;
        source = load_text(filepath);
        id = glCreateShader(_type);

        compile();
    }

    ~Shader()
    {
        glDeleteShader(id);
        delete source;
    }

    void compile()
    {
        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);

        int success;
        char infoLog[512];

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            printf("%i shader compilation failed: %s\n", type, infoLog);
        }

    }

    unsigned int id;
    int type;
    const char* source;
};

struct ShaderProgram
{
    ShaderProgram(Shader* _vertex, Shader* _fragment)
     : vertex(_vertex), fragment(_fragment)
    {
        id = glCreateProgram();
        
        link();
    }

    void link()
    {
        glAttachShader(id, vertex->id);
        glAttachShader(id, fragment->id);
        glLinkProgram(id);

        int success;
        char infoLog[512];

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            printf("Shader linking error: %s \n", infoLog);
        }
    }

    void use()
    {
        glUseProgram(id);

        if (sizeof(*vertex))
            delete vertex;

        if (sizeof(*fragment))
            delete fragment;
    }

    Shader* vertex;
    Shader* fragment;
    unsigned int id;
};
