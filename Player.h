#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "Utility.h"
#include "WorldTransform.h"
#include <list>

class Player {
public:
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle_);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
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

	// 弾
	std::list<PlayerBullet*> bullets_;
};