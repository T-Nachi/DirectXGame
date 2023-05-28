#include "PlayerBullet.h"
#include "ImGuiManager.h"
#include <cassert>

Vector3 PlayerBullet::GetWorldPosition() {
	// ���[���h���W������֐�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
void PlayerBullet::OnCollision() { isDead_ = true; }

PlayerBullet::~PlayerBullet() { delete utility_; }

/// <summary>
/// ������
/// </summary>
void PlayerBullet::Initialize(Model* model, Vector3& position, const Vector3& velocity) {

	assert(model);
	textureHandle_ = TextureManager::Load("slime2.png");
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
};

/// <summary>
/// ���t���[������
/// </summary>
void PlayerBullet::Update() {

	// ���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.translation_ = utility_->Add(worldTransform_.translation_, velocity_);
	worldTransform_.UpdateMatrix();
};

/// <summary>
/// �`��
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
};