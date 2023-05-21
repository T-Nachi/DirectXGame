#include "Enemy.h"
#include "ImGuiManager.h"
#include <cassert>
Enemy::~Enemy() { delete utility_; }

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	textureHandle_ = textureHandle;
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = {0, 0, 50};
	velocity_ = {0, 0, -0.5f};
}

/// <summary>
/// –ˆƒtƒŒ[ƒ€ˆ—
/// </summary>
void Enemy::Update() {
	worldTransform_.translation_ = utility_->Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix();
};

/// <summary>
/// •`‰æ
/// </summary>
void Enemy::Draw(ViewProjection viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
};