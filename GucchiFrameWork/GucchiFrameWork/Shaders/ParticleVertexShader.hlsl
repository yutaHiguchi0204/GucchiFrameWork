/* =====================================================================
//! @param		「ParticleVertexShader」シェーダソース
//! @create		樋口 裕太
//! @date		17/12/26
===================================================================== */

// ヘッダファイルのインクルード
#include "Particle.hlsli"

/*==============================================================
// @brief		頂点シェーダ
// @param		位置（float4）、色（float4）、テクスチャコード（float2）
// @return		ジオメトリシェーダへの入力（GS_INPUT）
===============================================================*/
GS_INPUT main(float4 pos : POSITION, float4 color : COLOR, float2 other : TEXCOORD)
{
	GS_INPUT gsOut;

	gsOut.pos_ = pos;
	gsOut.color_ = color;
	gsOut.other_ = other;

	return gsOut;
}