/* =====================================================================
//! @param		�uFramework�v�w�b�_
//! @create		��� �T��
//! @date		17/10/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <DirectXMath.h>
#include <DirectXColors.h>
#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"
#include "../Utility/Interpolater.h"

namespace GucchiLibrary
{
	/*
	// @class		Framework �N���X
	// @content		�A�v���𐧌䂷��t���[�����[�N
	*/
	class Framework : public IDeviceNotify
	{
	public:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		HWND								hwnd_;

		// �`��p���[�v�^�C�}�[
		StepTimer&							timer_ = StepTimer::GetInstance();

		// FPS�\��
		bool isDispFPS_;

	public:
		Framework(HINSTANCE hInstance, int nCmdShow);
		virtual ~Framework() {};

		virtual void Initialize() {};
		virtual void Finalize() {};

		// �Q�[�����[�v�p
		virtual void Tick();

		// ���b�Z�[�W�֘A
		virtual void OnActivated();
		virtual void OnDeactivated();
		virtual void OnSuspending();
		virtual void OnResuming();
		virtual void OnWindowSizeChanged(int width, int height);

		// �v���p�e�B
		void GetDefaultSize(int& width, int& height) const;

		// ���̑�
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