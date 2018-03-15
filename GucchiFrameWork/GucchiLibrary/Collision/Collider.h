/* =====================================================================
//! @param		�uCollider�v�w�b�_
//! @create		��� �T��
//! @date		18/02/07
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <memory>
#include "../Common/Component.h"
#include "../Primitive/PrimitiveRenderer.h"

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

	protected:
		std::unique_ptr<Primitive>	primitive_;				// �����蔻��p�v���~�e�B�u

	public:
		// �R���X�g���N�^
		Collider() = default;

		// �f�X�g���N�^
		virtual ~Collider() = default;

		/*
		// @method		Initialize
		// @content		����������
		// @param		�v�f�iElement*�j
		*/
		virtual void Initialize(Element* element) override = 0;

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		virtual void Update(Element* element) override = 0;

		/*
		// @method		SetPrimitiveActive�istatic�j
		// @content		�����蔻��̃A�N�e�B�u��Ԃ̕ύX
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetPrimitiveActive(bool active);
	};

	/*
	// @class		SegmentCollider �N���X
	// @content		����
	*/
	class SegmentCollider : public Collider
	{
	public:
		Vector3 start_;			// �n�_
		Vector3 end_;			// �I�_

	public:
		/*
		// @method		Initialize
		// @content		����������
		// @param		�v�f�iElement*�j
		*/
		void Initialize(Element* element) override;

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		SphereCollider �N���X
	// @content		��
	*/
	class SphereCollider : public Collider
	{
	public:
		Vector3 center_;		// ���S���W
		float radius_;			// ���a

	public:
		// �R���X�g���N�^
		SphereCollider() : radius_(1.0f) {}

		/*
		// @method		Initialize
		// @content		����������
		// @param		�v�f�iElement*�j
		*/
		void Initialize(Element* element) override;

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	///*
	//// @class		CapsuleCollider �N���X
	//// @content		�J�v�Z��
	//*/
	//class CapsuleCollider : public Collider
	//{
	//public:
	//	SegmentCollider segment_;		// �c��
	//	float radius_;			// ���a

	//public:
	//	// �R���X�g���N�^
	//	CapsuleCollider() : radius_(1.0f)
	//	{
	//		segment_.start_ = Vector3(0.f, 0.f, 0.f);
	//		segment_.end_ = Vector3(0.f, 1.f, 0.f);
	//	}

	//	/*
	//	// @method		Initialize
	//	// @content		����������
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		�X�V����
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Update(Element* element) override;
	//};

	///*
	//// @class		PlaneCollider �N���X
	//// @content		����
	//*/
	//class PlaneCollider : public Collider
	//{
	//public:
	//	Vector3 normal_;		// �@���x�N�g��
	//	float distance_;		// ���_����̋���

	//public:
	//	// �R���X�g���N�^
	//	PlaneCollider() : distance_(0.f) {}

	//	/*
	//	// @method		Initialize
	//	// @content		����������
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		�X�V����
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Update(Element* element) override;
	//};

	///*
	//// @class		TriangleCollider �N���X
	//// @content		�O�p�`�i�����v���A�@���t���j
	//*/
	//class TriangleCollider : public Collider
	//{
	//public:
	//	Vector3 p0_;			// �P�ڂ̒��_
	//	Vector3 p1_;			// �Q�ڂ̒��_
	//	Vector3 p2_;			// �R�ڂ̒��_
	//	Vector3 normal_;		// �@���x�N�g��

	//public:
	//	/*
	//	// @method		Initialize
	//	// @content		����������
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		�X�V����
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Update(Element* element) override;
	//};

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
		// @method		Initialize
		// @content		����������
		// @param		�v�f�iElement*�j
		*/
		void Initialize(Element* element) override;

		/*
		// @method		Update
		// @content		�X�V����
		// @param		�v�f�iElement*�j
		*/
		void Update(Element* element) override;
	};

	///*
	//// @class		OBB �N���X
	//// @content		�L�����E�{�b�N�X
	//*/
	//class OBB : public Collider
	//{
	//public:
	//	Vector3 center_;		// ���S���W
	//	Vector3 axis_[3];		// ���[�J�����W
	//	Vector3 size_;			// �T�C�Y

	//public:
	//	/*
	//	// @method		Initialize
	//	// @content		����������
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		�X�V����
	//	// @param		�v�f�iElement*�j
	//	*/
	//	void Update(Element* element) override;
	//};
}
