#include <iostream>
#include <stdio.h>

#define GLFW_INCLUDE_NONE // tell glfw not to include its opengl 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "fileman.hpp"
#include "models.hpp"
#include "shaders.hpp"


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
#pragma region GLFW Setup
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
#pragma endregion

    // shader setup
    Shader vertexShader(GL_VERTEX_SHADER, "res/main.vert.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "res/main.frag.glsl");

    ShaderProgram shaderProgram(&fragmentShader, &vertexShader);

    glUseProgram(shaderProgram.id);
    glDeleteShader(shaderProgram.vertex->id);
    glDeleteShader(shaderProgram.fragment->id);

    // buffer setup
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // bindings
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Square::vertices), Square::vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Square::indices), Square::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * 3 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * 3 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    // math stuff
    glUseProgram(shaderProgram.id);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)winSize.width/winSize.height, 0.1f, 1000.0f);
    glm::mat4 transform(1.0f);
    transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    // glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));

    unsigned int matLoc = glGetUniformLocation(shaderProgram.id, "transform");

    // Main loop
    while (!glfwWindowShouldClose(window)) // glfwSetWindowCloseCallbakc, glfwSetWindowShouldClose
    {
        // main loop :)

        transform = glm::rotate(transform, glm::radians(0.1f), glm::vec3(1.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(0.2f), glm::vec3(0.0f, 0.0f, 1.0f));

        //rendering
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram.id);
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
