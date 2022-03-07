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

    printf("Key pressed: %i\n", key);
}

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

    glfwSetKeyCallback(window, key_callback); // input bind

    // specific input setup
    const int scancode = glfwGetKeyScancode(GLFW_KEY_F11);
    set_key_mapping(scancode, [](){ });

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
