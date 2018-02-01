/* =====================================================================
//! @param		「Camera」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>

namespace GucchiLibrary
{
	/*
	// @class		Camera クラス
	// @content		カメラ
	// @use			グローバル座標系の描画に使用
	*/
	class Camera
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix = DirectX::SimpleMath::Matrix;

	public:
		/*
		// @struct		View 構造体
		// @content		ビュー行列関係
		*/
		struct View
		{
			Matrix viewMat;				// ビュー行列
			Vector3 eyePos;				// カメラ視点
			Vector3 refPos;				// ターゲット座標
			Vector3 upVec;				// 上方向ベクトル
		};

		/*
		// @struct		Projection 構造体
		// @content		プロジェクション行列関係
		*/
		struct Projection
		{
			Matrix projMat;				// プロジェクション行列
			float fov;					// 縦方向視野角
			float aspect;				// アスペクト比
			float nearClip;				// ニアクリップ
			float farClip;				// ファークリップ
		};

	protected:
		View			view_;					// ビュー行列関係
		Projection		proj_;					// プロジェクション行列関係

		Matrix			billboard_;				// ビルボード行列
		Matrix			billboardConstrainY_;	// ビルボード行列（Y軸限定）

	public:
		/*
		// @method		コンストラクタ
		// @param		画面の幅（int）
		// @param		画面の高さ（int）
		*/
		Camera(int width, int height);

		// デストラクタ
		virtual ~Camera() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		virtual void Update();

		/*
		// @method		CalcBillboard
		// @content		ビルボード行列の計算
		*/
		virtual void CalcBillboard();

		/* アクセッサ */

		void SetEyePos(const Vector3& pos)						{ view_.eyePos = pos; }
		void SetRefPos(const Vector3& pos)						{ view_.refPos = pos; }
		void SetUpVec(const Vector3& vec)						{ view_.upVec = vec; }
		void SetFov(float fov)									{ proj_.fov = fov; }
		void SetAspect(float aspect)							{ proj_.aspect = aspect; }
		void SetNearClip(float nearClip)						{ proj_.nearClip = nearClip; }
		void SetFarClip(float farClip)							{ proj_.farClip = farClip; }

		inline const Matrix& GetView() const					{ return view_.viewMat; }
		inline const Vector3& GetEyePos() const					{ return view_.eyePos; }
		inline const Vector3& GetRefPos() const					{ return view_.refPos; }
		inline const Vector3& GetUpVec() const					{ return view_.upVec; }
		inline const Matrix& GetProjection() const				{ return proj_.projMat; }
		inline float GetFov() const								{ return proj_.fov; }
		inline float GetAspect() const							{ return proj_.aspect; }
		inline float GetNearClip() const						{ return proj_.nearClip; }
		inline float GetFarClip() const							{ return proj_.farClip; }
		inline const Matrix& GetBillboard() const				{ return billboard_; }
		inline const Matrix& GetBillboardConstrainY() const		{ return billboardConstrainY_; }
	};
}