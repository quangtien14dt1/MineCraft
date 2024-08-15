#include "renderer/chunkrenderer.h"
#include "shader/basicshader.h"
#include "world/block/blockdatabase.h"
#include "world/chunk/chunkmodel.h"
#include "basemodel.h"
#include "entity/camera.h"
#include "ultils/matrix.h"


ChunkRenderer::ChunkRenderer() 
	: _chunkShader(NULL)
{
	_chunkShader = new BasicShader("Chunk", "Chunk");
}

void 
ChunkRenderer::Add(const ChunkModel& model) {
	_chunks.push_back(&model);
};

void 
ChunkRenderer::Render(Camera* camera) {
	_chunkShader->Activate();
	BlockDatabase::GetInstance()->GetTexture()->bind();

	/* update camera */
	camera->UpdateCameraVector();

	/* project view model */
	_chunkShader->LoadViewMatrix(camera->GetViewMatrix());
	_chunkShader->LoadProjectionMatrix(camera->GetProjectionMatrix());
	for (const ChunkModel* chunk : _chunks) {

		chunk->GetModel()->GetVao().bind();

		_chunkShader->LoadModelMatrix( MakeModelMatrix( 
			ConvertToGlmVec3i(chunk->GetChunkLocation()), DEFAULT_ROTATION)
		);
	}
	
};

ChunkRenderer::~ChunkRenderer() {
	if (_chunkShader != NULL) {
		delete _chunkShader; _chunkShader = nullptr;
	}
};