#include "Scene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>
/* void Scene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	 title = TextureManager::Load("./Resources./titlee.png");
	 clear = TextureManager::Load("./Resources./clearr.png");
	 over = TextureManager::Load("./Resources./overr.png");
	spriteScene = Sprite::Create(title, Vector2(0, 0), Vector4(1, 1, 1, 1), Vector2(0, 0));
}

void Scene::Draw(int s) {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();
#pragma endregion


#pragma region 
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region 
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	if (s == 0) {
		spriteScene->SetTextureHandle(title);
		spriteScene->Draw();
	} else if (s == 2) {
		spriteScene->SetTextureHandle(clear);

		spriteScene->Draw();
	} else if (s == 3) {
		spriteScene->SetTextureHandle(over);

		spriteScene->Draw();
	}

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}*/