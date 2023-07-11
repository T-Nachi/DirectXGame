#include "Player.h"
#include "ImGuiManager.h"
#include <cassert>

Player::~Player() {
	delete utility_;
	for (PlayerBullet* bullet : bullets_) {

		delete bullet;
	}

	delete sprite2DReticle_;
}

void Player::Initialize(Model* model, uint32_t textureHandle, const Vector3& position) {
	assert(model);

	textureHandle_ = textureHandle;
	// ���e�B�N���p�e�N�X�`���擾

	uint32_t textureReticle_ = TextureManager::Load("Reticle.png");
	// �X�v���C�g����
	sprite2DReticle_ = Sprite::Create(
	    textureReticle_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	model_ = model;
	reticleModel_ = model;

	worldTransform_.translation_ = position;
	worldTransform_.Initialize();

	// 3D���e�B�N���p�g�����X�t�H�[��������
	worldTransform3DReticle_.Initialize();

	input_ = Input::GetInstance();
}

void Player::OnCollision() {}

void Player::Attack() {

	if (input_->PushKey(DIK_SPACE)) {
		// �e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, 0);

		// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = utility_->Subract(Get3DReticleWorldPosition(), GetWorldPosition());
		velocity = utility_->Multiply(kBulletSpeed, utility_->Normalize(velocity));
		Vector3 position = GetWorldPosition();

		// �e�𐶐��A������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, position, velocity);

		bullets_.push_back(newBullet);
	}
}

Vector3 Player::Get3DReticleWorldPosition() {
	// ���[���h���W������֐�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];
	return worldPos;
}

Vector3 Player::GetWorldPosition() {
	// ���[���h���W������֐�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Vector3 Player::GetWorldRotation() {
	// �p�x������֐�
	Vector3 worldRota;
	// �p�x���擾�i���W�A���j
	worldRota.x = worldTransform_.rotation_.x;
	worldRota.y = worldTransform_.rotation_.y;
	worldRota.z = worldTransform_.rotation_.z;
	return worldRota;
}

void Player::SetParent(const WorldTransform* parent) {
	// �e�q�֌n������
	worldTransform_.parent_ = parent;
	worldTransform3DReticle_.parent_ = parent;
}

void Player::Update(const ViewProjection& viewProjection) {

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
	move = {0, 0, 0};
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

	// ���@������3D���e�B�N���ւ̋���
	const float kDistancePlayerTo3DReticle = 50.0f;
	// ���@����3D���e�B�N���̃I�t�Z�b�g(z+����)
	Vector3 offset = {0, 0, 1.0f};
	offset = utility_->TransformNormal(offset, worldTransform_.matWorld_);
	// �x�N�g���̒����𐮂���
	offset = utility_->Multiply(kDistancePlayerTo3DReticle, utility_->Normalize(offset));
	// 3D���e�B�N���̍��W��ݒ�
	worldTransform3DReticle_.translation_ = {
	    worldTransform_.translation_.x + offset.x, worldTransform_.translation_.y + offset.y,
	    worldTransform_.translation_.z + offset.z};

	Attack();

	for (PlayerBullet* bullet : bullets_) {

		bullet->Update();
	}

	// ���s�ړ�
	worldTransform_.translation_ = utility_->Add(move, worldTransform_.translation_);

	// �͈͂𒴂��Ȃ�����
	/*
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.x, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.x, +kMoveLimitY);
	*/

	worldTransform_.UpdateMatrix();
	worldTransform3DReticle_.UpdateMatrix();

	// 3D���e�B�b�N���̃��[���h���W����2D���e�B�N���̃X�N���[�����W���v�Z
	Vector3 posReticle = Get3DReticleWorldPosition();

	// �r���[�|�[�g�s��
	Matrix4x4 matViewport =
	    utility_->MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	// �r���[�|�[�g�s��ƃv���W�F�N�V�����s��A�r���[�s�������
	Matrix4x4 matViewProjectionViewport = utility_->Multiply(
	    utility_->Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);

	// ���[���h���W����X�N���[�����W�ϊ��i������3D����2D�ɂȂ�j
	posReticle = utility_->Transform(posReticle, matViewProjectionViewport);

	// �X�v���C�g�̃��e�B�N���ɍ��W�ݒ�
	sprite2DReticle_->SetPosition(Vector2(posReticle.x, posReticle.y));

	ImGui::Begin("PlayerPos");
	ImGui::Text(
	    "PlayerPos %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::SliderFloat3("pos", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::End();
}

void Player::Draw(ViewProjection viewprojection) {
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
	// �e�̕`��
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewprojection);
	}
	// reticleModel_->Draw(worldTransform3DReticle_, viewprojection);
}

void Player::DrawUI() { sprite2DReticle_->Draw(); }