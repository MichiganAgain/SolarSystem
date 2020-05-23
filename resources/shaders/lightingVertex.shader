#version 330 core

layout (location = 0) in vec3 vPos;

uniform mat4 modelMatrix;

out vec2 fTexPos;

void main() {
    gl_Position = modelMatrix * vec4(vPos.x, vPos.y, vPos.z, 1.0f);
    //fTexPos = vTexPos;
}
