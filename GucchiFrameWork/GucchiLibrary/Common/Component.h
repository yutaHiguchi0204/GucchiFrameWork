/* =====================================================================
//! @param		�uComponent�v�w�b�_
//! @create		��� �T��
//! @date		18/02/08
===================================================================== */
#pragma once

namespace GucchiLibrary
{
	class Element;

	/*
	// @class		Component �N���X
	// @content		�R���|�[�l���g�N���X
	*/
	class Component
	{
	public:
		// �R���X�g���N�^
		Component() = default;
		
		// �f�X�g���N�^
		virtual ~Component() = default;

		/*
		// @method		Initialize
		// @content		����������
		*/
		virtual void Initialize(Element* element) = 0;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		virtual void Update(Element* element) = 0;

		/*
		// @method		Finalize
		// @content		�I������
		*/
		virtual void Finalize() = 0;
	};
}