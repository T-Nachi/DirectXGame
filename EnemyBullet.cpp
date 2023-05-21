#include "EnemyBullet.h"
#include "ImGuiManager.h"
#include <cassert>

EnemyBullet::~EnemyBullet() { delete utility_; }

/// <summary>
/// ������
/// </summary>
void EnemyBullet::Initialize(Model* model, Vector3& position, const Vector3& velocity) {

	assert(model);
	textureHandle_ = TextureManager::Load("slime3.png");
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
};

/// <summary>
/// ���t���[������
/// </summary>
void EnemyBullet::Update() {

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
void EnemyBullet::Draw(const ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
};