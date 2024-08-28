#pragma once

#include <SFML/Graphics.hpp>
#include "glm.h"

glm::mat4 MakeModelMatrix(const glm::vec3&,const glm::vec3&);

glm::vec3 ConvertToGlmVec3f(const sf::Vector3f&);

sf::Vector3f ConvertToSfVector3f(const glm::vec3&);