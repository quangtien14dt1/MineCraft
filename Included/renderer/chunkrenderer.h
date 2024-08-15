#pragma once

#pragma once

#include "../glm.h"
#include <array>
#include <vector>

class BasicShader;
class Camera;
class ChunkModel;

class ChunkRenderer
{
public:
	ChunkRenderer();

	void Add(const ChunkModel& model);

	void Render(Camera* camera);

	~ChunkRenderer();

private:

	std::vector<const ChunkModel* > _chunks;

	BasicShader* _chunkShader;


};