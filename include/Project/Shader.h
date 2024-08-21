#ifndef SHADER_H
#define SHADER_H

const char* vertexShaderSource = R"(
#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
}

)";

const char* fragmentShaderSource = R"(
#version 330
layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = vec4(1.0, 0.5, 0.3, 1.0);
}

)";

#endif