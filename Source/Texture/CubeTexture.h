#pragma once

#include "Texture.h"

class CubeTexture : public Texture {
public:

    CubeTexture(const std::string& );

    ~CubeTexture();

    /**
        MUST BE IN THIS ORDER:
            -right
            -left
            -top
            -bottom
            -back
            -front
    */
    std::vector<GLfloat>  GetTexture(const sf::Vector2f& coords);

private:
    int _imageSize;
    int _individualTextureSize;

};
