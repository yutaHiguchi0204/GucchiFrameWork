/* =====================================================================
//! @param		�uObjectRenderer�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"
#include <CommonStates.h>
#include <Effects.h>
#include <list>
#include <PrimitiveBatch.h>
#include <string>
#include <VertexTypes.h>
#include <wrl/client.h>
#include "Object.h"

namespace GucchiLibrary
{
	// �N���X�̒�`�i�I�u�W�F�N�g�Ǘ��j
	class ObjectRenderer : public SingletonDirector<ObjectRenderer>
	{
	private:
		std::list<Object> objectList_;

		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> primitiveBatch_;

	private:
		friend class SingletonDirector<ObjectRenderer>;

		ObjectRenderer() {}

	public:
		void Initialize();										// ����������

		void RegisterObject(Object* object);					// �I�u�W�F�N�g�̓o�^
		void SetActive(Object* object, bool active);			// �A�N�e�B�u��Ԃ̕ύX

		void Draw();											// �A�N�e�B�u��Ԃ̃I�u�W�F�N�g��`��
		void DrawSubtractive();									// �A�N�e�B�u��Ԃ̃I�u�W�F�N�g�����Z�`��
		void Reset();											// ���X�g���Z�b�g

		void SetBlendState(Asset3D::BLEND_MODE mode);			// �u�����h�ݒ�
		void SetSubtractive(ID3D11BlendState* blendState);		// ���Z�`��ݒ�

		void DisableLighting(DirectX::Model* model);			// �I�u�W�F�N�g�̃��C�e�B���O�𖳌��ɂ���
	};

	// �N���X�̒�`�i�I�u�W�F�N�g�̐����j
	class ObjectFactory : public SingletonDirector<ObjectFactory>
	{
	private:
		Camera* camera_;			// ���������I�u�W�F�N�g�ɓn���J����

	private:
		friend class SingletonDirector<ObjectFactory>;

		ObjectFactory() {};

	public:
		std::unique_ptr<Object> CreateObjectFromFile(const std::wstring fileName);

		// �A�N�Z�b�T
		void SetCamera(Camera* camera) { camera_ = camera; }
	};
}