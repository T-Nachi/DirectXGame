#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "Utility.h"
#include "WorldTransform.h"
#include <list>

class Player {
public:
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle_, const Vector3& position);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewprojection);

	void Attack();

	// ���[���h���W���擾
	Vector3 GetWorldPosition();
	// ��]�p���擾
	Vector3 GetWorldRotation();

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	// �e���X�g���擾
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

	/// <summary>
	/// �e�ƂȂ郏�[���h�g�����X�t�H�[�����Z�b�g
	/// </summary>
	void SetParent(const WorldTransform* parent);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	Vector3 move = {0, 0, 0};
	Player* player_;
	// ���w�֐�
	Utility* utility_ = nullptr;

	// �e
	std::list<PlayerBullet*> bullets_;
};