#include "Enemy.h"
#include "EnemyBullet.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include <cassert>
#include <player.h>

// �ڋ߃t�F�[�Y�X�V�֐�
void Enemy::PhaseApproach(const Vector3& v1, const Vector3& v2) {
	worldTransform_.translation_ = utility_->Add(v1, v2);
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	// ���˃^�C�}�[�J�E���g�_�E��
	--fireTimer_;
	// �w�莞�Ԃɓ��B����
	if (fireTimer_ == 0) {
		// �e�𔭎�
		Fire();
		// ���˃^�C�}�[�̏�����
		fireTimer_ = kFireInterval;
	}
}

void Enemy::OnCollision() { isDead_ = true; }

// �e�̏���
void Enemy::Fire() {
	assert(player_);
	assert(gameScene_);
	// �e�̑��x
	const float kBulletSpeed = 1.0f;

	Vector3 playerVector = player_->GetWorldPosition();
	Vector3 enemyVector = GetWorldPosition();
	Vector3 vector = utility_->Subract(playerVector, enemyVector);
	vector = utility_->Normalize(vector);
	Vector3 velocity = utility_->Multiply(kBulletSpeed, vector);

	// �e�𐶐��A������
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	gameScene_->AddEnemyBullet(newBullet);
}

// �ڋ߃t�F�[�Y������
void Enemy::approachInitialize() {
	// ���˃^�C�}�[��������
	fireTimer_ = kFireInterval;
}

// ���E�t�F�[�Y�X�V�֐�
void Enemy::PhaseLeave(const Vector3& v1, const Vector3& v2) {
	worldTransform_.translation_ = utility_->Add(v1, v2);
}

Vector3 Enemy::GetWorldPosition() {
	// ���[���h���W������֐�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Enemy::~Enemy() { delete utility_; }

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& position) {
	assert(model);
	textureHandle_ = textureHandle;
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocityApproach = {0.0f, 0.0f, -0.0f};
	velocityLeave = {-0.05f, 0.05f, -0.1f};

	// �e�𔭎�
	// Fire();
	// �ڋ߃t�F�[�Y������
	approachInitialize();
}

/// <summary>
/// ���t���[������
/// </summary>
void Enemy::Update() {

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		// �ړ�
		PhaseApproach(worldTransform_.translation_, velocityApproach);

		break;
	case Enemy::Phase::Leave:
		// �ړ�
		PhaseLeave(worldTransform_.translation_, velocityLeave);
		break;
	}

	worldTransform_.UpdateMatrix();

	ImGui::Begin("EnemyPos");
	ImGui::Text(
	    "EnemyPos %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);

	ImGui::End();
};

/// <summary>
/// �`��
/// </summary>
void Enemy::Draw(ViewProjection viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
};