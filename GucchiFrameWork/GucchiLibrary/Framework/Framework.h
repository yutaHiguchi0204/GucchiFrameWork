/* =====================================================================
//! @param		「Framework」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/09
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <DirectXMath.h>
#include <DirectXColors.h>
#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"
#include "../Utility/Interpolater.h"

namespace GucchiLibrary
{
	/*
	// @class		Framework クラス
	// @content		アプリを制御するフレームワーク
	*/
	class Framework : public IDeviceNotify
	{
	public:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		HWND								hwnd_;

		// 描画用ループタイマー
		StepTimer&							timer_ = StepTimer::GetInstance();

		// FPS表示
		bool isDispFPS_;

	public:
		Framework(HINSTANCE hInstance, int nCmdShow);
		virtual ~Framework() {};

		virtual void Initialize() {};
		virtual void Finalize() {};

		// ゲームループ用
		virtual void Tick();

		// メッセージ関連
		virtual void OnActivated();
		virtual void OnDeactivated();
		virtual void OnSuspending();
		virtual void OnResuming();
		virtual void OnWindowSizeChanged(int width, int height);

		// プロパティ
		void GetDefaultSize(int& width, int& height) const;

		// その他
		void SetIsDispFPS(bool flag) { isDispFPS_ = flag; }

		// IDeviceNotify override
		virtual void OnDeviceLost() override {};
		virtual void OnDeviceRestored() override;

	protected:
		virtual void Update(const StepTimer& timer) = 0;
		virtual void PreRender();
		virtual void PostRender();
		virtual void Render() = 0;
		virtual void Clear();

		virtual void CreateDeviceDependentResources();
		virtual void CreateWindowSizeDependentResources() {};
	};
}