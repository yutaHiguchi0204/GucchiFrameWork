/* =====================================================================
//! @param		�uElement�v�w�b�_
//! @create		��� �T��
//! @date		18/02/08
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <list>
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
		std::list<Component*> componentList_;			// �R���|�[�l���g���X�g

	public:
		// �R���X�g���N�^
		Element() = default;

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
			componentList_.emplace_back(new C);

			// �d���h�~
			componentList_.unique();
		}

		/*
		// @method		RemoveComponent�itemplate�j
		// @content		�R���|�[�l���g�̍폜
		*/
		template <class C> void RemoveComponent()
		{
			for (auto& component : componentList_)
			{
				C* type = dynamic_cast<C*>(component);

				if (type)
				{
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
				C* type = dynamic_cast<C*>(component);

				if (type)
				{
					return type;
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
			for (auto& component : componentList_)
			{
				delete component;
			}

			componentList_.clear();
		}
	};
}