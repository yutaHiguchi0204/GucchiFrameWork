/* =====================================================================
//! @param		Main
//! @create		樋口 裕太
//! @date		17/10/09
===================================================================== */

// ヘッダファイルのインクルード
#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <memory>

#include "Game.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// ハイブリッドグラフィックスシステムが個々のパーツを優先するように設定（デフォルト）
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

// ここから始まる
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

    // メインループ
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

// ゲーム終了
void ExitGame()
{
    PostQuitMessage(0);
}
