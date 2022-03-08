#include <iostream>
#include <stdio.h>

#define GLFW_INCLUDE_NONE // tell glfw not to include its opengl 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "fileman.h"
#include "models.h"


static void glfw_error_callback(int error, const char* desc);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_callback(GLFWwindow* window, double posx, double posy);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

struct WinSize
{
    unsigned int width;
    unsigned int height;

    WinSize(unsigned int a_width, unsigned int a_height) : height(a_height), width(a_width) { } 
};


GLFWmonitor* monitor;
GLFWwindow* window;
WinSize winSize(600, 600);

int main(void)
{
    // setup
    // glfw setup
    if (!glfwInit())
        return -1; // Initialization failed

    glfwSetErrorCallback(glfw_error_callback);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // opengl version
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor); // get monitor's params

    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(winSize.width, winSize.height, "Title", NULL, NULL);

    if (!window)
        return -1; // window or opengl context creation failed

    glfwMakeContextCurrent(window); // make opengl context current

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // link with glad

    glfwSetKeyCallback(window, key_callback); // input bind
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // shader setup
    unsigned int vertexShader;
    unsigned int fragmentShader;

    // vertex shader compilation
    {
        const char* source = load_text("res/main.vertex");

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &source, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            printf("Vertex shader compilation failed: %s\n", infoLog);
        }

        delete source;
    };

    // fragment shader compilation
    {
        const char* source = load_text("res/main.fragment");
        
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &source, NULL);
        glCompileShader(fragmentShader);

        int success;
        char infoLog[512];

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            printf("Fragment shader compilation error: %s\n", infoLog);
        }

        delete source;
    };

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    {
        int success;
        char infoLog[512];

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            printf("Shader linking error: %s \n", infoLog);
        }
    };

    // buffer setup
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // bindings
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Main loop
    while (!glfwWindowShouldClose(window)) // glfwSetWindowCloseCallbakc, glfwSetWindowShouldClose
    {
        // main loop :)



        //rendering
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate(); // destroy remaining windows

    return 0;
}

static void glfw_error_callback(int error, const char* desc)
{
    fprintf(stderr, "glfw error: %s\n", desc);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);

        // glfwSetWindowSize();
    }

    if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor); // get monitor's params

        printf("w: %i, h: %i \n", mode->width, mode->height);

        // glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        glfwSetWindowSize(window, mode->width, mode->height);
        glViewport(0, 0, mode->width, mode->height);
    }

    printf("Key pressed: %i\n", key);
}

static void mouse_callback(GLFWwindow* window, double posx, double posy)
{
    printf("x: %f, y: %f \n", posx, posy);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    printf("scroll: x: %f, y: %f \n", xoffset, yoffset);
}
