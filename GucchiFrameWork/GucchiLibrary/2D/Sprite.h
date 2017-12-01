/* =====================================================================
//! @param		�uSprite�v�w�b�_
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <string>
#include <vector>
#include "TextureCache.h"

namespace GucchiLibrary
{
	/*
	// @class		Sprite �N���X
	// @content		2D�p�X�v���C�g���\�[�X
	// @use			SpriteFactory���g����������
	// @use			�e�N�X�`����TextureCache�ɂ���ĊǗ������iSpriteFactory���j
	// @use			SpriteRenderer�ɓo�^���邱�Ƃŕ`��\�i���̎��I�[�_�[�l��ς��邱�Ƃŕ`�揇��ύX�\�j
	*/
	class Sprite
	{
	private:
		Texture*						texture_;			// �e�N�X�`���n���h��
		DirectX::SimpleMath::Vector2	pos_;				// �ʒu
		DirectX::SimpleMath::Vector2	size_;				// �T�C�Y
		RECT*							textureRect_;		// �摜��`
		float							scale_;				// �g�嗦
		float							angle_;				// ��]�p
		bool							isActive_;			// �A�N�e�B�u���

		Sprite*							parentSprite_;		// �e�X�v���C�g
		std::vector<Sprite*>			childSprite_;		// �q�X�v���C�g

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		�X�v���C�g�T�C�Y�iVector2�j
		// @param		�������W�iVector2�j�@�F�@�f�t�H���g�iVector2::Zero�j
		// @param		��`�擾�iRECT*�j�@�F�@�f�t�H���g�inullptr�j
		// @param		�X�P�[���ifloat�j�@�F�@�f�t�H���g�i1.0f�j
		// @param		��]�p�ifloat�j�@�F�@�f�t�H���g�i0.0f�j
		*/
		Sprite(const DirectX::SimpleMath::Vector2& size, const DirectX::SimpleMath::Vector2& pos = DirectX::SimpleMath::Vector2::Zero, RECT* rect = nullptr, float scale = 1.0f, float angle = 0.0f);

		// �R�s�[�R���X�g���N�^
		Sprite(const Sprite& sprite);

		// �f�X�g���N�^
		virtual ~Sprite() {}

		/*
		// @method		SetParent
		// @content		�e�q�֌W�\�z�i�e�ݒ�j
		// @param		�e�X�v���C�g�iSprite*�j
		*/
		void SetParent(Sprite* sprite);

		/*
		// @method		AddChild
		// @content		�e�q�֌W�\�z�i�q�ݒ�j
		// @param		�q�X�v���C�g�iSprite*�j
		*/
		void AddChild(Sprite* sprite);

		/* �A�N�Z�b�T */

		void SetTexture(Texture* texture)							{ texture_ = texture; }
		void SetPos(const DirectX::SimpleMath::Vector2& pos)		{ pos_ = pos; }
		void SetSize(const DirectX::SimpleMath::Vector2& size)		{ size_ = size; }
		void SetRect(RECT* rect)									{ textureRect_ = rect; }
		void SetScale(float scale)									{ scale_ = scale; }
		void SetAngle(float angle)									{ angle_ = angle; }
		void SetActive(bool active)									{ isActive_ = active; }

		inline Texture* GetTexture() const							{ return texture_; }
		inline DirectX::SimpleMath::Vector2 GetPos() const			{ return pos_; }
		inline DirectX::SimpleMath::Vector2 GetSize() const			{ return size_; }
		inline RECT* GetRect() const								{ return textureRect_; }
		inline float GetScale() const								{ return scale_; }
		inline float GetAngle() const								{ return angle_; }
		inline bool GetActive() const								{ return isActive_; }
		inline Sprite* GetParent() const							{ return parentSprite_; }
		inline std::vector<Sprite*> GetChildren() const				{ return childSprite_; }

	public:
		// ����I�y���[�^
		Sprite& operator=(const Sprite& sprite)
		{
			texture_      = sprite.texture_;
			pos_          = sprite.pos_;
			size_         = sprite.size_;
			textureRect_  = sprite.textureRect_;
			scale_        = sprite.scale_;
			angle_        = sprite.angle_;
			isActive_     = sprite.isActive_;
			parentSprite_ = sprite.parentSprite_;
			childSprite_  = sprite.childSprite_;

			return (*this);
		}

		// ��r�p�I�y���[�^
		bool operator==(const Sprite& sprite) const
		{
			if (texture_		== sprite.GetTexture()		&&
				pos_			== sprite.GetPos()			&&
				size_			== sprite.GetSize()			&&
				textureRect_	== sprite.GetRect()			&&
				scale_			== sprite.GetScale()		&&
				angle_			== sprite.GetAngle()		&&
				isActive_		== sprite.GetActive()		&&
				parentSprite_	== sprite.GetParent()		&&
				childSprite_	== sprite.GetChildren()
				)
			{
				return true;
			}

			return false;
		}
	};
}