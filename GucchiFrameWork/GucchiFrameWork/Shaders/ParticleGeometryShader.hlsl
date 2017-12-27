/* =====================================================================
//! @param		「ParticleGeometryShader」シェーダソース
//! @create		樋口 裕太
//! @date		17/12/26
===================================================================== */

// ヘッダファイルのインクルード
#include "Particle.hlsli"

// 四角形の頂点数
static const uint vNum = 4;

// 中心点からのオフセット（モデル座標ベース）
static const float4 offsetArray[vNum] =
{
	{ -0.5f, -0.5f, 0, 0 },			// 左下
	{  0.5f, -0.5f, 0, 0 },			// 右下
	{ -0.5f,  0.5f, 0, 0 },			// 左上
	{  0.5f,  0.5f, 0, 0 }			// 右上
};

// 
static const float2 uvArray[vNum] =
{
	{ 0.0f, 1.0f },					// 左下
	{ 1.0f, 1.0f },					// 右下
	{ 0.0f, 0.0f },					// 左上
	{ 1.0f, 0.0f }					// 右上
};

/*==============================================================
// @brief		ジオメトリシェーダ
// @param		ジオメトリシェーダへの入力（GS_INPUT）、ピクセルシェーダへの入力用三角ポリゴン情報（PS_INPUT）
// @return		なし
===============================================================*/
[maxvertexcount(4)]
void main(point GS_INPUT input[1], inout TriangleStream<PS_INPUT> psOut)
{
	PS_INPUT element;

	float4 offset = float4(0, 0, 0, 0);
	float scale = input[0].other_.x;
	float rot = input[0].other_.y;

	// 4点分の情報を設定
	for (uint i = 0; i < vNum; i++)
	{
		// 指定した角度分回転させる
		offset.x = offsetArray[i].x *  cos(rot) + offsetArray[i].y * sin(rot);
		offset.y = offsetArray[i].x * -sin(rot) + offsetArray[i].y * cos(rot);
		offset.z = 0;
		offset.w = 0;

		// ビルボード回転
		offset = mul(offset, billboard_);

		// サンプル
		element.pos_ = input[0].pos_ + offset * scale;

		// 座標変換（3D → 2D）
		element.pos_ = mul(element.pos_, wvpMat_);
		element.color_ = input[0].color_;
		element.uv_ = uvArray[i];
		psOut.Append(element);
	}

	// プリミティブの区切り
	psOut.RestartStrip();
}