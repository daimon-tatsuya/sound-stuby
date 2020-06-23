#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <iostream> 
using namespace std;
#pragma comment(lib, "winmm.lib")
// �g�`�f�[�^��p��
unsigned char wave[44100];
//�֐��̓X�^�b�N�́Aanalyze:stacksize '16384'�o�C�g�̂��߁A�q�[�v��
 
int main(void) {
	// �I�[�f�B�I�f�o�C�X�̃n���h��
	HWAVEOUT hWaveOut;
	// WAVE�t�@�C���̃t�H�[�}�b�g����p��
	// https://msdn.microsoft.com/ja-jp/library/cc371559.aspx
	WAVEFORMATEX waveFormatex;
	waveFormatex.wFormatTag = WAVE_FORMAT_PCM;

	waveFormatex.nChannels = 1; // ���m����:1 �X�e���I:2

	waveFormatex.wBitsPerSample = 8; // �ʎq���r�b�g��

	//440hz?
	waveFormatex.nSamplesPerSec = 44100; // �W�{�����g��

    // �f�[�^�̍ŏ��͈�(�o�C�g�P��)
	waveFormatex.nBlockAlign =waveFormatex.nChannels * waveFormatex.wBitsPerSample / 8;

	waveFormatex.nAvgBytesPerSec = // ���ϓ]���r�b�g��

	waveFormatex.nSamplesPerSec * waveFormatex.nBlockAlign;

   

	//�g�`���o�͂���I�[�f�B�I�f�o�C�X���J��
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormatex, 0, 0, CALLBACK_NULL);
	int len = 44100 / 440;
	for (int i = 0; i < 44100; i++) {
		if (i % len < len / 2)
			wave[i] = (128 + 64);
		else
			wave[i] = (128 + 64);
	}
	cout << "��`�g�� 440Hz (��) ���Đ��I�I" << endl;
	
	// �g�`�f�[�^�̏��ƍĐ��t���O�̐ݒ�
	int waveLength = 44100;
	WAVEHDR whdr;
	whdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	whdr.dwLoops = 1;
	whdr.lpData = (LPSTR)wave;
	whdr.dwBufferLength = waveLength;

	// �I�[�f�B�I�f�o�C�X�̃f�[�^�u���b�N(�o�b�t�@)��������
	waveOutPrepareHeader(hWaveOut, &whdr, sizeof(WAVEHDR));

	// �g�`�f�[�^���I�[�f�B�I�f�o�C�X�ɏ������݁B�������݌�A�����ɔg�`�͍Đ������B
	waveOutWrite(hWaveOut, &whdr, sizeof(WAVEHDR));

	// 1�b�҂�
	Sleep(1000);

	// �I�[�f�B�I�f�o�C�X�����
	waveOutClose(hWaveOut);
	return 0;
}