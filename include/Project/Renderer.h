#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Data.h"
#include "Shader.h"

class Renderer {
public:
    Renderer(GLFWwindow* window) : window(window) {}

    void init_shader() {
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        // Check if shader was compiled successfully
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        // Vertex Shader 
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "ERROR: Vertex shader compilation failed: " << infoLog << std::endl;
        }

        // Fragment Shader
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cout << "ERROR: Fragment shader compilation failed: " << infoLog << std::endl;
        }

        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check if shaders were linked successfully
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR: Linking failed: " << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    void render() {

        GLuint VBO, VAO;
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        // Allocate memory and store vertex data in VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        // Define how to interpret vertex data in VBO (3 floats, no strides)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // Enable vertex attribute at location = 0
        glEnableVertexAttribArray(0);

        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Unbind VAO
        glBindVertexArray(0);

        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }
private:
    GLFWwindow* window;
    unsigned int shaderProgram;
};

#endif