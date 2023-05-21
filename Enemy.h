#pragma once
#include "Input.h"
#include "Model.h"
#include "Utility.h"
#include "WorldTransform.h"

class Enemy {
public:
	~Enemy();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle_);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection viewprojection);

	void PhaseApproach(const Vector3& v1, const Vector3& v2);

	void PhaseLeave(const Vector3& v1, const Vector3& v2);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Utility* utility_ = nullptr;
	Vector3 velocityApproach = {0, 0, 0};
	Vector3 velocityLeave = {0, 0, 0};

	enum class Phase {
		Approach, // Ú‹ß‚·‚é
		Leave,    // —£’E‚·‚é

	};

	Phase phase_ = Phase::Approach;
};