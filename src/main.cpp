#include <stdio.h>

#define GLFW_INCLUDE_NONE // tell glfw not to include its opengl 
#include <glad/glad.h>
#include <GLFW/glfw3.h>


static void glfw_error_callback(int error, const char* desc)
{
    fprintf(stderr, "glfw error: %s\n", desc);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main(void)
{
    // setup
    GLFWwindow* window;

    if (!glfwInit())
        return -1; // Initialization failed

    glfwSetErrorCallback(glfw_error_callback);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // opengl version
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(600, 600, "Title", NULL, NULL);

    if (!window)
        return -1; // window or opengl context creation failed

    glfwMakeContextCurrent(window); // make opengl context current

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // link with glad

    glfwSetKeyCallback(window, key_callback);

    // Main loop
    while (!glfwWindowShouldClose(window)) // glfwSetWindowCloseCallbakc, glfwSetWindowShouldClose
    {

    }

    // cleanup
    glfwDestroyWindow(window);

    glfwTerminate(); // destroy remaining windows

    return 0;
}
