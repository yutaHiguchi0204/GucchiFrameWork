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
#include "TextureCache.h"

namespace GucchiLibrary
{
	// �N���X�̒�`
	class Sprite
	{
	private:
		Texture*						texture_;			// �e�N�X�`���n���h��
		DirectX::SimpleMath::Vector2	pos_;				// �ʒu
		DirectX::SimpleMath::Vector2	size_;				// �T�C�Y
		float							scale_;				// �g�嗦
		float							angle_;				// ��]�p
		bool							isActive_;			// �A�N�e�B�u���

	public:
		Sprite();
		virtual ~Sprite() {};

		void Initialize(const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector2& size, float scale = 1.0f, float angle = 0.0f);

		void SetTexture(Texture* texture)							{ texture_ = texture; }
		void SetPos(const DirectX::SimpleMath::Vector2& pos)		{ pos_ = pos; }
		void SetSize(const DirectX::SimpleMath::Vector2& size)		{ size_ = size; }
		void SetScale(float scale)									{ scale_ = scale; }
		void SetAngle(float angle)									{ angle_ = angle; }
		void SetActive(bool active)									{ isActive_ = active; }

		inline Texture* GetTexture() const							{ return texture_; }
		inline DirectX::SimpleMath::Vector2 GetPos() const			{ return pos_; }
		inline DirectX::SimpleMath::Vector2 GetSize() const			{ return size_; }
		inline float GetScale() const								{ return scale_; }
		inline float GetAngle() const								{ return angle_; }
		inline bool GetActive() const								{ return isActive_; }
	};
}