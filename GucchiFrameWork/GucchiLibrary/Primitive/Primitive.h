/* =====================================================================
//! @param		「Primitive」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/Element.h"
#include <GeometricPrimitive.h>
#include <map>
#include <string>
#include <vector>
#include <VertexTypes.h>

namespace GucchiLibrary
{
	/*
	// @class		Primitive クラス
	// @content		プリミティブ
	*/
	class Primitive : public Element
	{
	public:
		/*
		// @content		プリミティブタイプ
		// @mode		POINT		：	点
		// @mode		POINT3D		：	点
		// @mode		LINE		：	線
		// @mode		SEGMENT		：	線分
		// @mode		TRIANGLE	：	三角
		// @mode		RECTANGLE	：　長方形
		// @mode		BOX			：	直方体
		// @mode		CIRCLE		：　円
		// @mode		SPHERE		：	球
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
		PRIMITIVE_TYPE											type_;			// プリミティブタイプ

	public:
		Vector3													pos_;			// 座標
		bool													isFill_;		// 塗りつぶしするかどうか

	public:
		// コンストラクタ
		Primitive();

		// デストラクタ
		virtual ~Primitive() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update() override { Element::Update(); }

		/* アクセッサ */

		void SetType(PRIMITIVE_TYPE type)		{ type_ = type; }

		inline PRIMITIVE_TYPE GetType()	const	{ return type_; }
	};

	/*
	// @class		Primitive2D クラス
	// @content		２Ｄプリミティブ
	*/
	class Primitive2D : public Primitive
	{
	public:
		std::map<std::string, DirectX::VertexPositionColor>		vertices_;		// 頂点データ

	public:
		// コンストラクタ
		Primitive2D();

		// デストラクタ
		virtual ~Primitive2D() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update() override { Primitive::Update(); }

		/*
		// @method		GetKeys
		// @content		キーの取得
		// @return		全てのキー（vector<string>）
		*/
		std::vector<std::string> GetKeys() const;
	};

	/*
	// @class		Primitive3D クラス
	// @content		プリミティブ
	*/
	class Primitive3D : public Primitive
	{
	public:
		std::unique_ptr<DirectX::GeometricPrimitive>	geometry_;		// ジオメトリ
		Color											color_;			// 色情報

	public:
		// コンストラクタ
		Primitive3D();

		// デストラクタ
		virtual ~Primitive3D() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update() override { Primitive::Update(); }
	};

	/*
	// @class		Circle クラス
	// @content		円プリミティブ
	*/
	class Circle : public Primitive2D
	{
	public:
		float	radius_;		// 半径
		int		div_;			// 分割数
	};
}