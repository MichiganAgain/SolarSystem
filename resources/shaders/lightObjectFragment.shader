#version 330 core

uniform sampler2D texture0;

in vec2 fTexPos;
in vec3 fNormal;
out vec4 FragColor;

void main() {
    FragColor = texture(texture0, fTexPos);
}
