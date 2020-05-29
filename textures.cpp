#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <stb/stb_image.h>
#include <unordered_map>
#include <iostream>
#include <stdexcept>

#include "textures.hpp"

/*
	A hash map is used to keep track of textures that have already been loaded.  If the texture requested is found
	in the hash map then the ID to that texture is returned.  Otherwise the loadTexture() function is called which
	generates a texture, get the ID and stores that ID in the hash map before finally returning it.
*/
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

    stbi_set_flip_vertically_on_load(true);		//	As OpenGL expects the top left image coord to be (0, 1)
    int width, height, channelsInFile;
    unsigned char* data;
    
    switch (t) {
        case TEXTURES::GRADIENT:
            data = stbi_load("resources/textures/grayGradient.jpeg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::EARTH:
            data = stbi_load("resources/textures/earth.png", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::SUN:
            data = stbi_load("resources/textures/sun.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::MOON:
            data = stbi_load("resources/textures/moon.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::MERCURY:
            data = stbi_load("resources/textures/mercury.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::VENUS:
            data = stbi_load("resources/textures/venus.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::MARS:
            data = stbi_load("resources/textures/mars.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::JUPITER:
            data = stbi_load("resources/textures/jupiter.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::SATURN:
            data = stbi_load("resources/textures/saturn.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::URANUS:
            data = stbi_load("resources/textures/uranus.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::NEPTUNE:
            data = stbi_load("resources/textures/neptune.jpg", &width, &height, &channelsInFile, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case TEXTURES::STAR:
            data = stbi_load("resources/textures/star.jpeg", &width, &height, &channelsInFile, 0);
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
