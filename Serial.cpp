#pragma once
#include "Serial.h"

Serial::Serial(){
	hComm = CreateFile(
		"COM3",                       /* シリアルポートの文字列 */
		GENERIC_READ | GENERIC_WRITE, /* アクセスモード */
		0,                            /* 共有モード */
		NULL,                         /* セキュリティ属性 */
		OPEN_EXISTING,                /* 作成フラグ */
		FILE_ATTRIBUTE_NORMAL,        /* 属性 */
		NULL                          /* テンプレートのハンドル */
	);

	GetCommState(hComm, &dcb); /* DCB を取得 */
		
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = 115200;     /* 転送速度を設定*/
	dcb.fParity = FALSE;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hComm, &dcb); /* DCB を設定 */

}

Serial::~Serial() {
	Close();
}

//シリアルでデータを転送
void Serial::Send(short data) {
	DWORD dwWritten;
	WriteFile(hComm, &data, sizeof(short), &dwWritten, NULL);
}

//シリアルポートを閉じる
void Serial::Close() {
	CloseHandle(hComm);
}

