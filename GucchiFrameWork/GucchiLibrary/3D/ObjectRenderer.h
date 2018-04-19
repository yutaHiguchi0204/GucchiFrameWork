/* =====================================================================
//! @param		�uObjectRenderer�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"
#include <string>
#include "Object.h"

namespace GucchiLibrary
{
	/*
	// @class		ObjectRenderer �N���X�iSingleton�j
	// @content		�I�u�W�F�N�g�Ǘ��p
	// @use			RegisterObject�֐��ɂ���ēo�^���ꂽ�I�u�W�F�N�g��`�悷��
	// @use			�V�[���J�ڎ��Ȃǂ�Reset�֐����ĂԂ��Ƃœo�^�����I�u�W�F�N�g���������
	*/
	class ObjectRenderer : public SingletonDirector<ObjectRenderer>
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix = DirectX::SimpleMath::Matrix;

	private:
		std::list<Object*> objectList_;

	private:
		friend class SingletonDirector<ObjectRenderer>;

		ObjectRenderer() = default;

	public:
		/*
		// @method		RegisterObject
		// @content		�I�u�W�F�N�g�̓o�^
		// @param		�o�^����I�u�W�F�N�g�iObject*�j
		*/
		void RegisterObject(Object* object);

		/*
		// @method		SetActive
		// @content		�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ̕ύX
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetActive(Object* object, bool active);

		/*
		// @method		Update
		// @content		�A�N�e�B�u��Ԃ̃I�u�W�F�N�g���X�V
		*/
		void Update();

		/*
		// @method		Draw
		// @content		�A�N�e�B�u��Ԃ̃I�u�W�F�N�g��`��
		*/
		void Draw();

		/*
		// @method		DrawObject
		// @content		�I�u�W�F�N�g�̕`��
		// @param		�I�u�W�F�N�g�iObject*�j
		*/
		void DrawObject(Object* object);

		/*
		// @method		GetParentObjectPos
		// @content		�e�̈ʒu��H��
		// @param		�e�I�u�W�F�N�g�iObject*�j
		// @return		�ŏI�ʒu�iMatrix�j
		*/
		Matrix GetParentObjectMatrix(Object* object);

		/*
		// @method		Reset
		// @content		�o�^���ꂽ�I�u�W�F�N�g�̃��X�g�����Z�b�g
		*/
		void Reset();

		/*
		// @method		DisableLighting
		// @content		���f���̃��C�e�B���O�𖳌��ɂ���
		// @param		���f���iModel*�j
		*/
		void DisableLighting(DirectX::Model* model);
	};

	/*
	// @class		ObjectFactory �N���X�iSingleton�j
	// @content		�I�u�W�F�N�g�����p
	// @use			CreateObjectFromFile�֐����ĂԂ��ƂŃI�u�W�F�N�g�𐶐�����
	*/
	class ObjectFactory : public SingletonDirector<ObjectFactory>
	{
	private:
		Camera* camera_;			// ���������I�u�W�F�N�g�ɓn���J����

	private:
		friend class SingletonDirector<ObjectFactory>;

		ObjectFactory() = default;

	public:
		/*
		// @method		CreateObjectFromFile
		// @content		�w�肵��cmo�t�@�C������I�u�W�F�N�g�𐶐�����
		// @param		���f���t�@�C�����i�g���q�������j�iwstring�j
		// @return		�I�u�W�F�N�g�iunique_ptr<Object>�j
		*/
		std::unique_ptr<Object> CreateObjectFromFile(const std::wstring& fileName);

		/* �A�N�Z�b�T */

		void SetCamera(Camera* camera) { camera_ = camera; }
	};
}