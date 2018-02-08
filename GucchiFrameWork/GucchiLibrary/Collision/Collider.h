/* =====================================================================
//! @param		�uCollider�v�w�b�_
//! @create		��� �T��
//! @date		18/02/07
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "../Common/Component.h"

namespace GucchiLibrary
{
	/*
	// @class		Collider �N���X
	// @content		�����蔻��N���X
	*/
	class Collider : public Component
	{
	protected:
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		// �R���X�g���N�^
		Collider() = default;

		// �f�X�g���N�^
		virtual ~Collider() = default;

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		virtual void Update(Element* element) override = 0;
	};

	/*
	// @class		Segment �N���X
	// @content		����
	*/
	class Segment : public Collider
	{
	public:
		Vector3 start_;			// �n�_
		Vector3 end_;			// �I�_

	public:
		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Sphere �N���X
	// @content		��
	*/
	class Sphere : public Collider
	{
	public:
		Vector3 center_;		// ���S���W
		float radius_;			// ���a

	public:
		// �R���X�g���N�^
		Sphere() : radius_(1.0f) {}

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Capsule �N���X
	// @content		�J�v�Z��
	*/
	class Capsule : public Collider
	{
	public:
		Segment segment_;		// �c��
		float radius_;			// ���a

	public:
		// �R���X�g���N�^
		Capsule() : radius_(1.0f)
		{
			segment_.start_ = Vector3(0.f, 0.f, 0.f);
			segment_.end_ = Vector3(0.f, 1.f, 0.f);
		}

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Plane �N���X
	// @content		����
	*/
	class Plane : public Collider
	{
	public:
		Vector3 normal_;		// �@���x�N�g��
		float distance_;		// ���_����̋���

	public:
		// �R���X�g���N�^
		Plane() : distance_(0.f) {}

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Triangle �N���X
	// @content		�O�p�`�i�����v���A�@���t���j
	*/
	class Triangle : public Collider
	{
	public:
		Vector3 p0_;			// �P�ڂ̒��_
		Vector3 p1_;			// �Q�ڂ̒��_
		Vector3 p2_;			// �R�ڂ̒��_
		Vector3 normal_;		// �@���x�N�g��

	public:
		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		AABB �N���X
	// @content		�����s���E�{�b�N�X
	*/
	class AABB : public Collider
	{
	public:
		Vector3 min_;			// �ŏ����W
		Vector3 max_;			// �ő���W

	public:
		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		OBB �N���X
	// @content		�L�����E�{�b�N�X
	*/
	class OBB : public Collider
	{
	public:
		Vector3 center_;		// ���S���W
		Vector3 axis_[3];		// ���[�J�����W
		Vector3 size_;			// �T�C�Y

	public:
		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};
}
