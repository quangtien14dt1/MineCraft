#pragma once

#include "CubeTexture.h"
#include "QuadTexture.h"

class CubeTexture  : public QuadTexture {
public:

    CubeTexture(const std::string& );

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
    GLfloat m_imageSize;
    GLfloat m_individualTextureSize;

};
