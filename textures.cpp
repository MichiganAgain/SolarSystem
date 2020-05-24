#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <unordered_map>
#include <stb_image.h>
#include <iostream>
#include <stdexcept>

#include "textures.hpp"

unsigned int Texture::getTexture(TEXTURES t) {
    std::unordered_map<TEXTURES, unsigned int>::iterator i;
    if ((i = textureMap.find(t)) != textureMap.end()) return i->second;

    unsigned int textureID = loadTexture(t);
    textureMap.insert(std::pair<TEXTURES, unsigned int>(t, textureID));
    return textureID;
}

unsigned int Texture::loadTexture(TEXTURES t) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, channelsInFile;
    unsigned char* data;
    
    switch (t) {
        case TEXTURES::GRADIENT:
            data = stbi_load("resources/textures/grayGradient.jpeg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        default:
            throw std::runtime_error("Failed to find texture");
    }

    if (!data) throw std::runtime_error("Failed to load existing texture");
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return textureID;
}
