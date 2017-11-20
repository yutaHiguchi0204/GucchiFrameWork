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
	// クラスの定義
	class Camera
	{
	public:
		// ビュー行列
		struct View
		{
			DirectX::SimpleMath::Matrix viewMat;		// ビュー行列
			DirectX::SimpleMath::Vector3 eyePos;		// カメラ視点
			DirectX::SimpleMath::Vector3 refPos;		// ターゲット座標
			DirectX::SimpleMath::Vector3 upVec;			// 上方向ベクトル
		};

		// プロジェクション行列
		struct Projection
		{
			DirectX::SimpleMath::Matrix projMat;		// プロジェクション行列
			float fov;									// 縦方向視野角
			float aspect;								// アスペクト比
			float nearClip;								// ニアクリップ
			float farClip;								// ファークリップ
		};

	protected:
		View		view_;								// ビュー行列関係
		Projection	proj_;								// プロジェクション行列関係

	public:
		Camera(int width, int height);
		virtual ~Camera() {};

		// 更新
		virtual void Update();

		// アクセッサ
		void SetEyePos(const DirectX::SimpleMath::Vector3& pos)		{ view_.eyePos = pos; }
		void SetRefPos(const DirectX::SimpleMath::Vector3& pos)		{ view_.refPos = pos; }
		void SetUpVec(const DirectX::SimpleMath::Vector3& vec)		{ view_.upVec = vec; }
		void SetFov(float fov)										{ proj_.fov = fov; }
		void SetAspect(float aspect)								{ proj_.aspect = aspect; }
		void SetNearClip(float nearClip)							{ proj_.nearClip = nearClip; }
		void SetFarClip(float farClip)								{ proj_.farClip = farClip; }

		inline const DirectX::SimpleMath::Matrix& GetView()			{ return view_.viewMat; }
		inline const DirectX::SimpleMath::Vector3& GetEyePos()		{ return view_.eyePos; }
		inline const DirectX::SimpleMath::Vector3& GetRefPos()		{ return view_.refPos; }
		inline const DirectX::SimpleMath::Vector3& GetUpVec()		{ return view_.upVec; }
		inline const DirectX::SimpleMath::Matrix& GetProjection()	{ return proj_.projMat; }
		inline float GetFov()										{ return proj_.fov; }
		inline float GetAspect()									{ return proj_.aspect; }
		inline float GetNearClip()									{ return proj_.nearClip; }
		inline float GetFarClip()									{ return proj_.farClip; }
	};
}