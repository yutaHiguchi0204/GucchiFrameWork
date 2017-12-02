/* =====================================================================
//! @param		�uAction�v�w�b�_�i�ړ��֌W���C�u�����j
//! @create		��� �T��
//! @date		17/12/02
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "../2D/Sprite.h"
#include "../3D/Object.h"

namespace GucchiLibrary
{
	/*
	// @class		Action �N���X
	// @content		�ړ��֌W�̋��ʃN���X
	*/
	class Action
	{
	protected:
		DirectX::SimpleMath::Vector2 startPosV2;			// �n�_�i�X�v���C�g�p�j
		DirectX::SimpleMath::Vector3 startPosV3;			// �n�_�i�I�u�W�F�N�g�p�j

	public:
		Action() {}
		virtual ~Action() {}
	};

	/*
	// @class		MoveTo �N���X
	// @content		���`�ړ��i��Έړ��j
	*/
	class MoveTo : public Action
	{
	public:
		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�I�_�iVector2�j
		*/
		static void Action(Sprite* sprite, float time, const DirectX::SimpleMath::Vector2& pos);

		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�I�_�iVector3�j
		*/
		static void Action(Object* object, float time, const DirectX::SimpleMath::Vector3& pos);
	};

	/*
	// @class		MoveBy �N���X
	// @content		���`�ړ��i���Έړ��j
	*/
	class MoveBy : public Action
	{
	public:
		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�I�_�iVector2�j
		*/
		static void Action(Sprite* sprite, float time, const DirectX::SimpleMath::Vector2& distance);
		
		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�I�_�iVector3�j
		*/
		static void Action(Object* object, float time, const DirectX::SimpleMath::Vector3& distance);
	};
}