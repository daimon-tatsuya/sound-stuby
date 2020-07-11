#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <iostream> 
using namespace std;
#pragma comment(lib, "winmm.lib")
// 波形データを用意
unsigned char wave[44100];
//関数はスタックは、analyze:stacksize '16384'バイトのため、ヒープへ
 
int main(void) {
	// オーディオデバイスのハンドル
	HWAVEOUT hWaveOut;
	// WAVEファイルのフォーマット情報を用意
	// https://msdn.microsoft.com/ja-jp/library/cc371559.aspx
	WAVEFORMATEX waveFormatex;

	waveFormatex.wFormatTag = WAVE_FORMAT_PCM;

	waveFormatex.nChannels = 1; // モノラル:1 ステレオ:2

	waveFormatex.wBitsPerSample = 8; // 量子化ビット数

	//ここを変えると音の高さが変わる
	waveFormatex.nSamplesPerSec = 44100; // 標本化周波数

    // データの最小範囲(バイト単位)
	waveFormatex.nBlockAlign =waveFormatex.nChannels * waveFormatex.wBitsPerSample / 8;

	
	// 平均転送ビット数
	waveFormatex.nAvgBytesPerSec

	 = waveFormatex.nSamplesPerSec * waveFormatex.nBlockAlign;

   /*
   ド  261.626Hz
   レ  293.665Hz
   ミ  329.628Hz
   ファ349.228Hz
   ソ  391.995Hz
   ラ  440.000Hz
   シ  493.883Hz
   ド  523.251Hz
   */
	float freq[8]{ 261.626, 293.665, 329.628,349.228,
		391.995, 440.000,493.883, 523.251 };
	
	//波形を出力するオーディオデバイスを開く
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormatex, 0, 0, CALLBACK_NULL);

	int len = 44100 / freq[1];
	for (int i = 0; i < 44100; i++)
	{
		if (i % len < len / 2)
		{wave[i] = (128 + 64);}

		else
		{wave[i] = (128 - 64);}
			
	}
//	cout << "矩形波で 440Hz (ラ) を再生！！" << endl;
	
	// 波形データの情報と再生フラグの設定
	int waveLength = 44100;
	WAVEHDR whdr;
	whdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	whdr.dwLoops = 1;
	whdr.lpData = (LPSTR)wave;
	whdr.dwBufferLength = waveLength;

	// オーディオデバイスのデータブロック(バッファ)を初期化
	waveOutPrepareHeader(hWaveOut, &whdr, sizeof(WAVEHDR));

	// 波形データをオーディオデバイスに書き込み。書き込み後、直ちに波形は再生される。
	waveOutWrite(hWaveOut, &whdr, sizeof(WAVEHDR));

	// 1秒待つ
	Sleep(1000);

	// オーディオデバイスを閉じる
	waveOutClose(hWaveOut);
	return 0;
}