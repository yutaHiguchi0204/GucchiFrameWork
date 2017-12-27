/* =====================================================================
//! @param		「ParticlePixelShader」シェーダソース
//! @create		樋口 裕太
//! @date		17/12/26
===================================================================== */

// ヘッダファイルのインクルード
#include "Particle.hlsli"

/*==============================================================
// @brief		頂点シェーダ
// @param		ピクセルシェーダへの入力（PS_INPUT）
// @return		シェーダ（float4）
===============================================================*/
float4 main(PS_INPUT input) : SV_TARGET
{
	float4 color = texture_.Sample(sampler_, input.uv_) * input.color_;
	return color;
}