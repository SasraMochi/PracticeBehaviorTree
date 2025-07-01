#include <windows.h>
#include "DxLib.h"
#include <assert.h> // 画像読み込み失敗表示用

#include "Math/MySystemTimer.h"
#include "Math/Screen.h"
#include "Game.h"

#include "imgui.h"
#include <Backends/imgui_impl_win32.h>
#include <Backends/imgui_impl_dx11.h>

#include "imnodes.h"

// FPS関連設定
int TargetFPS = 60;
static bool EnableFrameSkip = true;
double MaxAllowSkipTime = 0.2;
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000);
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks;
static int skipCount = 0;
static long fpsTicks = 0;
static int fpsFrameCount = 0;
static float CurrentFPS; // 現在のFPS

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ImGuiにプロシージャの情報を流す
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp)) {
		return true;
	}

	return 0;
}

// 描画処理
static void GameDraw(Game& game)
{
	ClearDrawScreen();
	game.draw();

	// ImGuiの描画
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	game.draw_debug();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ScreenFlip();
	skipCount = 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// プログラムの処理優先度を上げる
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	// 垂直同期の設定
	SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);

	// 画面モードの設定
	SetWindowSize(Screen::Width, Screen::Height);
	SetGraphMode(Screen::Width, Screen::Height, 32);
	SetMainWindowText("ゲームのウィンドウ名を変えるときはここ");
	ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);

	// DXライブラリの初期化
	if (DxLib_Init() < 0) return -1;

	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE);

	// ImGuiの初期化
	ImGui::CreateContext();
	ImNodes::CreateContext();
	g_pd3dDevice = (ID3D11Device*)(GetUseDirect3D11Device());
	g_pd3dDeviceContext = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
	ImGui_ImplWin32_Init(GetMainWindowHandle());
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	SetHookWinProc(WndProc);
	ImGui::GetIO().Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 40.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	// ImGui_ImplDX11_CreateDeviceObjects();

	// ゲーム初期化
	Game game(Screen::Width, Screen::Height);
	game.start();

	MySystemTimer& timer = MySystemTimer::GetInstance();
	ScreenFlip();
	timer.Init();

	// メインループ
	while (ProcessMessage() == 0)
	{
		// FPS計測
		fpsFrameCount++;
		if (fpsFrameCount >= 60)
		{
			long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
			float elapsedSec = (float)elapsedTicks / 10000000;
			CurrentFPS = fpsFrameCount / elapsedSec;
			fpsFrameCount = 0;
			fpsTicks = timer.GetElapsedTicks();
		}

		game.update();

		// スローモーション・早送り対応
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{
			TargetFPS = (int)(60 / timer.timeScale);
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000);
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}

		// 垂直同期が有効な場合
		if (GetWaitVSyncFlag() == TRUE && !timer.isTimeScaleMode)
		{
			if (EnableFrameSkip)
			{
				long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
				if (waitTicks < 0)
				{
					if (skipCount < MaxAllowSkipCount)
					{
						skipCount++;
					}
					else
					{
						nextFrameTicks = timer.GetElapsedTicks();
						GameDraw(game);
					}
				}
				else
				{
					GameDraw(game);
				}
				nextFrameTicks += IntervalTicks;
			}
			else
			{
				GameDraw(game);
			}
		}
		else
		{
			// 垂直同期が無効な場合
			long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
			if (EnableFrameSkip && waitTicks < 0)
			{
				if (skipCount < MaxAllowSkipCount)
				{
					skipCount++;
				}
				else

				{
					nextFrameTicks = timer.GetElapsedTicks();
					GameDraw(game);
				}
			}
			else
			{
				if (waitTicks > 20000)
				{
					int waitMillsec = (int)(waitTicks / 10000) - 2;
					timer.SleepForMilliSec(waitMillsec);
				}
				while (timer.GetElapsedTicks() < nextFrameTicks) {}
				GameDraw(game);
			}
			nextFrameTicks += IntervalTicks;
		}
	}

#if _DEBUG
	// ImGui終了処理
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImNodes::DestroyContext();
	ImGui::DestroyContext();
#endif

	WaitKey();
	DxLib::DxLib_End();
	return 0;
}
