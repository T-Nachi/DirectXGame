#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "Utility.h"
#include "WorldTransform.h"

class Player {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle_);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewprojection);

	void Attack();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	Vector3 move = {0, 0, 0};

	Utility* utility_ = nullptr;

	// �e
	PlayerBullet* bullet_ = nullptr;
};