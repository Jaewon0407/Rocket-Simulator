#include <iostream>

#include "../include/Project/Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void init_GL(GLFWwindow** window, int width, int height);

int main() {

    int width = 800;
    int height = 600;
    GLFWwindow* window;

    init_GL(&window, width, height);

    Renderer renderer(window);
    renderer.render();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void init_GL(GLFWwindow** window, int width, int height) {
    glewExperimental = GL_TRUE; 
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(width, height, "Rocket Simulation", nullptr, nullptr);
    if (!*window) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return;
    }
} 