/* =====================================================================
//! @param		「Collider」ヘッダ
//! @create		樋口 裕太
//! @date		18/02/07
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "../Common/Component.h"

namespace GucchiLibrary
{
	/*
	// @class		Collider クラス
	// @content		当たり判定クラス
	*/
	class Collider : public Component
	{
	protected:
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		// コンストラクタ
		Collider() = default;

		// デストラクタ
		virtual ~Collider() = default;

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		virtual void Update(Element* element) override = 0;
	};

	/*
	// @class		Segment クラス
	// @content		線分
	*/
	class Segment : public Collider
	{
	public:
		Vector3 start_;			// 始点
		Vector3 end_;			// 終点

	public:
		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Sphere クラス
	// @content		球
	*/
	class Sphere : public Collider
	{
	public:
		Vector3 center_;		// 中心座標
		float radius_;			// 半径

	public:
		// コンストラクタ
		Sphere() : radius_(1.0f) {}

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Capsule クラス
	// @content		カプセル
	*/
	class Capsule : public Collider
	{
	public:
		Segment segment_;		// 芯線
		float radius_;			// 半径

	public:
		// コンストラクタ
		Capsule() : radius_(1.0f)
		{
			segment_.start_ = Vector3(0.f, 0.f, 0.f);
			segment_.end_ = Vector3(0.f, 1.f, 0.f);
		}

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Plane クラス
	// @content		平面
	*/
	class Plane : public Collider
	{
	public:
		Vector3 normal_;		// 法線ベクトル
		float distance_;		// 原点からの距離

	public:
		// コンストラクタ
		Plane() : distance_(0.f) {}

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		Triangle クラス
	// @content		三角形（反時計回り、法線付き）
	*/
	class Triangle : public Collider
	{
	public:
		Vector3 p0_;			// １つ目の頂点
		Vector3 p1_;			// ２つ目の頂点
		Vector3 p2_;			// ３つ目の頂点
		Vector3 normal_;		// 法線ベクトル

	public:
		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		AABB クラス
	// @content		軸平行境界ボックス
	*/
	class AABB : public Collider
	{
	public:
		Vector3 min_;			// 最小座標
		Vector3 max_;			// 最大座標

	public:
		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		OBB クラス
	// @content		有向境界ボックス
	*/
	class OBB : public Collider
	{
	public:
		Vector3 center_;		// 中心座標
		Vector3 axis_[3];		// ローカル座標
		Vector3 size_;			// サイズ

	public:
		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};
}
