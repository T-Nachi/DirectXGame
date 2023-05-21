#pragma once
#include "ImGuiManager.h"
#include "WorldTransform.h"
#include <cassert>

class Utility {
public:
	// ��]X
	Matrix4x4 MakeRotateXMatrix(float theta);
	// Y
	Matrix4x4 MakeRotateYMatrix(float theta);

	// Z
	Matrix4x4 MakeRotateZMatrix(float theta);

	// �X�J���[�{
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	// ���s�ړ�
	Matrix4x4 MakeTranselateMatrix(const Vector3& translate);

	// �A�t�B���ϊ�
	Matrix4x4
	    MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
	// ���Z
	Vector3 Add(const Vector3& v1, const Vector3& v2);

	// ���Z
	Vector3 Subract(const Vector3& v1, const Vector3& v2);

	// �X�J���[�{
	Vector3 Multiply(float scalar, const Vector3& v);

	// ����(�m���})
	float Length(const Vector3& v);

	// ���K��
	Vector3 Normalize(const Vector3& v);

	//
	Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);
};