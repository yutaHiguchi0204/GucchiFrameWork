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
	class ActionManager
	{
	public:
		// �R���X�g���N�^
		ActionManager() {}

		// �f�X�g���N�^
		virtual ~ActionManager() {}
	};

	/*
	// @class		MoveTo �N���X
	// @content		���`�ړ��i��Έړ��j
	*/
	class MoveTo : public ActionManager
	{
	public:
		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�I�_�iVector2�j
		// @return		��Ԓl�iVector2�j
		*/
		static DirectX::SimpleMath::Vector2 Action(Sprite* sprite, float time, const DirectX::SimpleMath::Vector2& pos);

		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�I�_�iVector3�j
		// @return		��Ԓl�iVector3�j
		*/
		static DirectX::SimpleMath::Vector3 Action(Object* object, float time, const DirectX::SimpleMath::Vector3& trans);
	};

	/*
	// @class		MoveBy �N���X
	// @content		���`�ړ��i���Έړ��j
	*/
	class MoveBy : public ActionManager
	{
	public:
		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�ړ������iVector2�j
		// @return		��Ԓl�iVector2�j
		*/
		static DirectX::SimpleMath::Vector2 Action(Sprite* sprite, float time, const DirectX::SimpleMath::Vector2& distance);
		
		/*
		// @method		Action
		// @content		�ړ��A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		�ړ��ɂ����鎞�ԁifloat�j
		// @param		�ړ������iVector3�j
		// @return		��Ԓl�iVector3�j
		*/
		static DirectX::SimpleMath::Vector3 Action(Object* object, float time, const DirectX::SimpleMath::Vector3& distance);
	};

	/*
	// @class		ScaleTo �N���X
	// @content		�X�P�[���ω��i��Εω��j
	*/
	class ScaleTo : public ActionManager
	{
	public:
		/*
		// @method		Action
		// @content		�X�P�[���ω��A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		�ω��ɂ����鎞�ԁifloat�j
		// @param		�X�P�[���l�ifloat�j
		// @return		��Ԓl�ifloat�j
		*/
		static float Action(Sprite* sprite, float time, float scale);

		/*
		// @method		Action
		// @content		�X�P�[���ω��A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		�ω��ɂ����鎞�ԁifloat�j
		// @param		�X�P�[���l�iVector3�j
		// @return		��Ԓl�iVector3�j
		*/
		static DirectX::SimpleMath::Vector3 Action(Object* object, float time, const DirectX::SimpleMath::Vector3& scale);
	};

	/*
	// @class		ScaleBy �N���X
	// @content		�X�P�[���ω��i���Έړ��j
	*/
	class ScaleBy : public ActionManager
	{
	public:
		/*
		// @method		Action
		// @content		�X�P�[���ω��A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		�ω��ɂ����鎞�ԁifloat�j
		// @param		���݂̃X�P�[������̔{���ifloat�j
		// @return		��Ԓl�ifloat�j
		*/
		static float Action(Sprite* sprite, float time, const float scale);

		/*
		// @method		Action
		// @content		�X�P�[���ω��A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		�ω��ɂ����鎞�ԁifloat�j
		// @param		���݂̃X�P�[������̔{���iVector3�j
		// @return		��Ԓl�iVector3�j
		*/
		static DirectX::SimpleMath::Vector3 Action(Object* object, float time, const DirectX::SimpleMath::Vector3& scale);
	};

	/*
	// @class		RotateTo �N���X
	// @content		��]�^���i��Ή�]�j
	*/
	class RotateTo : public ActionManager
	{
	public:
		/*
		// @method		Action
		// @content		��]�A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		��]�ɂ����鎞�ԁifloat�j
		// @param		��]�p�ifloat�j
		// @return		��Ԓl�ifloat�j
		*/
		static float Action(Sprite* sprite, float time, float angle);

		/*
		// @method		Action
		// @content		��]�A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		��]�ɂ����鎞�ԁifloat�j
		// @param		��]�p�iVector3�j
		// @return		��Ԓl�iVector3�j
		*/
		static DirectX::SimpleMath::Vector3 Action(Object* object, float time, const DirectX::SimpleMath::Vector3& rot);
	};

	/*
	// @class		RotateBy �N���X
	// @content		��]�^���i���Ή�]�j
	*/
	class RotateBy : public ActionManager
	{
	public:
		/*
		// @method		Action
		// @content		��]�A�N�V����
		// @param		�X�v���C�g�iSprite*�j
		// @param		��]�ɂ����鎞�ԁifloat�j
		// @param		���݂̊p�x����̉�]�p�ifloat�j
		// @return		��Ԓl�ifloat�j
		*/
		static float Action(Sprite* sprite, float time, float angle);

		/*
		// @method		Action
		// @content		��]�A�N�V����
		// @param		�I�u�W�F�N�g�iObject*�j
		// @param		��]�ɂ����鎞�ԁifloat�j
		// @param		���݂̊p�x����̉�]�p�iVector3�j
		// @return		��Ԓl�iVector3�j
		*/
		static DirectX::SimpleMath::Vector3 Action(Object* object, float time, const DirectX::SimpleMath::Vector3& rot);
	};
}