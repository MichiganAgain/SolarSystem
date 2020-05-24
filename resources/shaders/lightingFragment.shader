#version 330 core

uniform sampler2D texture0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 fPos;
in vec2 fTexPos;
in vec3 fNormal;

out vec4 FragColor;

void main() {
    float ambientStrength = 0.1f;

    vec3 normal = normalize(fNormal);
    vec3 lightDir = normalize(lightPos - fPos);
    float diffusion = max(dot(normal, lightDir), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(viewPos - fPos);
    vec3 reflectDirection = reflect(-lightDir, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32) * specularStrength;

    vec4 resultingColor = (ambientStrength + diffusion + specular) * lightColor;
    FragColor = texture(texture0, fTexPos) * resultingColor;
}
