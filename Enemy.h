#pragma once
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "Utility.h"
#include "WorldTransform.h"
#include <list>

class Enemy {
public:
	~Enemy();

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

	// 接近フェーズ関数
	void PhaseApproach(const Vector3& v1, const Vector3& v2);
	// 離脱フェーズ関数
	void PhaseLeave(const Vector3& v1, const Vector3& v2);

	// 弾の関数
	void Fire();

	void approachInitialize();

public:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Utility* utility_ = nullptr;

	// 発射間隔
	static const int kFireInterval = 60;
	// 発射タイマー
	int32_t fireTimer_ = 0;

	// フェーズ
	Vector3 velocityApproach = {0, 0, 0};
	Vector3 velocityLeave = {0, 0, 0};

	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する

	};

	Phase phase_ = Phase::Approach;

	// 弾
	std::list<EnemyBullet*> bullets_;
};