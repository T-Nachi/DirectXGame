#pragma once
#include "Input.h"
#include "Model.h"
#include "Utility.h"
#include "WorldTransform.h"
#include <list>

// �N���X�̑O���錾
class Player;
class GameScene;

class Enemy {
public:
	~Enemy();

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

	// �ڋ߃t�F�[�Y�֐�
	void PhaseApproach(const Vector3& v1, const Vector3& v2);
	// ���E�t�F�[�Y�֐�
	void PhaseLeave(const Vector3& v1, const Vector3& v2);

	// �e�̊֐�
	void Fire();

	void approachInitialize();

	void SetPlayer(Player* player) { player_ = player; }

	bool IsDead() const { return isDead_; }

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	// �e���X�g���擾
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

public:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Utility* utility_ = nullptr;

	// �f�X�t���O
	bool isDead_ = false;

	// ���ˊԊu
	static const int kFireInterval = 60;
	// ���˃^�C�}�[
	int32_t fireTimer_ = 0;

	// �t�F�[�Y
	Vector3 velocityApproach = {0, 0, 0};
	Vector3 velocityLeave = {0, 0, 0};

	enum class Phase {
		Approach, // �ڋ߂���
		Leave,    // ���E����

	};

	Phase phase_ = Phase::Approach;

	GameScene* gameScene_ = nullptr;

	// ���L����
	Player* player_ = nullptr;
};
