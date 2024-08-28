#include "ultils/matrix.h"
#include <SFML/Graphics.hpp>

glm::mat4 MakeModelMatrix(
	const glm::vec3& location,
	const glm::vec3& rotation)
{
	glm::mat4 mat = glm::mat4(1.0f);

	auto rotateMatrix = [&mat](const glm::vec3& rotation) {
		glm::vec3 axes[] = {
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		};

		for (int i = 0; i < 3; ++i) {
			mat = glm::rotate(mat, glm::radians(rotation[i]), axes[i]);
		}
		};

	rotateMatrix(rotation);

	mat = glm::translate(mat, location);

	return mat;

};

glm::vec3 ConvertToGlmVec3f(const sf::Vector3f& sfVector) {
	return glm::vec3(static_cast<float>(sfVector.x),
		static_cast<float>(sfVector.y),
		static_cast<float>(sfVector.z));
}

sf::Vector3f ConvertToSfVector3f(const glm::vec3& glmVector) {
	return sf::Vector3f(static_cast<int>(glmVector.x),
		static_cast<int>(glmVector.y),
		static_cast<int>(glmVector.z));
};
