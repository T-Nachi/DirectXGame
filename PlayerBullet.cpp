#include "PlayerBullet.h"
#include "ImGuiManager.h"
#include <cassert>

/// <summary>
/// ‰Šú‰»
/// </summary>
void PlayerBullet::Initialize(Model* model, Vector3& position) {

	assert(model);
	textureHandle_ = TextureManager::Load("slime.png");
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
};

/// <summary>
/// –ˆƒtƒŒ[ƒ€ˆ—
/// </summary>
void PlayerBullet::Update() { worldTransform_.UpdateMatrix(); };

/// <summary>
/// •`‰æ
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
};