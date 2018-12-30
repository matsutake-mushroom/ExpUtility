#include "utils.h"


void WF1974::open() {
	if (viOpenDefaultRM(&defaultRm) < VI_SUCCESS) {
		OutputDebugString((LPCSTR)"//error");
	}
	sprintf(rsc, "USB0::0x0D4A::0x000E::%d::INSTR", serialNumber);
	viOpen(defaultRm, rsc, VI_NO_LOCK, (ViUInt32)0, &instr);
	send("RST;CHA 1;SIG 0;CHA 2;SIG 0;");
}
void WF1974::close() {
	viClose(instr);
	viClose(defaultRm);
}


WF1974::WF1974() {//・ｽ・ｽ・ｽﾚ托ｿｽ・ｽ・ｽ・ｽ
	serialNumber = -1;//init
}

WF1974::WF1974(int serial) {
	serialNumber = serial;
	open();
}
WF1974::~WF1974() {
	close();
}

void WF1974::resetSerial(int number) {
	if (serialNumber != -1) {
		close();
	}
	serialNumber = number;
	open();
}

void WF1974::connect(int serial) {
	resetSerial(serial);
	open();
	send(":TRIG:SEL:EXEC IST; :OUTP1 OFF; :OUTP2 OFF;");
}

void WF1974::send(std::string msg) {
	msg.append("\n");
	ViBuf buf = (ViBuf)(msg.c_str());
	viWrite(instr, buf, (ViUInt32)strlen((ViPChar)buf), &count_WF);
}

void WF1974::disconnect() {
	close();
}


WF1974::WF1974_Channel::WF1974_Channel(WF1974* _parent, int channel_number){
	parent = _parent;
	number = channel_number;
}

WF1974::WF1974_Channel::~WF1974_Channel()
{
}

void WF1974::WF1974_Channel::ON(){
	std::stringstream ss;
	ss << ":OUTP" << number << " ON;"; 
	parent->send(ss.str());
}
void WF1974::WF1974_Channel::OFF(){
	std::stringstream ss;
	ss << ":OUTP" << number << " OFF;"; 
	parent->send(ss.str());
}








WF1974::WF1974_Sequence::WF1974_Sequence(WF1974* _parent) {
	parent = _parent;
}

WF1974::WF1974_Sequence::~WF1974_Sequence()
{
}

void WF1974::WF1974_Sequence::reset() {
	parent->send(":OUTP1 OFF; :OUTP2 OFF; :TRIG:SEL:EXEC IST;");
	parent->send(":RST; :TRAC:SEQ:CLE 0;");
}

void WF1974::WF1974_Sequence::start(){
	parent->send(":TRIG:SEL:EXEC STAR; :SEQ:IMM;");
}

void WF1974::WF1974_Sequence::stop(){
	parent->send(":OUTP1 OFF; :TRIG:SEL:EXEC STOP;");
}

void WF1974::WF1974_Sequence::immidiate_stop(){
	parent->send(":OUTP1 OFF; :OUTP2 OFF; :TRIG:SEL:EXEC IST;");
}

void WF1974::WF1974_Sequence::compile(){
	parent->send(":TRIG:COMP;");
}

void WF1974::WF1974_Sequence::sendfile(std::string filename){
	std::ifstream inputfile(filename);
	std::ofstream logfile("sequence_command_log.txt");
	std::string sequenceFile((std::istreambuf_iterator<char>(inputfile)), std::istreambuf_iterator<char>());
	std::string sequenceHeader;
	/*
	sequenceHeader = "[FILE]\nVERSION=\"1.00\"\n[SYSTEM]\nMODEL=\"WF1974\"\nNCHAN=2\nVERSION=\"1.00\"\n[DATA]\n";
	sequenceHeader += "SEQ=1,SSYN,OFF,STAR,POS\n";
	sequenceFile = sequenceHeader + sequenceFile;
	*/
	int digit = std::to_string(sequenceFile.length()).size();
	sequenceHeader = ":SOUR1:SEQ:STAT ON;"; //CH1・ｽ・ｽV・ｽ[・ｽP・ｽ・ｽ・ｽX・ｽ・ｽ・ｽ[・ｽh・ｽ・ｽ
	sequenceHeader += ":TRAC:SEQ 0,\"TEST\",#";//SEQ・ｽf・ｽ[・ｽ^・ｽ・ｽ・ｽo・ｽﾍ。・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ(0~10)・ｽA・ｽ・ｽ・ｽO・ｽA・ｽf・ｽ[・ｽ^・ｽu・ｽv
	sequenceHeader += (std::to_string(digit) + std::to_string(sequenceFile.length() + 1) + "\n");
	sequenceFile = sequenceHeader + sequenceFile;

	//log
	logfile << sequenceFile;

	parent->send(sequenceFile);
}
