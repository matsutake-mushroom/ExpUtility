#pragma once
#include <Windows.h>
#include <cstdio>
class Serial
{
private:
	DCB dcb;
	HANDLE hComm;
public:
	Serial(int baudrate);
	~Serial();

	//�V���A���Ńf�[�^��]��
	void Send(short data);
	int available();
	char read();
	//�V���A���|�[�g�����
	void Close();
};
