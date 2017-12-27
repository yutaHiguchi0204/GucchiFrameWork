/* =====================================================================
//! @param		「Particle」シェーダヘッダ
//! @create		樋口 裕太
//! @date		17/12/26
===================================================================== */

/*
// @summary		コンスタントバッファ
// @content		パーティクルを描画する際に必要となる情報をまとめた構造体
*/
cbuffer Constants
{
	row_major matrix wvpMat_;			// ワールド・ビュー・プロジェクションの合成行列
	row_major matrix billboard_;		// ビルボード行列
};

/*
// @summary		テクスチャ関係
// @content		テクスチャ・テクスチャサンプラー
*/
Texture2D texture_		: register(t0);
SamplerState sampler_	: register(s0);

/*
// @summary		ジオメトリシェーダ
// @content		ジオメトリシェーダへの入力
*/
struct GS_INPUT
{
	float4 pos_		: SV_POSITION;
	float4 color_	: COLOR;

	// other_.x : scale  other_.y : rot
	float2 other_	: TEXCOORD;
};

/*
// @summary		ピクセルシェーダ
// @content		ピクセルシェーダへの入力
*/
struct PS_INPUT
{
	float4 pos_		: SV_POSITION;
	float4 color_	: COLOR;
	float2 uv_		: TEXCOORD;
};