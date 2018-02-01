/* =====================================================================
//! @param		�uParticle�v�w�b�_
//! @create		��� �T��
//! @date		17/12/27
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <VertexTypes.h>
#include "../3D/Asset3D.h"

namespace GucchiLibrary
{
	/*
	// @class		Particle �N���X
	// @content		�p�[�e�B�N��
	*/
	class Particle
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Vector4 = DirectX::SimpleMath::Vector4;

	public:
		/*
		// @content		���[�v���[�h
		// @mode		DEFAULT		�F	�����ɒ����ȃ��[�h�i-1�Ȃ�����Ȃ��A�ݒ肳��Ă���΂��̎��Ԃŏ�����j
		// @mode		REPEAT		�F	�����ɂȂ����珉��������ď��߂���G�t�F�N�g���J�n���郂�[�h
		// @mode		TURN		�F	REPEAT�Ɠ����d�l�����A�ʏ큨�t���ʏ큨�t�E�E�E�ƃA�j���[�V�������Đ�����郂�[�h
		*/
		enum class LOOP_MODE
		{
			DEFAULT,
			REPEAT,
			TURN,

			LOOP_MODE_NUM
		};

	public:
		static const int FOREVER_EXIST;			// �i���I����
		static const float DEFAULT_SCALE;		// �����X�P�[��
		static const float DEFAULT_ROTATE;		// ������]�p

	private:
		DirectX::VertexPositionColorTexture		vertexStart_;				// �n�_���
		DirectX::VertexPositionColorTexture		vertexEnd_;					// �I�_���
		DirectX::VertexPositionColorTexture		vertexNow_;					// ���݂̒��_�f�[�^

		float									exisTime_;					// ����
		float									nowFrame_;					// �o�����Ă���̌o�߃t���[��

		Asset3D::BLEND_MODE						blendMode_;					// �u�����h���[�h
		LOOP_MODE								loopMode_;					// ���[�v���[�h

		bool									isExist_;					// ���݂��Ă��邩�ǂ���

		std::unique_ptr<InterpolateDirector>	interpolateDirector_;		// ��ԃX�e�[�g

	public:
		// �R���X�g���N�^
		Particle() = default;

		// �R�s�[�R���X�g���N�^
		Particle(const Particle& particle);

		// �f�X�g���N�^
		virtual ~Particle() = default;

		/*
		// @method		Initialize
		// @content		����������
		// @param		�����ifloat�j							�F	�f�t�H���g�iFOREVER_EXIST�j
		// @param		�n�_���iVertexPositionColorTexture�j	�F	�f�t�H���g�iVertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		�I�_���iVertexPositionColorTexture�j	�F	�f�t�H���g�iVertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		�u�����h���[�h�iBLEND_MODE�j			�F	�f�t�H���g�iALPHA�j
		// @param		���[�v���[�h�iLOOP_MODE�j				�F	�f�t�H���g�iDEFAULT�j
		*/
		void Initialize(
			float exisTime = FOREVER_EXIST, 
			DirectX::VertexPositionColorTexture vertexDataStart = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE)),
			DirectX::VertexPositionColorTexture vertexDataEnd = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE)),
			Asset3D::BLEND_MODE blendMode = Asset3D::BLEND_MODE::ALPHA, 
			LOOP_MODE loopMode = LOOP_MODE::DEFAULT
		);

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update();

		/*
		// @method		Reset
		// @content		���Z�b�g
		*/
		void Reset();

		/* �A�N�Z�b�T */

		inline const DirectX::VertexPositionColorTexture& GetVertexNow() const	{ return vertexNow_; }
		inline Asset3D::BLEND_MODE GetBlendMode() const							{ return blendMode_; }
		inline bool IsExist() const												{ return isExist_; }

	public:
		// ����I�y���[�^
		Particle& operator=(const Particle& particle)
		{
			vertexStart_ = particle.vertexStart_;
			vertexEnd_   = particle.vertexEnd_;
			vertexNow_   = particle.vertexNow_;
			exisTime_    = particle.exisTime_;
			nowFrame_    = particle.nowFrame_;
			blendMode_   = particle.blendMode_;
			loopMode_    = particle.loopMode_;
			isExist_     = particle.isExist_;

			return (*this);
		}
	};
}