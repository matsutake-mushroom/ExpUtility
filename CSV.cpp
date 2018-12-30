#include "utils.h"
using namespace std;
CSV::CSV(){
	Row = 0;
	Column = 0;
}

CSV::CSV(string filename){
	read_csv(filename);
}

CSV::~CSV(){
}

vector<string> CSV::split(string& line, char delimiter) {
	vector<string> returnVector;
	string temp;
	stringstream ss(line);
	while (getline(ss, temp, delimiter)) {
		returnVector.push_back(temp);
	}
	return returnVector;
}

void CSV::updateSize(){
	Row = data.size();
	if(Row>0){
		Column = data[0].size();
	}
}

void CSV::read_csv(string filename){
	string buffer;
	ifstream inputfile(filename);
	if (!inputfile) {
		return;//open Error
	}
	while (getline(inputfile, buffer)) {
		data.push_back(split(buffer, ','));
	}
	updateSize();
}

void CSV::write_csv(string filename){
	ofstream outputfile(filename);
	if (!outputfile) {
		return;//open Error
	}
	for (auto i = data.begin(); i < data.end(); ++i) {
		for (auto j = (*i).begin(); j < (*i).end(); ++j) {
			outputfile << (*j) << ",";
		}
		outputfile << endl;
	}
}

vector<string>& CSV::operator[](int i) {
	return data[i];
}