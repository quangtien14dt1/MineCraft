#include "renderer/baserender.h"

BaseRender::BaseRender()
{ }

void BaseRender::AddModel(const BaseModel* m) {
	_model.push_back(m);
};


