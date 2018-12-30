#pragma once
#include "..\common.h"

class CSV{
private:
	std::vector<std::vector<std::string>> data;
	std::vector<std::string> split(std::string& line, char delimiter);
	void updateSize();
public:
	CSV();
	CSV(std::string filename);
	~CSV();
	int Row;
	int Column;

	void read_csv(std::string filename);
	void write_csv(std::string filename);
	std::vector<std::string> &operator[](int i);
};

