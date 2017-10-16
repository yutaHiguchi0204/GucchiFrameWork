/* =====================================================================
//! @param		Main
//! @create		��� �T��
//! @date		17/10/09
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <memory>

#include "Game.h"

// ���O���
using namespace GucchiLibrary;
using namespace std;

// �n�C�u���b�h�O���t�B�b�N�X�V�X�e�����X�̃p�[�c��D�悷��悤�ɐݒ�i�f�t�H���g�j
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

// ��������n�܂�
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	unique_ptr<Framework> framework;

    HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
    if (FAILED(hr))
        return 1;

	try
	{
		framework = make_unique<Game>(hInstance, nCmdShow);
	}
	catch (...)
	{
		return 1;
	}
	framework->Initialize();

    // ���C�����[�v
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            framework->Tick();
        }
    }

	framework->Finalize();
	framework.reset();

    CoUninitialize();

    return (int) msg.wParam;
}

// �Q�[���I��
void ExitGame()
{
    PostQuitMessage(0);
}
