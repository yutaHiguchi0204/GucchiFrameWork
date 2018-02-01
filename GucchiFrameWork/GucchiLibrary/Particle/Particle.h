/* =====================================================================
//! @param		「Particle」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/27
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <VertexTypes.h>
#include "../3D/Asset3D.h"

namespace GucchiLibrary
{
	/*
	// @class		Particle クラス
	// @content		パーティクル
	*/
	class Particle
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Vector4 = DirectX::SimpleMath::Vector4;

	public:
		/*
		// @content		ループモード
		// @mode		DEFAULT		：	寿命に忠実なモード（-1なら消えない、設定されていればその時間で消える）
		// @mode		REPEAT		：	寿命になったら初期化されて初めからエフェクトを開始するモード
		// @mode		TURN		：	REPEATと同じ仕様だが、通常→逆→通常→逆・・・とアニメーションが再生されるモード
		*/
		enum class LOOP_MODE
		{
			DEFAULT,
			REPEAT,
			TURN,

			LOOP_MODE_NUM
		};

	public:
		static const int FOREVER_EXIST;			// 永続的存在
		static const float DEFAULT_SCALE;		// 初期スケール
		static const float DEFAULT_ROTATE;		// 初期回転角

	private:
		DirectX::VertexPositionColorTexture		vertexStart_;				// 始点情報
		DirectX::VertexPositionColorTexture		vertexEnd_;					// 終点情報
		DirectX::VertexPositionColorTexture		vertexNow_;					// 現在の頂点データ

		float									exisTime_;					// 寿命
		float									nowFrame_;					// 出現してからの経過フレーム

		Asset3D::BLEND_MODE						blendMode_;					// ブレンドモード
		LOOP_MODE								loopMode_;					// ループモード

		bool									isExist_;					// 存在しているかどうか

		std::unique_ptr<InterpolateDirector>	interpolateDirector_;		// 補間ステート

	public:
		// コンストラクタ
		Particle() = default;

		// コピーコンストラクタ
		Particle(const Particle& particle);

		// デストラクタ
		virtual ~Particle() = default;

		/*
		// @method		Initialize
		// @content		初期化処理
		// @param		寿命（float）							：	デフォルト（FOREVER_EXIST）
		// @param		始点情報（VertexPositionColorTexture）	：	デフォルト（VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		終点情報（VertexPositionColorTexture）	：	デフォルト（VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE))
		// @param		ブレンドモード（BLEND_MODE）			：	デフォルト（ALPHA）
		// @param		ループモード（LOOP_MODE）				：	デフォルト（DEFAULT）
		*/
		void Initialize(
			float exisTime = FOREVER_EXIST, 
			DirectX::VertexPositionColorTexture vertexDataStart = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE)),
			DirectX::VertexPositionColorTexture vertexDataEnd = DirectX::VertexPositionColorTexture(Vector3::Zero, Vector4::One, Vector2(DEFAULT_SCALE, DEFAULT_ROTATE)),
			Asset3D::BLEND_MODE blendMode = Asset3D::BLEND_MODE::ALPHA, 
			LOOP_MODE loopMode = LOOP_MODE::DEFAULT
		);

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update();

		/*
		// @method		Reset
		// @content		リセット
		*/
		void Reset();

		/* アクセッサ */

		inline const DirectX::VertexPositionColorTexture& GetVertexNow() const	{ return vertexNow_; }
		inline Asset3D::BLEND_MODE GetBlendMode() const							{ return blendMode_; }
		inline bool IsExist() const												{ return isExist_; }

	public:
		// 代入オペレータ
		Particle& operator=(const Particle& particle)
		{
			vertexStart_ = particle.vertexStart_;
			vertexEnd_   = particle.vertexEnd_;
			vertexNow_   = particle.vertexNow_;
			exisTime_    = particle.exisTime_;
			nowFrame_    = particle.nowFrame_;
			blendMode_   = particle.blendMode_;
			loopMode_    = particle.loopMode_;
			isExist_     = particle.isExist_;

			return (*this);
		}
	};
}