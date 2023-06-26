#include "RailCamera.h"
#include "ImGuiManager.h"
RailCamera ::~RailCamera() { delete utility_; }

void RailCamera::Initialize(const Vector3& position, const Vector3& rotation) {
	// ���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	// �r���[�v���W�F�N�V�����̏�����
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();
}

/// <summary>
/// ���t���[������
/// </summary>
void RailCamera::Update() {

	const float kCameraSpeed = 0.1f;
	velocity_ = {0, 0, kCameraSpeed};
	// worldTransform_.rotation_.y += kCameraSpeed;

	// �ړ�
	worldTransform_.translation_ = utility_->Add(worldTransform_.translation_, velocity_);
	// ��]
	worldTransform_.rotation_ = utility_->Add(worldTransform_.rotation_, rotation_);
	// ���[���h�s��̍Čv�Z
	worldTransform_.matWorld_ = utility_->MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// �J�����I�u�W�F�N�g�̃��[���h�s�񂩂�r���[�s����v�Z����

	viewProjection_.matView = utility_->Inverse(worldTransform_.matWorld_);

	ImGui::Begin("Camera");
	ImGui::SliderFloat("CameraTranslation", &worldTransform_.translation_.x, 0.0f, 10.0f);
	ImGui::SliderFloat("CameraRotation", &worldTransform_.rotation_.x, 0.0f, 10.0f);
	ImGui::End();
}