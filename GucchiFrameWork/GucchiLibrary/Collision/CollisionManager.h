/* =====================================================================
//! @param		�uCollisionManager�v�w�b�_
//! @create		��� �T��
//! @date		17/11/29
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		CollisionManager �N���X
	// @content		�����蔻��`�F�b�N�p
	*/
	class CollisionManager : public SingletonDirector<CollisionManager>
	{
	public:
		/*
		// @content		�����蔻����`�F�b�N�������
		// @mode		OWN		�F�@���g�̏ꏊ
		// @mode		LEFT	�F�@����
		// @mode		RIGHT	�F�@�E��
		// @mode		TOP		�F�@�㑤
		// @mode		BOTTOM	�F�@����
		*/
		enum class COLLISION
		{
			OWN,
			LEFT,
			RIGHT,
			TOP,
			BOTTOM
		};

	private:
		friend class SingletonDirector<CollisionManager>;

		CollisionManager() {}

	public:
		/*
		// @method		CheckCollisionMapTip
		// @content		�w�肵���ꏊ�̃}�b�v�`�b�v���`�F�b�N
		*/
		//bool CheckCollisionMapTip()
	};
}