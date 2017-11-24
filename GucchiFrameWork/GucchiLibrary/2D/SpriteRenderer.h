/* =====================================================================
//! @param		�uSpriteRenderer�v�w�b�_
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"
#include <list>
#include "Sprite.h"

namespace GucchiLibrary
{
	/*
	// @class		SpriteRenderer �N���X�iSingleton�j
	// @content		�X�v���C�g�Ǘ��p
	// @use			RegisterSprite�֐��ɂ���ēo�^���ꂽ�X�v���C�g��`�悷��
	// @use			�V�[���J�ڎ��Ȃǂ�Reset�֐����ĂԂ��Ƃœo�^�����X�v���C�g���������
	*/
	class SpriteRenderer : public SingletonDirector<SpriteRenderer>
	{
	private:
		std::list<Sprite> spriteList_;

	private:
		friend class SingletonDirector<SpriteRenderer>;

		SpriteRenderer() {};

	public:
		/*
		// @method		RegisterSprite
		// @content		�X�v���C�g�̓o�^
		// @param		�o�^����X�v���C�g�iSprite*�j
		// @param		�I�[�_�[�l�iint�j�@�F�@�f�t�H���g�i-1�j
		*/
		void RegisterSprite(Sprite* sprite, int order = -1);

		/*
		// @method		SetActive
		// @content		�X�v���C�g�̃A�N�e�B�u��Ԃ̕ύX
		// @param		�X�v���C�g�iSprite*�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetActive(Sprite* sprite, bool active);

		/*
		// @method		SetOrder
		// @content		�I�[�_�[�l�̕ύX
		// @param		�X�v���C�g�iSprite*�j
		// @param		�I�[�_�[�l�iint�j
		*/
		void SetOrder(Sprite* sprite, int order);

		/*
		// @method		Draw
		// @content		�A�N�e�B�u��Ԃ̃X�v���C�g��`��
		*/
		void Draw();

		/*
		// @method		Reset
		// @content		�o�^���ꂽ�X�v���C�g�̃��X�g�����Z�b�g
		*/
		void Reset();
	};

	/*
	// @class		SpriteFactory �N���X�iSingleton�j
	// @content		�X�v���C�g�����p
	// @use			CreateSpriteFromFile�֐����ĂԂ��ƂŃX�v���C�g�𐶐�����
	*/
	class SpriteFactory : public SingletonDirector<SpriteFactory>
	{
	private:
		friend class SingletonDirector<SpriteFactory>;

		SpriteFactory() {};

	public:
		/*
		// @method		CreateSpriteFromFile
		// @content		�w�肵���e�N�X�`������X�v���C�g�𐶐�����
		// @param		�e�N�X�`�����i�g���q�������j�iwstring�j
		// @param		�e�N�X�`���T�C�Y�iVector2�j
		*/
		std::unique_ptr<Sprite> CreateSpriteFromFile(const std::wstring fileName, const DirectX::SimpleMath::Vector2& size);
	};
}