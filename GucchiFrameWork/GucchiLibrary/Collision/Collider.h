/* =====================================================================
//! @param		「Collider」ヘッダ
//! @create		樋口 裕太
//! @date		18/02/07
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <memory>
#include "../Common/Component.h"
#include "../Primitive/PrimitiveRenderer.h"

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

	protected:
		std::unique_ptr<Primitive>	primitive_;				// 当たり判定用プリミティブ

	public:
		// コンストラクタ
		Collider() = default;

		// デストラクタ
		virtual ~Collider() = default;

		/*
		// @method		Initialize
		// @content		初期化処理
		// @param		要素（Element*）
		*/
		virtual void Initialize(Element* element) override = 0;

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		virtual void Update(Element* element) override = 0;

		/*
		// @method		SetPrimitiveActive（static）
		// @content		当たり判定のアクティブ状態の変更
		// @param		アクティブ状態（bool）
		*/
		void SetPrimitiveActive(bool active);
	};

	/*
	// @class		SegmentCollider クラス
	// @content		線分
	*/
	class SegmentCollider : public Collider
	{
	public:
		Vector3 start_;			// 始点
		Vector3 end_;			// 終点

	public:
		/*
		// @method		Initialize
		// @content		初期化処理
		// @param		要素（Element*）
		*/
		void Initialize(Element* element) override;

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	/*
	// @class		SphereCollider クラス
	// @content		球
	*/
	class SphereCollider : public Collider
	{
	public:
		Vector3 center_;		// 中心座標
		float radius_;			// 半径

	public:
		// コンストラクタ
		SphereCollider() : radius_(1.0f) {}

		/*
		// @method		Initialize
		// @content		初期化処理
		// @param		要素（Element*）
		*/
		void Initialize(Element* element) override;

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	///*
	//// @class		CapsuleCollider クラス
	//// @content		カプセル
	//*/
	//class CapsuleCollider : public Collider
	//{
	//public:
	//	SegmentCollider segment_;		// 芯線
	//	float radius_;			// 半径

	//public:
	//	// コンストラクタ
	//	CapsuleCollider() : radius_(1.0f)
	//	{
	//		segment_.start_ = Vector3(0.f, 0.f, 0.f);
	//		segment_.end_ = Vector3(0.f, 1.f, 0.f);
	//	}

	//	/*
	//	// @method		Initialize
	//	// @content		初期化処理
	//	// @param		要素（Element*）
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		更新処理
	//	// @param		要素（Element*）
	//	*/
	//	void Update(Element* element) override;
	//};

	///*
	//// @class		PlaneCollider クラス
	//// @content		平面
	//*/
	//class PlaneCollider : public Collider
	//{
	//public:
	//	Vector3 normal_;		// 法線ベクトル
	//	float distance_;		// 原点からの距離

	//public:
	//	// コンストラクタ
	//	PlaneCollider() : distance_(0.f) {}

	//	/*
	//	// @method		Initialize
	//	// @content		初期化処理
	//	// @param		要素（Element*）
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		更新処理
	//	// @param		要素（Element*）
	//	*/
	//	void Update(Element* element) override;
	//};

	///*
	//// @class		TriangleCollider クラス
	//// @content		三角形（反時計回り、法線付き）
	//*/
	//class TriangleCollider : public Collider
	//{
	//public:
	//	Vector3 p0_;			// １つ目の頂点
	//	Vector3 p1_;			// ２つ目の頂点
	//	Vector3 p2_;			// ３つ目の頂点
	//	Vector3 normal_;		// 法線ベクトル

	//public:
	//	/*
	//	// @method		Initialize
	//	// @content		初期化処理
	//	// @param		要素（Element*）
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		更新処理
	//	// @param		要素（Element*）
	//	*/
	//	void Update(Element* element) override;
	//};

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
		// @method		Initialize
		// @content		初期化処理
		// @param		要素（Element*）
		*/
		void Initialize(Element* element) override;

		/*
		// @method		Update
		// @content		更新処理
		// @param		要素（Element*）
		*/
		void Update(Element* element) override;
	};

	///*
	//// @class		OBB クラス
	//// @content		有向境界ボックス
	//*/
	//class OBB : public Collider
	//{
	//public:
	//	Vector3 center_;		// 中心座標
	//	Vector3 axis_[3];		// ローカル座標
	//	Vector3 size_;			// サイズ

	//public:
	//	/*
	//	// @method		Initialize
	//	// @content		初期化処理
	//	// @param		要素（Element*）
	//	*/
	//	void Initialize(Element* element) override;

	//	/*
	//	// @method		Update
	//	// @content		更新処理
	//	// @param		要素（Element*）
	//	*/
	//	void Update(Element* element) override;
	//};
}
