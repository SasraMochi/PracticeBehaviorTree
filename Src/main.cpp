#include <windows.h>
#include "DxLib.h"
#include <assert.h> // �摜�ǂݍ��ݎ��s�\���p

#include "Math/MySystemTimer.h"
#include "Math/Screen.h"
#include "Game.h"

// FPS�֘A�ݒ�
int TargetFPS = 60;
static bool EnableFrameSkip = true;
double MaxAllowSkipTime = 0.2;
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000);
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks;
static int skipCount = 0;
static long fpsTicks = 0;
static int fpsFrameCount = 0;
static float CurrentFPS; // ���݂�FPS

// �`�揈��
static void GameDraw(Game& game)
{
	ClearDrawScreen();
	game.draw();

	ScreenFlip();
	skipCount = 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �v���O�����̏����D��x���グ��
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	// ���������̐ݒ�
	SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);

	// ��ʃ��[�h�̐ݒ�
	SetWindowSize(Screen::Width, Screen::Height);
	SetGraphMode(Screen::Width, Screen::Height, 32);
	SetMainWindowText("�Q�[���̃E�B���h�E����ς���Ƃ��͂���");
	ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);

	// DX���C�u�����̏�����
	if (DxLib_Init() < 0) return -1;

	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE);

	// �Q�[��������
	Game game;
	game.start();

	MySystemTimer& timer = MySystemTimer::GetInstance();
	ScreenFlip();
	timer.Init();

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// FPS�v��
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

		// �X���[���[�V�����E������Ή�
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{
			TargetFPS = (int)(60 / timer.timeScale);
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000);
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}

		// �����������L���ȏꍇ
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
			// ���������������ȏꍇ
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
