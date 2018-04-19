/* =====================================================================
//! @param		「Element」ヘッダ
//! @create		樋口 裕太
//! @date		18/02/08
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <list>
#include <memory>
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
		std::list<std::unique_ptr<Component>>	componentList_;			// コンポーネントリスト
		bool									isActive_;				// アクティブ状態

	public:
		// コンストラクタ
		Element()
			: isActive_(true)
		{
		}

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
			componentList_.emplace_back(std::make_unique<C>());

			// 初期化
			componentList_.back()->Initialize(this);
		}

		/*
		// @method		RemoveComponent（template）
		// @content		コンポーネントの削除
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
		// @method		GetComponent（template）
		// @content		コンポーネントの取得
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
		// @content		リストのクリア
		*/
		void Clear()
		{
			componentList_.clear();
		}

		/* アクセッサ */

		virtual void SetActive(bool active) { isActive_ = active; }

		inline virtual bool GetActive()	const { return isActive_; }
	};
}