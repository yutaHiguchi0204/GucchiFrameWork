/* =====================================================================
//! @param		�uEmitter�v�w�b�_
//! @create		��� �T��
//! @date		17/12/27
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Particle.h"
#include <PrimitiveBatch.h>
#include <string>
#include <vector>
#include "../2D/TextureCache.h"
#include "../3D/Object.h"

namespace GucchiLibrary
{
	/*
	// @class		Emitter �N���X
	// @content		�p�[�e�B�N���G�~�b�^�[
	*/
	class Emitter : public Element
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Vector4 = DirectX::SimpleMath::Vector4;

	public:
		static const int FOREVER_EXIST;			// ����

	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>	primitiveBatch_;	// �v���~�e�B�u�o�b�`

		Texture*																		texture_;			// �p�[�e�B�N���p�e�N�X�`��
		std::vector<std::unique_ptr<Particle>>											particle_;			// �p�[�e�B�N��

		Vector3																			pos_;				// �G�~�b�^�[�̍��W
		float																			exisTime_;			// �G�~�b�^�[�̎���
		float																			nowFrame_;			// �o�����Ă���̌o�߃t���[��
		bool																			isExist_;			// ���݂��Ă��邩�ǂ���

		Object*																			parentObject_;		// �e�I�u�W�F�N�g

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		�G�~�b�^�[�̍��W�iVector3�j	�F	�f�t�H���g�iVector3::Zero�j
		// @param		�����ifloat�j				�F	�f�t�H���g�iFOREVER_EXIST�j
		*/
		Emitter(const Vector3& pos = Vector3::Zero, float exisTime = FOREVER_EXIST);

		// �f�X�g���N�^
		virtual ~Emitter() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update();

		/*
		// @method		Draw
		// @content		�`�揈��
		*/
		void Draw();

		/*
		// @method		Entry
		// @content		�p�[�e�B�N������
		// @param		�����ifloat�j							�F	�f�t�H���g�iFOREVER_EXIST�j
		// @param		�n�_���iVertexPositionColorTexture�j	�F	�f�t�H���g�iVertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		�I�_���iVertexPositionColorTexture�j	�F	�f�t�H���g�iVertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		�u�����h���[�h�iBLEND_MODE�j			�F	�f�t�H���g�iALPHA�j
		// @param		���[�v���[�h�iLOOP_MODE�j				�F	�f�t�H���g�iDEFAULT�j
		*/
		void Entry(
			float exisTime = FOREVER_EXIST,
			DirectX::VertexPositionColorTexture vertexDataStart = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(Particle::DEFAULT_SCALE, Particle::DEFAULT_ROTATE)),
			DirectX::VertexPositionColorTexture vertexDataEnd = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(Particle::DEFAULT_SCALE, Particle::DEFAULT_ROTATE)),
			Asset3D::BLEND_MODE blendMode = Asset3D::BLEND_MODE::ALPHA,
			Particle::LOOP_MODE loopMode = Particle::LOOP_MODE::DEFAULT
		);

		/*
		// @method		LoadTexture
		// @content		�e�N�X�`���̓ǂݍ���
		// @param		�e�N�X�`���t�@�C�����iwstring�j
		*/
		void LoadTexture(const std::wstring& fileName);

		/* �A�N�Z�b�T */

		void SetPos(const Vector3& pos)			{ pos_ = pos; }
		void SetParent(Object* parent)			{ parentObject_ = parent; }

		inline const Vector3& GetPos() const	{ return pos_; }
		inline bool IsExist() const				{ return isExist_; }
	};
}