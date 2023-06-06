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
	/// ������
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewprojection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};