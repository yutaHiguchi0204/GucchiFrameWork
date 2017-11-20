/* =====================================================================
//! @param		�uCamera�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>

namespace GucchiLibrary
{
	// �N���X�̒�`
	class Camera
	{
	public:
		// �r���[�s��
		struct View
		{
			DirectX::SimpleMath::Matrix viewMat;		// �r���[�s��
			DirectX::SimpleMath::Vector3 eyePos;		// �J�������_
			DirectX::SimpleMath::Vector3 refPos;		// �^�[�Q�b�g���W
			DirectX::SimpleMath::Vector3 upVec;			// ������x�N�g��
		};

		// �v���W�F�N�V�����s��
		struct Projection
		{
			DirectX::SimpleMath::Matrix projMat;		// �v���W�F�N�V�����s��
			float fov;									// �c��������p
			float aspect;								// �A�X�y�N�g��
			float nearClip;								// �j�A�N���b�v
			float farClip;								// �t�@�[�N���b�v
		};

	protected:
		View		view_;								// �r���[�s��֌W
		Projection	proj_;								// �v���W�F�N�V�����s��֌W

	public:
		Camera(int width, int height);
		virtual ~Camera() {};

		// �X�V
		virtual void Update();

		// �A�N�Z�b�T
		void SetEyePos(const DirectX::SimpleMath::Vector3& pos)		{ view_.eyePos = pos; }
		void SetRefPos(const DirectX::SimpleMath::Vector3& pos)		{ view_.refPos = pos; }
		void SetUpVec(const DirectX::SimpleMath::Vector3& vec)		{ view_.upVec = vec; }
		void SetFov(float fov)										{ proj_.fov = fov; }
		void SetAspect(float aspect)								{ proj_.aspect = aspect; }
		void SetNearClip(float nearClip)							{ proj_.nearClip = nearClip; }
		void SetFarClip(float farClip)								{ proj_.farClip = farClip; }

		inline const DirectX::SimpleMath::Matrix& GetView()			{ return view_.viewMat; }
		inline const DirectX::SimpleMath::Vector3& GetEyePos()		{ return view_.eyePos; }
		inline const DirectX::SimpleMath::Vector3& GetRefPos()		{ return view_.refPos; }
		inline const DirectX::SimpleMath::Vector3& GetUpVec()		{ return view_.upVec; }
		inline const DirectX::SimpleMath::Matrix& GetProjection()	{ return proj_.projMat; }
		inline float GetFov()										{ return proj_.fov; }
		inline float GetAspect()									{ return proj_.aspect; }
		inline float GetNearClip()									{ return proj_.nearClip; }
		inline float GetFarClip()									{ return proj_.farClip; }
	};
}