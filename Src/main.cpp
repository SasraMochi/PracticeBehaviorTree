#include <windows.h>
#include "DxLib.h"
#include <assert.h> // 画像読み込み失敗表示用

#include "Math/MySystemTimer.h"
#include "Math/Screen.h"
#include "Game.h"

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

// 描画処理
static void GameDraw(Game& game)
{
	ClearDrawScreen();
	game.draw();

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

	// ゲーム初期化
	Game game;
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

	WaitKey();
	DxLib::DxLib_End();
	return 0;
}
