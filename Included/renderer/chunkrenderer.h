#pragma once

#include "glm.h"
#include "baserender.h"s
#include <array>
#include <vector>

class BasicShader;
class Camera;
class ChunkModel;

class ChunkRenderer : public BaseRender
{
public:
	ChunkRenderer();

	void RenderModels(Camera* , ChunkModel* );

	~ChunkRenderer();

private:
	BasicShader* _chunkShader;
};