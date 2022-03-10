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
        -0.5f, -0.5f,  0.5f, //0
         0.5f, -0.5f,  0.5f, //1
         0.5f, -0.5f, -0.5f, //2
        -0.5f, -0.5f, -0.5f, //3
        -0.5f,  0.5f,  0.5f, //4
         0.5f,  0.5f,  0.5f, //5
         0.5f,  0.5f, -0.5f  //6
        -0.5f,  0.5f, -0.5f, //7
    };

    static constexpr unsigned int indices[] = {
        //Bot
        0, 1, 2,
        3, 2, 0, 
        
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
        // //Top
        // 4, 5, 6,
        // 4, 6, 7,

        // //Back
        // 6, 2, 3,
        // 7, 6, 3,

        // //Front
        // 0, 1, 5,
        // 0, 5, 4,

        // //Left
        // 7, 3, 0,
        // 7, 0, 4,

        // //Right
        // 1, 2, 6, 
        // 1, 6, 5
    };
};
