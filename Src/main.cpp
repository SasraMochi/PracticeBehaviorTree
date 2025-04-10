#include "DxLib.h"
#include <assert.h> // 画像読み込みの読込み失敗表示用

#include "Math/MySystemTimer.h"


#include "Math/Screen.h"
#include "Game.h"

int TargetFPS = 60; // 目標のFPS(Frame Per Second, 1秒あたりのフレーム数)
static bool EnableFrameSkip = true; // 高負荷時にフレームスキップするか（falseの場合は処理落ち（スロー））
double MaxAllowSkipTime = 0.2; // フレームスキップする最大間隔（秒）。これ以上の間隔が空いた場合はスキップせずに処理落ちにする。
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // フレーム間のTick数。1Tick = 100ナノ秒 = 1/10000000秒
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks; // 次のフレームの目標時刻
static int skipCount = 0; // 何回連続でフレームスキップしたか
static long fpsTicks = 0; // FPS計測のためのTicks。
static int fpsFrameCount = 0; // FPS計測のためのフレームカウント。60回数えるごとに、要した時間からFPSを算出する。

/// <summary>
/// 現在のFPS（Frame per Second）
/// </summary>
static float CurrentFPS;


// static関数はどこでも呼べる関数
static void GameDraw(Game& game)
{
    ClearDrawScreen();// 一旦キャンバスをきれいにまっさらに
    game.draw(); // パラパラ漫画の描画処理
    ScreenFlip(); // 裏で描いておいたパラパラ漫画を表面に入れ替えフリップ
    skipCount = 0; // フレームスキップのカウントをリセット
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // [Windowsの機能]このプログラム実行の処理優先度を上げる
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

    // ★垂直同期とはモニターへの描画が完了するまで処理全体を停止し、
    // 描画処理と更新処理の間隔を双方一定となるように処理の間隔を調整すること
    // https://qiita.com/Seiten_Minagawa/items/615312ebe5e688ffee7f
    // 画面リフレッシュレートと目標フレームレートが等しい場合は垂直同期を有効に、等しくない場合は垂直同期を無効にする
    SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);
    // 画面モードの設定
    SetWindowSize(Screen::Width, Screen::Height);// ウィンドウサイズ960×540(こことSetGraphModeのサイズが異なると画像がゆがむ)
    SetGraphMode(Screen::Width, Screen::Height, 32); // 画面サイズ960×540のカラービット数32ビットで起動
    SetMainWindowText("ゲームのウィンドウ名を変えるときはここ");//この行でエラーになったら【設定】マルチバイト文字セットが間違ってるかも
    ChangeWindowMode(TRUE);//フルスクリーン表示かウィンドウ表示か
    SetAlwaysRunFlag(TRUE); // ウィンドウが非アクティブでも動作させる

    // ＤＸライブラリの初期化
    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }

    SetMouseDispFlag(TRUE);// ここをFALSEにするとマウスカーソル非表示
    //表示しているスクリーンの後ろで隠れて次に描く画像を先に描くモード
    // これとペアでScreenFlip();でつぎのページと入れ替えでちらつきを防ぐ
    SetDrawScreen(DX_SCREEN_BACK);
    SetUseTransColor(FALSE); // 画像の指定色を透過する機能を無効化

    // これまでInitでやってきてた初期化処理
    Game game;
    game.start(); // gameのInit準備

    // 独自時刻クラスの参照を得る(シングルトン型)
    MySystemTimer& timer = MySystemTimer::GetInstance();
    ScreenFlip();

    timer.Init(); // 時刻計測開始

    // アニメーション(パラパラ漫画)するにはWhile文
    while (ProcessMessage() == 0)
    {
        // FPSの計測(FPS = 1秒あたりのパラパラ漫画枚数)
        fpsFrameCount++;
        if (fpsFrameCount >= 60)
        {   // 経過時間 1Tick = 100ナノ秒 = 1/10000000秒 (elasped=経過)
            long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
            float elapsedSec = (float)elapsedTicks / 10000000;
            CurrentFPS = fpsFrameCount / elapsedSec;// 現在のFPS

            fpsFrameCount = 0; // 60枚数えたら0リセット
            // 60枚数えたら現在のFPS(パラパラ速度)を記録
            fpsTicks = timer.GetElapsedTicks();
        }

        game.update(); //ゲームの更新処理

        //[実験機能]スローモーション、早送り(time.timeScaleが0.5で2倍速2.0で1/2スロー)
        if (timer.isTimeScaleMode && timer.timeScale > 0)
        {   // フレームレートを再計算し早送りやスローモーション
            TargetFPS = (int)(60 / timer.timeScale); // 目標のFPS(Frame Per Second, 1秒あたりのフレーム数)
            MaxAllowSkipTime = 0.2; // フレームスキップする最大間隔（秒）。これ以上の間隔が空いた場合はスキップせずに処理落ちにする。
            IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // フレーム間のTick数。1Tick = 100ナノ秒 = 1/10000000秒
            MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
        }

        // ★垂直同期がDX設定で効いているならDXライブラリにWait処理を任せられる(フレームスキップだけ自分でやる)
        if (GetWaitVSyncFlag() == TRUE && timer.isTimeScaleMode == false)
        {   // ★フレームスキップとは描画処理が重い時にパラパラ漫画を1枚飛ばすか?
            if (EnableFrameSkip)
            {   // ★余った時刻 = 次のパラパラ予定時刻 - 現在の時刻
                long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
                if (waitTicks < 0) // 目標時刻をオーバーしている
                {   //★あまり漫画のパラパラページ数を飛ばすとキャラがワープして見えるので限度をつけてる
                    if (skipCount < MaxAllowSkipCount) // 連続フレームスキップ数が最大スキップ数を超えていなければ
                    {
                        skipCount++; // フレームスキップ（描画処理を飛ばす）
                    }
                    else
                    {   // 最大スキップ数を超えてるので、フレームスキップしないで描画
                        nextFrameTicks = timer.GetElapsedTicks();
                        GameDraw(game); // ★限度越えでスロー描画処理に切替え
                    }
                }
                else
                {   // 目標時刻OKなのでフレームスキップしないで描く
                    // ★DXライブラリが自動で液晶の60Hzとタイミング合わせて描画
                    GameDraw(game); // 描画処理
                }
                // 次のパラパラ予定時刻はIntervalTicks(単位:100ナノ秒)あと
                nextFrameTicks += IntervalTicks;
            }
            else
            {   // ここのelseは何があってもフレームスキップしない設定の時に来る
                GameDraw(game); // ★スロー描画処理
            }
        }
        else
        {   // ★垂直同期がDX設定で【効いてない】ならWait処理を自力でやる(フレームスキップも自分でやる)
            // ↓こちらはフレームスキップ処理(waitTicks = 次のパラパラ予定時刻 - 現在の時刻)
            long waitTicks = nextFrameTicks - timer.GetElapsedTicks(); // 余った時間（待機が必要な時間）
            if (EnableFrameSkip && waitTicks < 0)
            {   // あまり漫画のパラパラページ数を飛ばすとキャラがワープして見えるので限度をつけてる
                if (skipCount < MaxAllowSkipCount)
                {
                    skipCount++; // フレームスキップ（描画処理を飛ばす）
                }
                else
                {   // 次のパラパラ予定時刻を現時刻に設定するので次も絶対遅れてwaitTicks < 0になる
                    nextFrameTicks = timer.GetElapsedTicks();
                    GameDraw(game); //遅れつつもスローモーションで描いてゆく設定の時はここ
                }
            }
            else
            {   // ★自力でWait処理
                if (waitTicks > 20000) // あと2ミリ秒以上待つ必要がある
                {   // ★自作TimeクラスのSleepで一定時間プログラム休止
                    // https://marycore.jp/prog/objective-c/sleep-process/#sleep_for
                    // Sleepは指定した時間でピッタリ戻ってくるわけではないので、
                    // 余裕を持って、「待たなければならない時間-2ミリ秒」Sleepする
                    int waitMillsec = (int)(waitTicks / 10000) - 2;
                    timer.SleepForMilliSec(waitMillsec);
                }

                // 時間が来るまで何もしないループを回して待機する
                while (timer.GetElapsedTicks() < nextFrameTicks)
                {   // 所定の時間になるまで空ループ
                }

                GameDraw(game); // 所定の時間になったら描画処理
            }
            // 次のパラパラ予定時刻はIntervalTicks(単位:100ナノ秒)あと
            nextFrameTicks += IntervalTicks;
        }
    }

    // キー入力待ちをする
    WaitKey();

    // ＤＸライブラリの後始末
    DxLib::DxLib_End();

    // ソフトの終了
    return 0;
}
