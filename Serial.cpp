#pragma once
#include "Serial.h"

Serial::Serial(){
	hComm = CreateFile(
		"COM3",                       /* �V���A���|�[�g�̕����� */
		GENERIC_READ | GENERIC_WRITE, /* �A�N�Z�X���[�h */
		0,                            /* ���L���[�h */
		NULL,                         /* �Z�L�����e�B���� */
		OPEN_EXISTING,                /* �쐬�t���O */
		FILE_ATTRIBUTE_NORMAL,        /* ���� */
		NULL                          /* �e���v���[�g�̃n���h�� */
	);

	GetCommState(hComm, &dcb); /* DCB ���擾 */
		
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = 115200;     /* �]�����x��ݒ�*/
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

