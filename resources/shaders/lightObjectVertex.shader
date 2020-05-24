#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexPos;
layout (location = 2) in vec3 vNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 fTexPos;
out vec3 fNormal;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPos, 1.0f);
    fTexPos = vTexPos;
    fNormal = vNormal;
}
