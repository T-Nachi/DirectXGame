#pragma once
#include "Utility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class RailCamera {
public:
	~RailCamera();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �r���[�v���W�F�N�V�������擾
	/// </summary>
	/// <returns>�r���[�v���W�F�N�V����</returns>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

	/// <summary>
	/// ���[���h�g�����X�t�H�[�����擾
	/// </summary>
	const WorldTransform& GetWorldMatrix() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// ���w�֐�
	Utility* utility_ = nullptr;

	// ���x
	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};
	// �p�x
	Vector3 rotation_ = {0.0f, 0.0f, 0.0f};
};
