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
	// �N���X�̒�`�i�X�v���C�g�Ǘ��j
	class SpriteRenderer
	{
	private:
		std::list<Sprite> spriteList_;

	public:
		SpriteRenderer() {};
		virtual ~SpriteRenderer() {};

		void RegisterSprite(Sprite* sprite, int order = -1);		// �X�v���C�g�o�^
		void SetActive(Sprite* sprite, bool active);				// �A�N�e�B�u��Ԃ̕ύX
		void SetOrder(Sprite* sprite, int order);					// �\�����̕ύX

		void Draw();												// �A�N�e�B�u��Ԃ̃X�v���C�g��`��
	};

	// �N���X�̒�`�i�X�v���C�g�̐����j
	class SpriteFactory : public SingletonDirector<SpriteFactory>
	{
	private:
		friend class SingletonDirector<SpriteFactory>;

		SpriteFactory() {};

	public:
		std::unique_ptr<Sprite> CreateSpriteFromFile(const std::wstring fileName, const DirectX::SimpleMath::Vector2& size);
	};
}