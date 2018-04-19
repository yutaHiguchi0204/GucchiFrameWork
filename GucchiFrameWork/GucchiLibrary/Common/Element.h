/* =====================================================================
//! @param		�uElement�v�w�b�_
//! @create		��� �T��
//! @date		18/02/08
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <list>
#include <memory>
#include <SimpleMath.h>
#include "Component.h"

namespace GucchiLibrary
{
	/*
	// @class		Element �N���X
	// @content		�v�f�̊��N���X
	*/
	class Element
	{
	protected:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Vector4 = DirectX::SimpleMath::Vector4;
		using Matrix = DirectX::SimpleMath::Matrix;
		using Quaternion = DirectX::SimpleMath::Quaternion;
		using Color = DirectX::SimpleMath::Color;

	protected:
		std::list<std::unique_ptr<Component>>	componentList_;			// �R���|�[�l���g���X�g
		bool									isActive_;				// �A�N�e�B�u���

	public:
		// �R���X�g���N�^
		Element()
			: isActive_(true)
		{
		}

		// �f�X�g���N�^
		virtual ~Element()
		{
			Clear();
		}

		/*
		// @method		Update
		// @content		�X�V����
		*/
		virtual void Update()
		{
			// �q�����Ă���R���|�[�l���g�̏���
			for (auto& component : componentList_)
			{
				component->Update(this);
			}
		}

		/*
		// @method		AddComponent�itemplate�j
		// @content		�R���|�[�l���g�̒ǉ�
		*/
		template <class C> void AddComponent()
		{
			componentList_.emplace_back(std::make_unique<C>());

			// ������
			componentList_.back()->Initialize(this);
		}

		/*
		// @method		RemoveComponent�itemplate�j
		// @content		�R���|�[�l���g�̍폜
		*/
		template <class C> void RemoveComponent()
		{
			for (auto& component : componentList_)
			{
				if (dynamic_cast<C*>(component.get()))
				{
					component->Finalize();
					componentList_.remove(component);
					break;
				}
			}
		}

		/*
		// @method		GetComponent�itemplate�j
		// @content		�R���|�[�l���g�̎擾
		*/
		template <class C> C* GetComponent()
		{
			for (auto& component : componentList_)
			{
				if (C* c = dynamic_cast<C*>(component.get()))
				{
					return c;
				}
			}

			return nullptr;
		}

		/*
		// @method		Clear
		// @content		���X�g�̃N���A
		*/
		void Clear()
		{
			componentList_.clear();
		}

		/* �A�N�Z�b�T */

		virtual void SetActive(bool active) { isActive_ = active; }

		inline virtual bool GetActive()	const { return isActive_; }
	};
}