/* =====================================================================
//! @param		「Emitter」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/27
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Particle.h"
#include <PrimitiveBatch.h>
#include <string>
#include <vector>
#include "../2D/TextureCache.h"
#include "../3D/Object.h"

namespace GucchiLibrary
{
	/*
	// @class		Emitter クラス
	// @content		パーティクルエミッター
	*/
	class Emitter : public Element
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Vector4 = DirectX::SimpleMath::Vector4;

	public:
		static const int FOREVER_EXIST;			// 寿命

	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>	primitiveBatch_;	// プリミティブバッチ

		Texture*																		texture_;			// パーティクル用テクスチャ
		std::vector<std::unique_ptr<Particle>>											particle_;			// パーティクル

		Vector3																			pos_;				// エミッターの座標
		float																			exisTime_;			// エミッターの寿命
		float																			nowFrame_;			// 出現してからの経過フレーム
		bool																			isExist_;			// 存在しているかどうか

		Object*																			parentObject_;		// 親オブジェクト

	public:
		/*
		// @method		コンストラクタ
		// @param		エミッターの座標（Vector3）	：	デフォルト（Vector3::Zero）
		// @param		寿命（float）				：	デフォルト（FOREVER_EXIST）
		*/
		Emitter(const Vector3& pos = Vector3::Zero, float exisTime = FOREVER_EXIST);

		// デストラクタ
		virtual ~Emitter() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update();

		/*
		// @method		Draw
		// @content		描画処理
		*/
		void Draw();

		/*
		// @method		Entry
		// @content		パーティクル生成
		// @param		寿命（float）							：	デフォルト（FOREVER_EXIST）
		// @param		始点情報（VertexPositionColorTexture）	：	デフォルト（VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		終点情報（VertexPositionColorTexture）	：	デフォルト（VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		ブレンドモード（BLEND_MODE）			：	デフォルト（ALPHA）
		// @param		ループモード（LOOP_MODE）				：	デフォルト（DEFAULT）
		*/
		void Entry(
			float exisTime = FOREVER_EXIST,
			DirectX::VertexPositionColorTexture vertexDataStart = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(Particle::DEFAULT_SCALE, Particle::DEFAULT_ROTATE)),
			DirectX::VertexPositionColorTexture vertexDataEnd = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(Particle::DEFAULT_SCALE, Particle::DEFAULT_ROTATE)),
			Asset3D::BLEND_MODE blendMode = Asset3D::BLEND_MODE::ALPHA,
			Particle::LOOP_MODE loopMode = Particle::LOOP_MODE::DEFAULT
		);

		/*
		// @method		LoadTexture
		// @content		テクスチャの読み込み
		// @param		テクスチャファイル名（wstring）
		*/
		void LoadTexture(const std::wstring& fileName);

		/* アクセッサ */

		void SetPos(const Vector3& pos)			{ pos_ = pos; }
		void SetParent(Object* parent)			{ parentObject_ = parent; }

		inline const Vector3& GetPos() const	{ return pos_; }
		inline bool IsExist() const				{ return isExist_; }
	};
}