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
    static constexpr float s_vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    static constexpr unsigned int s_indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
};

struct Star 
{ 
    static constexpr float st_vertices[] = {
        0.32f,  0.32f, 0.0f,  // top right
        0.32f, -0.32f, 0.0f,  // bottom right
        -0.32f, -0.32f, 0.0f,  // bottom left
        -0.32f,  0.32f, 0.0f,  // top left

        0.0f,  1.0f, 0.0f,
        1.0f,  0.0f, 0.0f, 
        0.0f, -1.0f, 0.0f,
        -1.0f,  0.0f, 0.0f
    };

    static constexpr unsigned int st_indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle

        0, 3, 4,
        1, 0, 5,
        2, 1, 6,
        3, 2, 7
    }; 
};