#include "Player.h"
#include "ImGuiManager.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	textureHandle_ = textureHandle;
	model_ = model;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Attack() {

	if (input_->PushKey(DIK_SPACE)) {
		// ’e‚ð¶¬A‰Šú‰»
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		bullet_ = newBullet;
	}
}

void Player::Update() {

	const float kCharacterSpeed = 0.2f;
	const float kRotSpeed = 0.02f;

	// ¶‰EˆÚ“®
	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	// ã‰ºˆÚ“®
	if (input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	}

	// ù‰ñ
	if (input_->PushKey(DIK_RIGHTARROW)) {
		worldTransform_.rotation_.y += kRotSpeed;
	} else if (input_->PushKey(DIK_LEFTARROW)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}

	Attack();

	if (bullet_) {

		bullet_->Update();
	}
	// ”ÍˆÍ‚ð’´‚¦‚È‚¢ˆ—

	// •½sˆÚ“®
	Matrix4x4 translateMatrix = utility_->MakeTranselateMatrix(move);
	worldTransform_.translation_ = utility_->Transform(move, translateMatrix);

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

	const float kMoveLimitX = 640.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);

	ImGui::Begin("Debug1");
	ImGui::Text(
	    "PlayerPos %d.%d,%d", worldTransform_.matWorld_.m[3][0], worldTransform_.translation_.y,
	    move.z);
	ImGui::End();
}

void Player::Draw(ViewProjection viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
	// ’e‚Ì•`‰æ
	if (bullet_) {
		bullet_->Draw(viewprojection);
	}
}