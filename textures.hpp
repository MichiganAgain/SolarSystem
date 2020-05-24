#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <unordered_map>

enum class TEXTURES: unsigned int {GRADIENT};

class Texture {
    public:
        static unsigned int getTexture(TEXTURES t);

    private:
        static unsigned int loadTexture(TEXTURES t);

        static inline std::unordered_map<TEXTURES, unsigned int> textureMap = {};
};

#endif