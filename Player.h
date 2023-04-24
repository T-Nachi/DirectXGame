#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Player {
	public:
	WorldTransform worldtransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection viewprojection_;
	void Initialize(Model* model, uint32_t textureHandle, WorldTransform worldtransform);
	void Update();
	void Draw(ViewProjection);
};

