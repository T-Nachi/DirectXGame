#include "Player.h"
#include "ImGuiManager.h"
#include <cassert>

Player::~Player() {
	delete utility_;
	for (PlayerBullet* bullet : bullets_) {

		delete bullet;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	textureHandle_ = textureHandle;
	model_ = model;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::OnCollision() {}

void Player::Attack() {

	if (input_->PushKey(DIK_SPACE)) {
		// �e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = utility_->TransformNormal(velocity, worldTransform_.matWorld_);

		// �e�𐶐��A������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPosition() {
	// ���[���h���W������֐�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

void Player::Update() {

	// �f�X�t���O���������e���폜
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	const float kCharacterSpeed = 0.2f;
	const float kRotSpeed = 0.02f;

	// ���E�ړ�
	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	// �㉺�ړ�
	if (input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	}

	// ����
	if (input_->PushKey(DIK_RIGHTARROW)) {
		worldTransform_.rotation_.y += kRotSpeed;
	} else if (input_->PushKey(DIK_LEFTARROW)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}

	Attack();

	for (PlayerBullet* bullet : bullets_) {

		bullet->Update();
	}

	// �͈͂𒴂��Ȃ�����

	// ���s�ړ�
	Matrix4x4 translateMatrix = utility_->MakeTranselateMatrix(move);
	worldTransform_.translation_ = utility_->Transform(move, translateMatrix);

	worldTransform_.UpdateMatrix();

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
	// �e�̕`��
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewprojection);
	}
}