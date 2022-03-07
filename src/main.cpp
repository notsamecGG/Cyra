#include <boost/bind.hpp>

#include <any>
#include <stdio.h>

#define GLFW_INCLUDE_NONE // tell glfw not to include its opengl 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"


static void glfw_error_callback(int error, const char* desc);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void key_callback_new(GLFWwindow* window, int key, int scancode, int action, int mods);

void printKey(std::any args);


struct WinSize
{
    unsigned int width;
    unsigned int height;

    WinSize(unsigned int a_width, unsigned int a_height) : height(a_height), width(a_width) { } 
};

int main(void)
{
    // setup
    GLFWmonitor* monitor;
    GLFWwindow* window;


    if (!glfwInit())
        return -1; // Initialization failed

    glfwSetErrorCallback(glfw_error_callback);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // opengl version
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor); // get monitor's params
    WinSize winSize(600, 600);

    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(winSize.width, winSize.height, "Title", NULL, NULL);



    if (!window)
        return -1; // window or opengl context creation failed

    glfwMakeContextCurrent(window); // make opengl context current

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // link with glad


    // specific input setup
    InputManager inputMan;
    glfwSetKeyCallback(window, key_callback); // input bind
    
    const int scancode = glfwGetKeyScancode(GLFW_KEY_F11);
    inputMan.addKey(scancode, printKey);
    

    // Main loop
    while (!glfwWindowShouldClose(window)) // glfwSetWindowCloseCallbakc, glfwSetWindowShouldClose
    {
        // main loop :)

        // glfwSetWindowSize(window, mode->width, mode->hegiht);

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
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    inputMan.querryKey(scancode, args);
    // printf("Key pressed: %i\n", key);
}

void printKey(std::any args)
{
    printf("key pressed");
}
