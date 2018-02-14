/* =====================================================================
//! @param		�uPrimitive�v�w�b�_
//! @create		��� �T��
//! @date		17/12/23
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/Element.h"
#include <GeometricPrimitive.h>
#include <map>
#include <string>
#include <vector>
#include <VertexTypes.h>

namespace GucchiLibrary
{
	/*
	// @class		Primitive �N���X
	// @content		�v���~�e�B�u
	*/
	class Primitive : public Element
	{
	public:
		/*
		// @content		�v���~�e�B�u�^�C�v
		// @mode		POINT		�F	�_
		// @mode		POINT3D		�F	�_
		// @mode		LINE		�F	��
		// @mode		SEGMENT		�F	����
		// @mode		TRIANGLE	�F	�O�p
		// @mode		RECTANGLE	�F�@�����`
		// @mode		BOX			�F	������
		// @mode		CIRCLE		�F�@�~
		// @mode		SPHERE		�F	��
		*/
		enum class PRIMITIVE_TYPE
		{
			POINT,
			POINT3D,
			LINE,
			SEGMENT,
			TRIANGLE,
			RECTANGLE,
			BOX,
			CIRCLE,
			SPHERE
		};

	protected:
		PRIMITIVE_TYPE											type_;			// �v���~�e�B�u�^�C�v

	public:
		Vector3													pos_;			// ���W
		bool													isFill_;		// �h��Ԃ����邩�ǂ���

	public:
		// �R���X�g���N�^
		Primitive();

		// �f�X�g���N�^
		virtual ~Primitive() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update() override { Element::Update(); }

		/* �A�N�Z�b�T */

		void SetType(PRIMITIVE_TYPE type)		{ type_ = type; }

		inline PRIMITIVE_TYPE GetType()	const	{ return type_; }
	};

	/*
	// @class		Primitive2D �N���X
	// @content		�Q�c�v���~�e�B�u
	*/
	class Primitive2D : public Primitive
	{
	public:
		std::map<std::string, DirectX::VertexPositionColor>		vertices_;		// ���_�f�[�^

	public:
		// �R���X�g���N�^
		Primitive2D();

		// �f�X�g���N�^
		virtual ~Primitive2D() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update() override { Primitive::Update(); }

		/*
		// @method		GetKeys
		// @content		�L�[�̎擾
		// @return		�S�ẴL�[�ivector<string>�j
		*/
		std::vector<std::string> GetKeys() const;
	};

	/*
	// @class		Primitive3D �N���X
	// @content		�v���~�e�B�u
	*/
	class Primitive3D : public Primitive
	{
	public:
		std::unique_ptr<DirectX::GeometricPrimitive>	geometry_;		// �W�I���g��
		Color											color_;			// �F���

	public:
		// �R���X�g���N�^
		Primitive3D();

		// �f�X�g���N�^
		virtual ~Primitive3D() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update() override { Primitive::Update(); }
	};

	/*
	// @class		Circle �N���X
	// @content		�~�v���~�e�B�u
	*/
	class Circle : public Primitive2D
	{
	public:
		float	radius_;		// ���a
		int		div_;			// ������
	};
}