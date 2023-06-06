#pragma once

#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "Utility.h"
#include "WorldTransform.h"
#include <list>

class Skydome {
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection viewprojection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};