#pragma once
struct Triangle 
{
    static constexpr float vertices[] = {
        -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f
    };
    
    static constexpr unsigned int indices[] = {
        0, 1, 2
    };
};


struct Square 
{ 
    static constexpr float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
    };

    static constexpr unsigned int indices[] = {  // note that we start from 0!
        1, 2, 3,    // second triangle
        0, 1, 3   // first triangle
    };
};

struct Star 
{ 
    static constexpr float vertices[] = {
        0.32f,  0.32f, 0.0f,  // top right
        0.32f, -0.32f, 0.0f,  // bottom right
        -0.32f, -0.32f, 0.0f,  // bottom left
        -0.32f,  0.32f, 0.0f,  // top left

        0.0f,  1.0f, 0.0f,
        1.0f,  0.0f, 0.0f, 
        0.0f, -1.0f, 0.0f,
        -1.0f,  0.0f, 0.0f
    };

    static constexpr unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle

        0, 3, 4,
        1, 0, 5,
        2, 1, 6,
        3, 2, 7
    }; 
};

struct Cube
{
    static constexpr float vertices[] = {
        -0.5f, -0.5f, -0.5f, //0  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, //1  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, //2  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, //3  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f, //4  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, //5  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, //6  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, //7  0.0f, 1.0f,
    };

    static constexpr unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6, 
        6, 7, 4, 
        
        7, 3, 0, 
        0, 4, 7, 
        
        6, 2, 1, 
        1, 5, 6, 
        
        0, 1, 5, 
        5, 4, 0, 
        
        3, 2, 6, 
        6, 7, 3
    };
};
