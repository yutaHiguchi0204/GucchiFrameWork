/* =====================================================================
//! @param		�uSprite�v�w�b�_
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <vector>
#include "TextureCache.h"
#include "../Common/Element.h"
#include "../Utility/Interpolater.h"

namespace GucchiLibrary
{
	/*
	// @class		Sprite �N���X
	// @content		2D�p�X�v���C�g���\�[�X
	// @use			SpriteFactory���g����������
	// @use			�e�N�X�`����TextureCache�ɂ���ĊǗ������iSpriteFactory���j
	// @use			SpriteRenderer�ɓo�^���邱�Ƃŕ`��\�i���̎��I�[�_�[�l��ς��邱�Ƃŕ`�揇��ύX�\�j
	*/
	class Sprite : public Element
	{
	private:
		Texture*									texture_;				// �e�N�X�`���n���h��
		Vector2										pos_;					// �ʒu
		Vector2										size_;					// �T�C�Y
		RECT*										textureRect_;			// �摜��`
		Vector2										anchor_;				// �A���J�[�|�C���g
		float										scale_;					// �g�嗦
		float										angle_;					// ��]�p
		bool										isActive_;				// �A�N�e�B�u���

		Sprite*										parentSprite_;			// �e�X�v���C�g
		std::vector<Sprite*>						childSprite_;			// �q�X�v���C�g

		bool										isAction_;				// �A�N�V���������ǂ���

		std::unique_ptr<InterpolateDirector>		interpolateDirector_;	// ��ԃX�e�[�g

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		�X�v���C�g�T�C�Y�iVector2�j
		// @param		�������W�iVector2�j�@�F�@�f�t�H���g�iVector2::Zero�j
		// @param		��`�擾�iRECT*�j�@�F�@�f�t�H���g�inullptr�j
		// @param		�X�P�[���ifloat�j�@�F�@�f�t�H���g�i1.0f�j
		// @param		��]�p�ifloat�j�@�F�@�f�t�H���g�i0.0f�j
		*/
		Sprite(const Vector2& size, const Vector2& pos = Vector2::Zero, RECT* rect = nullptr, float scale = 1.0f, float angle = 0.0f);

		// �R�s�[�R���X�g���N�^
		Sprite(const Sprite& sprite);

		// �f�X�g���N�^
		virtual ~Sprite() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update() override;

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

		void SetTexture(Texture* texture)								{ texture_ = texture; }
		void SetPos(const Vector2& pos)									{ pos_ = pos; }
		void SetSize(const Vector2& size)								{ size_ = size; }
		void SetRect(RECT* rect)										{ textureRect_ = rect; }
		void SetAnchor(const Vector2& anchor)							{ anchor_ = anchor; }
		void SetScale(float scale)										{ scale_ = scale; }
		void SetAngle(float angle)										{ angle_ = angle; }
		void SetActive(bool active)										{ isActive_ = active; }
		void SetIsAction(bool isAction)									{ isAction_ = isAction; }

		inline Texture* GetTexture() const								{ return texture_; }
		inline const Vector2& GetPos() const							{ return pos_; }
		inline const Vector2& GetSize() const							{ return size_; }
		inline RECT* GetRect() const									{ return textureRect_; }
		inline const Vector2& GetAnchor() const							{ return anchor_; }
		inline float GetScale() const									{ return scale_; }
		inline float GetAngle() const									{ return angle_; }
		inline bool GetActive() const									{ return isActive_; }
		inline Sprite* GetParent() const								{ return parentSprite_; }
		inline std::vector<Sprite*> GetChildren() const					{ return childSprite_; }
		inline bool IsAction() const									{ return isAction_; }
		inline InterpolateDirector* GetInterpolateDirector() const		{ return interpolateDirector_.get(); }

	public:
		// ����I�y���[�^
		Sprite& operator=(const Sprite& sprite)
		{
			texture_      = sprite.texture_;
			pos_          = sprite.pos_;
			size_         = sprite.size_;
			textureRect_  = sprite.textureRect_;
			anchor_       = sprite.anchor_;
			scale_        = sprite.scale_;
			angle_        = sprite.angle_;
			isActive_     = sprite.isActive_;
			parentSprite_ = sprite.parentSprite_;
			childSprite_  = sprite.childSprite_;
			isAction_     = sprite.isAction_;

			return (*this);
		}

		// ��r�p�I�y���[�^
		bool operator==(const Sprite& sprite) const
		{
			return 
				texture_		== sprite.texture_		&& 
				pos_			== sprite.pos_			&& 
				size_			== sprite.size_			&& 
				textureRect_	== sprite.textureRect_	&& 
				anchor_			== sprite.anchor_		&& 
				scale_			== sprite.scale_		&& 
				angle_			== sprite.angle_		&& 
				isActive_		== sprite.isActive_		&& 
				parentSprite_	== sprite.parentSprite_	&& 
				childSprite_	== sprite.childSprite_	&& 
				isAction_		== sprite.isAction_;
		}
	};
}