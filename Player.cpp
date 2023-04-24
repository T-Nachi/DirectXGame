#include"Player.h"
#include<cassert>
void Player::Initialize(Model* model, uint32_t textureHandle, WorldTransform worldtransform) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldtransform_ = worldtransform;
	
}
void Player::Update() { worldtransform_.TransferMatrix(); }
void Player::Draw(ViewProjection viewprojection) { 
	model_->Draw(worldtransform_,viewprojection, textureHandle_);
}