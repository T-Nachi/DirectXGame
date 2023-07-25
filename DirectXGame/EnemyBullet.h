#pragma once
#include "Input.h"
#include "Model.h"
#include "Utility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemyBullet {
public:
	~EnemyBullet();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, Vector3& position, const Vector3& velocity);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewprojection);

	bool IsDead() const { return isDead_; }

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Utility* utility_ = nullptr;

	// ���x
	Vector3 velocity_;

	// ����
	static const int32_t kLifeTime = 60 * 5;
	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	// �f�X�t���O
	bool isDead_ = false;
};