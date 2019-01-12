#pragma once
#include "Serial.h"

Serial::Serial(int baudrate){
	hComm = CreateFile(
		"COM3",                       /* �V���A���|�[�g�̕����� */
		GENERIC_READ | GENERIC_WRITE, /* �A�N�Z�X���[�h */
		0,                            /* ���L���[�h */
		NULL,                         /* �Z�L�����e�B���� */
		OPEN_EXISTING,                /* �쐬�t���O */
		FILE_ATTRIBUTE_NORMAL,        /* ���� */
		NULL                          /* �e���v���[�g�̃n���h�� */
	);

	GetCommState(hComm, &dcb); /* DCB ��擾 */
		
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = baudrate;     /* �]�����x��ݒ�*/
	dcb.fParity = FALSE;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hComm, &dcb); /* DCB ��ݒ� */

}

Serial::~Serial() {
	Close();
}

//�V���A���Ńf�[�^��]��
void Serial::Send(short data) {
	DWORD dwWritten;
	WriteFile(hComm, &data, sizeof(short), &dwWritten, NULL);
}

//�V���A���|�[�g�����
void Serial::Close() {
	CloseHandle(hComm);
}

int Serial::available()
{
	//受信データ数を調べる
	DWORD errors;
	COMSTAT comStat;
	ClearCommError(hComm, &errors, &comStat);
 
	int lengthOfRecieved = comStat.cbInQue; // 受信したメッセージ長を取得する
 
	return lengthOfRecieved;
}
 
char Serial::read()
{
	char buf; // 受信データ格納用
	DWORD numberOfRead; // 実際に受信したバイト数
 
	//データ受信
	bool result = ReadFile(hComm, &buf, 1, &numberOfRead, NULL);
	if (result == false){
		return 'a';
	}else{
		return buf;
	}
}