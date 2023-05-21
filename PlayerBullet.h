#pragma once
#include "DebugCamera.h"
#include "Input.h"
#include "Model.h"
#include "Utility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class PlayerBullet {
public:
	~PlayerBullet();
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