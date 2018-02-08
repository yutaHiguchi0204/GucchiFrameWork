/* =====================================================================
//! @param		「Element」ヘッダ
//! @create		樋口 裕太
//! @date		18/02/08
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <list>
#include <SimpleMath.h>
#include "Component.h"

namespace GucchiLibrary
{
	/*
	// @class		Element クラス
	// @content		要素の基底クラス
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
		std::list<Component*> componentList_;			// コンポーネントリスト

	public:
		// コンストラクタ
		Element() = default;

		// デストラクタ
		virtual ~Element()
		{
			Clear();
		}

		/*
		// @method		Update
		// @content		更新処理
		*/
		virtual void Update()
		{
			// 繋げられているコンポーネントの処理
			for (auto& component : componentList_)
			{
				component->Update(this);
			}
		}

		/*
		// @method		AddComponent（template）
		// @content		コンポーネントの追加
		*/
		template <class C> void AddComponent()
		{
			componentList_.emplace_back(new C);

			// 重複防止
			componentList_.unique();
		}

		/*
		// @method		RemoveComponent（template）
		// @content		コンポーネントの削除
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
		// @method		GetComponent（template）
		// @content		コンポーネントの取得
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
		// @content		リストのクリア
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