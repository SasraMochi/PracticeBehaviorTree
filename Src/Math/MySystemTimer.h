#ifndef MYTIMER_H_
#define MYTIMER_H_

// マルチプラットフォーム対応の時刻取り扱いクラス(C++11対応なら移植容易)

#include <chrono> // 精度の高い時刻を得る(C++ならWindows,Macなど色んな環境で使える)
#include <thread> // 処理休止sleep_forするために必要
#include <vector> // リストvectorに必要
#include <map>	// 辞書型連想配列に必要
#include <memory> // shared_ptr回し読みポインタに必要
#include <string> // 文字列string型に必要
#include <sstream> // ostringstreamに必要 標準出力(ostringstreamで文字列に標準出力を)
#include <iomanip> // 時間の文字列出力put_time()に必要


#include "Singleton.h"

class MySystemTimer : public Singleton<MySystemTimer>
{
public:
	friend class Singleton<MySystemTimer>; // Singleton でのインスタンス作成は許可

	// 最初にsystem_clockとsteady_clockの両方で現在時間を取得
	// ★system_clockは【WindowなどOSの時刻(ユーザーが変更したら巻き戻しもありうる)】
	// ★steady_clockは【↑OSに依存しない時刻(不可逆なので時間計測に向いている)】
	std::chrono::system_clock::time_point systemInitTime = std::chrono::system_clock::now();
	std::chrono::steady_clock::time_point steadyInitTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point steadyNowTime = std::chrono::steady_clock::now();
	//
	std::chrono::system_clock::time_point systemTimeFromStart = UpdateSystemTimeFromStart();

	// 時刻を保管する文字列【注意】UpdateSystemTimeFromStart()呼ばないうちは最新に更新されない
	std::string timeStringSystemClock = GetTimeString("%Y年%m月%d日%H時%M分%S秒");
	float timeScale = 1.0f;//[実験機能]main.cppで画面を描く速度と連動させてスローモーションや早送りも
	bool isTimeScaleMode = false; //[実験機能]スローモーション、早送りモードをON OFF

	
	// 起動時間の記録の初期化/リセット(Initし直せば再取得もできる)
	void Init()
	{
		// 最初にsystem_clockとsteady_clockの両方で現在時間を取得(再取得も)
		systemInitTime = std::chrono::system_clock::now();
		steadyInitTime = std::chrono::steady_clock::now();
	}

	// 現時刻をOSに左右されず求める(計算結果はsystemTimeFromStartに保管)
	std::chrono::system_clock::time_point UpdateSystemTimeFromStart()
	{
		steadyNowTime = std::chrono::steady_clock::now(); //現時刻を得る(OSの時刻じゃない方)
		// 開始時のsteady_clock::nowとの差をとって、開始時のsystem_clock::nowに足す
		// [参考] https://techblog.kayac.com/steady_clock
		systemTimeFromStart =
			systemInitTime + std::chrono::duration_cast<std::chrono::seconds>(steadyNowTime - steadyInitTime);
		return systemTimeFromStart;
	}

	// 現時刻を特定の文字列フォーマットで得る(得たものはsteadyNowTimeとtimeStringSystemClockに保管)
	// 出力は"%c"ならフォーマットは[Mon Nov 27 10:58:32 2017]
	// "%Y年%m月%d日%H時%M分%S秒"なら[2020年12月11日14時30分15秒](デフォルト)
	// [フォーマット例] https://cpprefjp.github.io/reference/chrono/local_time.html
	std::string GetTimeString(const char* timeStringFormat = "%Y年%m月%d日%H時%M分%S秒")
	{
		systemTimeFromStart = UpdateSystemTimeFromStart();//現時刻をOS時刻に左右されず得る

		// 時刻タイプ型をsystem_clockのtime_point型からtime_t型に変換する。
		std::time_t timeFromStart = std::chrono::system_clock::to_time_t(systemTimeFromStart);
		// ローカルタイムを得る(ローカルタイムについては以下リンク参照)
		// https://programming.pc-note.net/c/time.html
		struct tm localTimeFromStart;
		localtime_s(&localTimeFromStart, &timeFromStart);
		//【ostringstream】は文字列ストリームに<<演算子などの方法でデータを流し込んでいく
		// https://programming-place.net/ppp/contents/cpp/library/029.html#write_to_string_stream
		std::ostringstream oss;
		//↓この一行で文字列ストリームに流し込み
		oss << std::put_time(&localTimeFromStart, timeStringFormat) << std::endl;

		timeStringSystemClock = oss.std::ostringstream::str(); //str()で文字列string化して保管
		return timeStringSystemClock; //現時刻を文字列として返す
	}


	// Initしてから現在までの経過時間を得る(単位Tick = 100ナノ秒 = 1/10000000秒)
	long GetElapsedTicks()
	{	// 時刻を更新
		UpdateSystemTimeFromStart();
		// Initしてから現在までの経過時間(ナノ秒)
		auto durationFromInit = std::chrono::duration_cast<std::chrono::nanoseconds>(steadyNowTime - steadyInitTime);
		// Tick数。1Tick = 100ナノ秒 = 1/10000000秒
		return (long)(durationFromInit.count() / 100);
	}

	// 指定ナノ秒 プログラムを休止
	void SleepForNanoSec(int waittime)
	{	// 指定ナノ秒 プログラムを休止
		std::this_thread::sleep_for(std::chrono::nanoseconds(waittime));
	}

	// 指定マイクロ秒 プログラムを休止
	void SleepForMicroSec(int waittime)
	{	// 指定ミリ秒 プログラムを休止
		std::this_thread::sleep_for(std::chrono::microseconds(waittime));
	}

	// 指定ミリ秒 プログラムを休止
	void SleepForMilliSec(int waittime)
	{	// 指定ミリ秒 プログラムを休止
		std::this_thread::sleep_for(std::chrono::milliseconds(waittime));
	}

	// 指定 秒 プログラムを休止
	void SleepForSec(int waittime)
	{	// 指定 秒 プログラムを休止
		std::this_thread::sleep_for(std::chrono::seconds(waittime));
	}

	// 指定 分 プログラムを休止
	void SleepForMinutes(int waittime)
	{	// 指定 分 プログラムを休止
		std::this_thread::sleep_for(std::chrono::minutes(waittime));
	}

protected:
	// 外部からのインスタンス作成は禁止
	MySystemTimer() {};
	//外部からのインスタンス破棄も禁止
	virtual ~MySystemTimer() {};
};

#endif
