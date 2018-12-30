#pragma once
#include "..\common.h"

class WF1974
{
private:
	int serialNumber;
	ViStatus status;
	ViChar rsc[256];
	ViUInt32 count_WF;
	ViSession defaultRm, instr;
	std::ifstream inputfile;
	std::ofstream outputfile;

	void open();
	void close();

	class WF1974_Channel{
	private:
		WF1974 *parent;
		int number;//1 or 2;
	public:
		WF1974_Channel(WF1974* _parent, int channel_number);
		~WF1974_Channel();
		void ON();
		void OFF();
	};

	class WF1974_Sequence {
	private:
		WF1974 *parent;
	public:
		WF1974_Sequence(WF1974* _parent);
		~WF1974_Sequence();
		void reset();
		void start();
		void stop();
		void immidiate_stop();
		void compile();
		void sendfile(std::string filename);
	};

public:
	WF1974();
	WF1974(int serial);
	~WF1974();

	WF1974_Sequence sequence = WF1974_Sequence(this);
	WF1974_Channel ch1 = WF1974_Channel(this, 1);
	WF1974_Channel ch2 = WF1974_Channel(this, 2);

	void resetSerial(int number);

	void connect(int serial);

	void send(std::string msg);

	void disconnect();

};

