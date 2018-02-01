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
	/*
	// @class		Camera �N���X
	// @content		�J����
	// @use			�O���[�o�����W�n�̕`��Ɏg�p
	*/
	class Camera
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix = DirectX::SimpleMath::Matrix;

	public:
		/*
		// @struct		View �\����
		// @content		�r���[�s��֌W
		*/
		struct View
		{
			Matrix viewMat;				// �r���[�s��
			Vector3 eyePos;				// �J�������_
			Vector3 refPos;				// �^�[�Q�b�g���W
			Vector3 upVec;				// ������x�N�g��
		};

		/*
		// @struct		Projection �\����
		// @content		�v���W�F�N�V�����s��֌W
		*/
		struct Projection
		{
			Matrix projMat;				// �v���W�F�N�V�����s��
			float fov;					// �c��������p
			float aspect;				// �A�X�y�N�g��
			float nearClip;				// �j�A�N���b�v
			float farClip;				// �t�@�[�N���b�v
		};

	protected:
		View			view_;					// �r���[�s��֌W
		Projection		proj_;					// �v���W�F�N�V�����s��֌W

		Matrix			billboard_;				// �r���{�[�h�s��
		Matrix			billboardConstrainY_;	// �r���{�[�h�s��iY������j

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		��ʂ̕��iint�j
		// @param		��ʂ̍����iint�j
		*/
		Camera(int width, int height);

		// �f�X�g���N�^
		virtual ~Camera() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		virtual void Update();

		/*
		// @method		CalcBillboard
		// @content		�r���{�[�h�s��̌v�Z
		*/
		virtual void CalcBillboard();

		/* �A�N�Z�b�T */

		void SetEyePos(const Vector3& pos)						{ view_.eyePos = pos; }
		void SetRefPos(const Vector3& pos)						{ view_.refPos = pos; }
		void SetUpVec(const Vector3& vec)						{ view_.upVec = vec; }
		void SetFov(float fov)									{ proj_.fov = fov; }
		void SetAspect(float aspect)							{ proj_.aspect = aspect; }
		void SetNearClip(float nearClip)						{ proj_.nearClip = nearClip; }
		void SetFarClip(float farClip)							{ proj_.farClip = farClip; }

		inline const Matrix& GetView() const					{ return view_.viewMat; }
		inline const Vector3& GetEyePos() const					{ return view_.eyePos; }
		inline const Vector3& GetRefPos() const					{ return view_.refPos; }
		inline const Vector3& GetUpVec() const					{ return view_.upVec; }
		inline const Matrix& GetProjection() const				{ return proj_.projMat; }
		inline float GetFov() const								{ return proj_.fov; }
		inline float GetAspect() const							{ return proj_.aspect; }
		inline float GetNearClip() const						{ return proj_.nearClip; }
		inline float GetFarClip() const							{ return proj_.farClip; }
		inline const Matrix& GetBillboard() const				{ return billboard_; }
		inline const Matrix& GetBillboardConstrainY() const		{ return billboardConstrainY_; }
	};
}