#include "Skydom.h"
void Skydome::Initialize(Model* model) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
}

/// <summary>
/// ���t���[������
/// </summary>
void Skydome::Update() {

	worldTransform_.scale_ = {500, 500, 500};
	worldTransform_.UpdateMatrix();
};

/// <summary>
/// �`��
/// </summary>
void Skydome::Draw(ViewProjection viewprojection) {
	model_->Draw(worldTransform_, viewprojection);
};