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

#define MOVEMENT_SPEED 0.03


static void glfw_error_callback(int error, const char* desc);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_callback(GLFWwindow* window, double posx, double posy);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


GLFWmonitor* monitor;
GLFWwindow* window;
glm::vec<2, int> winSize(600);

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

    window = glfwCreateWindow(winSize.x, winSize.y, "Title", NULL, NULL);

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);  
        
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
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * 3 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);

    // math stuff
    glUseProgram(shaderProgram.id);
    
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)winSize.x/winSize.y, 0.1f, 1000.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    unsigned int projectionLoc = glGetUniformLocation(shaderProgram.id, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram.id, "view");
    unsigned int modelLoc = glGetUniformLocation(shaderProgram.id, "model");

    unsigned int resolutionLoc = glGetUniformLocation(shaderProgram.id, "u_resolution");
    glUniform2fv(resolutionLoc, 1, glm::value_ptr(glm::vec2(winSize.x, winSize.y)));

    glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, -3.0f);
    glm::vec3 camFront    = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 camUp       = glm::vec3(0.0f, 1.0f, 0.0f);

    const float camSpeed = MOVEMENT_SPEED;

    // Main loop
    while (!glfwWindowShouldClose(window)) // glfwSetWindowCloseCallbakc, glfwSetWindowShouldClose
    {
        // main loop :)

        //input
        // camSpeed = glm::vec3();

        if (glfwGetKey(window, GLFW_KEY_W))
            camPosition += camFront * camSpeed;

        if (glfwGetKey(window, GLFW_KEY_S))
            camPosition -= camFront * camSpeed;

        if (glfwGetKey(window, GLFW_KEY_A))
            camPosition -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed; 
        
        if (glfwGetKey(window, GLFW_KEY_D))
            camPosition += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
        
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            camPosition += camUp * camSpeed;

        if (glfwGetKey(window, GLFW_KEY_SPACE))
            camPosition -= camUp * camSpeed;

        glm::vec<2, double> mousePos;
        glfwGetCursorPos(window, &(mousePos.x), &(mousePos.y));

        view = glm::mat4(1.0f);
        // view = glm::translate(view, glm::vec3(playerSpeed.x, playerSpeed.y, playerSpeed.z));
        view = glm::translate(view, camPosition);
    
        //rendering
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram.id);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // TODO: resolve the resize context problem

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
        glViewport(0, 0, mode->width, mode->height);
        glfwSetWindowSize(window, mode->width, mode->height);
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
