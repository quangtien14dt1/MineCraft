#pragma once

#include <SFML/Graphics.hpp>
#include "glm.h"

glm::mat4 MakeModelMatrix(const glm::vec3&,const glm::vec3&);

glm::vec3 ConvertToGlmVec3i(const sf::Vector3i&);

sf::Vector3i ConvertToSfVector3i(const glm::vec3&);