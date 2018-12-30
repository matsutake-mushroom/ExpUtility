#include "utils.h"

using namespace std;
/*******************
* sound unit
* puretone, silence, click
*******************/

SoundUnit::SoundUnit(int len) {
	length = len;//ms
}
void SoundUnit::writeSequenceStep(stringstream &output, int step, bool isEnd) {
	string comma = string(",");
	output << "STEP#" << step << "=";
	output << showpoint << (double)length << "E-03" << comma;//時間
	output << string((isEnd) ? "STOP" : "CONT") << comma;//最後か継続か
	output << "OFF" << comma;//オートホールド(とは？)
	output << 1 << comma;//ステップコード(とは？)
	output << "OFF" << comma << 1 << comma;//ステートブランチステップする？[ON/OFF]、そのステップ値
	output << "OFF" << comma << 1 << comma;//イベントブランチステップする？[ON/OFF]、そのステップ値
	output << ((isEnd)?"ON":"OFF") << comma << 1 << comma; //ジャンプステップする？[ON/OFF]、そのステップ値
	output << "INF" << comma << 1 << comma;//ジャンプ回数指定する？[INF/ON]、ジャンプ回数[ONのとき](0だとコンパイルされない！！！！)
	output << "OFF" << comma << 0.0;//終了位相指定する？[ON/OFF]、その位相
	output << endl;
}

vector<map<pair<double, int>, double>> PureTone::sound_pressure_map_vector;//staticの実体
std::map<std::pair<double, int>, double> PureTone::default_sound_pressure_map;//実体, SPM[0]
bool PureTone::sound_pressure_map_is_initialized = false;

void PureTone::initSoundPressureMap(){
	auto it = sound_pressure_map_vector.begin();
	sound_pressure_map_vector.insert(it, default_sound_pressure_map);
	sound_pressure_map_is_initialized = true;
}

PureTone::PureTone(double kHz, int dB, int len) : SoundUnit(len) {
	//use default SPM
	if (!sound_pressure_map_is_initialized) {
		initSoundPressureMap();
	}

	frequency = kHz;
	name = to_string(frequency) + " kHz";
	voltage = sound_pressure_map_vector[0][{kHz, dB}];
}

PureTone::PureTone(int SoundMapID, double kHz, int dB, int len) : SoundUnit(len) {
	//use registered SPM
	frequency = kHz;
	name = to_string(frequency) + " kHz";

	if (SoundMapID > sound_pressure_map_vector.size()) {
		voltage = sound_pressure_map_vector[0][{kHz, dB}];//use default
	}
	else {
		voltage = sound_pressure_map_vector[SoundMapID][{kHz, dB}];
	}
}

void PureTone::writeSequenceChannel(stringstream &output, int step, int channel) {
	string comma = ",";
	output << "CHAN#" << step << "#" << channel << "=";
	output << "SIN" << comma;//波形
	output << "0" << comma;//任意波番号
	output << "NORM" << comma;//極性(NORMal, INVert)
	output << "FS" << comma;//波形増幅(PFS->正、FS->正負, MFS->負
	output << "OFF" << comma;//方形波拡張(OFF/ON)

	output << showpoint << (double)(frequency*1000.0) << comma;//周波数(実数)
	output << "CONS" << comma;//動作(KEEP/CONStant/SWEep)

	output << showpoint << (double)voltage << comma;//振幅(real number)
	output << "CONS" << comma;//動作(KEEP/CONStant/SWEep)

	output << 0.00 << comma;//DC offset
	output << "CONS" << comma;//動作

	output << 0.00 << comma;//Phase
	output << "CONS" << comma;//dousa

	output << 50.0 << comma;//Duty[%],real number
	output << "CONS" << endl;//dousa
							 //CH2 for debug
	output << "CHAN#" << step << "#" << 2 << "=SIN,0,NORM,FS,OFF,1000.00000000,CONS,1.0000E-01,CONS,0.0000E+00,CONS,0.000,CONS,50.0000,CONS" << endl;
}

int PureTone::addSoundPressureMap(){
	if (!sound_pressure_map_is_initialized) {
		initSoundPressureMap();
	}
	std::map<std::pair<double, int>, double> new_member;
	sound_pressure_map_vector.push_back(new_member);
	auto itr = find(sound_pressure_map_vector.begin(), sound_pressure_map_vector.end(), new_member);
	return std::distance(sound_pressure_map_vector.begin(), itr);
}

void PureTone::soundCalibration(double kHz, int dB, double voltage){
	if (!sound_pressure_map_is_initialized) {
		initSoundPressureMap();
	}
	sound_pressure_map_vector[0][{kHz, dB}] = voltage;
}

void PureTone::soundCalibration(int soundMapID, double kHz, int dB, double voltage) {
	int id = soundMapID;
	if (soundMapID > sound_pressure_map_vector.size() || soundMapID < 0) {
		id = 0;
	}
	sound_pressure_map_vector[id][{kHz, dB}] = voltage;
}

void PureTone::soundCalibrationFromCSV(string filename){
	/**********************
	* 用意するcsvの書式
	*　一行目：項目名
	*　二行目以降：(double)kHz, (int)dB, (double)voltageの順
	*　四列目以降は備考を書いてよい
	***********************/
	CSV csvfile(filename);
	for (int i = 1; i < csvfile.Row; ++i) {
		soundCalibration(stod(csvfile[i][0]), stoi(csvfile[i][1]), stod(csvfile[i][2]));
	}
}

void PureTone::soundCalibrationFromCSV(int soundMapID, string filename) {
	int id = soundMapID;
	if (soundMapID > sound_pressure_map_vector.size() || soundMapID < 0) {
		id = 0;
	}

	CSV csvfile(filename);
	for (int i = 1; i < csvfile.Row; ++i) {
		soundCalibration(id, stod(csvfile[i][0]), stoi(csvfile[i][1]), stod(csvfile[i][2]));
	}
}

Click::Click(int len) : SoundUnit(len) {
	name = "Click";
	voltage = 15.0;//初期値
}

void Click::writeSequenceChannel(stringstream &output, int step, int channel) {//方形波
	string comma = ",";
	output << "CHAN#" << step << "#" << channel << "=";
	output << "SQU" << comma;//波形
	output << "0" << comma;//任意波番号
	output << "NORM" << comma;//極性(NORMal, INVert)
	output << "FS" << comma;//波形増幅(PFS->正、FS->正負, MFS->負
	output << "OFF" << comma;//方形波拡張(OFF/ON)

	output << showpoint << (double)(1.0) << comma;//周波数(実数)
	output << "CONS" << comma;//動作(KEEP/CONStant/SWEep)
	
	output << showpoint << (double)voltage << comma;//振幅(real number)
	output << "CONS" << comma;//動作(KEEP/CONStant/SWEep)

	output << 0.00 << comma;//DC offset
	output << "CONS" << comma;//動作

	output << 0.00 << comma;//Phase
	output << "CONS" << comma;//動作

	output << 0.025 << comma;//Duty[%],real number
	output << "CONS" << endl;//動作
							 //CH2 for debug
	output << "CHAN#" << step << "#" << 2 << "=SIN,0,NORM,FS,OFF,1000.00000000,CONS,1.0000E-01,CONS,0.0000E+00,CONS,0.000,CONS,50.0000,CONS" << endl;
}


Silence::Silence(int len) : SoundUnit(len) {
	name = "Silence";
}
void Silence::writeSequenceChannel(stringstream &output, int step, int channel) {//音なし
	string comma = ",";
	output << "CHAN#" << step << "#" << channel << "=";
	output << "SIN" << comma;//波形
	output << "0" << comma;//任意波番号
	output << "NORM" << comma;//極性(NORMal, INVert)
	output << "FS" << comma;//波形増幅(PFS->正、FS->正負, MFS->負
	output << "OFF" << comma;//方形波拡張(OFF/ON)

	output << showpoint << (double)(1000) << comma;//周波数(実数)
	output << "CONS" << comma;//動作(KEEP/CONStant/SWEep)

	output << "0.0000E+00" << comma;//振幅(real number)
	output << "CONS" << comma;//動作(KEEP/CONStant/SWEep)

	output << "0.0000E+00" << comma;//DC offset
	output << "CONS" << comma;//動作

	output << "0.0000E+00" << comma;//Phase
	output << "CONS" << comma;//動作

	output << 50.0 << comma;//Duty[%],real number
	output << "CONS" << endl;//動作
	//CH2 for debug
	output << "CHAN#" << step << "#" << 2 << "=SIN,0,NORM,FS,OFF,1000.00000000,CONS,1.0000E-01,CONS,0.0000E+00,CONS,0.000,CONS,50.0000,CONS" << endl;
}

/*******************
* sound vector
* to generate WF1974 sequence file
*******************/

string SoundVector::createSequenceCommand() {
	string sequenceFile;
	string sequenceCommand;
	int digit = 0;

	sequenceFile += "[FILE]\nVERSION=\"1.00\"\n[SYSTEM]\nMODEL=\"WF1974\"\nNCHAN=2\nVERSION=\"1.00\"\n[DATA]\n";
	sequenceFile += "SEQ=1,SSYN,OFF,STAR,POS\n";
	sequenceFile += createSequenceDataString();

	digit = to_string(sequenceFile.length()).size();
	sequenceCommand = ":SOUR1:SEQ:STAT ON;"; //CH1をシーケンスモードへ
	sequenceCommand += ":TRAC:SEQ 0,\"TEST\",#";//SEQデータ入出力。メモリ(0~10)、名前、データ「」
	sequenceCommand += to_string(digit) + to_string(sequenceFile.length() + 1) + "\n";
	sequenceCommand += sequenceFile;
	return sequenceCommand;
}

string SoundVector::createSequenceDataString() {
	stringstream ss;
	int channel = 1;
	int step = 1;

	ss << "STEP#0 = 1.0000E+00, CONT, OFF, 1, OFF, 1, OFF, 1, OFF, 1, INF, 1, OFF, 0.000\n";
	ss << "CHAN#0#1 = DC, 0, NORM, FS, OFF, 1000.00000000, CONS, 0.0000E+00, CONS, 0.0000E+00, CONS, 0.000, CONS, 50.0000, CONS\n";
	ss << "CHAN#0#2 = SIN, 0, NORM, FS, OFF, 1000.00000000, CONS, 1.0000E-01, CONS, 0.0000E+00, CONS, 0.000, CONS, 50.0000, CONS\n";

	for (auto i = sequence.begin(); i<sequence.end(); ++i) {
		(*i)->writeSequenceStep(ss, step, ((i+1) == sequence.end()) ? true : false);
		(*i)->writeSequenceChannel(ss, step, channel);
		++step;
	}
	return ss.str();
}
void SoundVector::resetSequence() {
	for (auto i = sequence.begin(); i<sequence.end(); ++i) {
		delete (*i);
	}
	sequence.clear();
}
void SoundVector::createRhythmSequence() {
	/*
	*   平均：500ms間隔(2Hz)
	*   1Hz, 2Hz, 4Hz, 8Hzのリズム(f)
	*   1/1, 1/2, 1/4, 1/8 のパワー←？？
	*   8    4    2    1  の比←個数にしていいの？？？
	*	合計15なので7倍しとく
	*	56,	28,	14,	7 の計105
	*   8s   2s   1/2s 1/8s -> 10+3/8 s (83/8)????
	*/
	int clicktime = 40;//<125
	int silenceArray[105];
	resetSequence();
	for (int i = 0; i<56; ++i) {
		silenceArray[i] = 1000 - clicktime;
	}
	for (int i = 56; i<84; ++i) {
		silenceArray[i] = 500 - clicktime;
	}
	for (int i = 84; i<98; ++i) {
		silenceArray[i] = 250 - clicktime;
	}
	for (int i = 98; i < 105; ++i) {
		silenceArray[i] = 125 - clicktime;
	}
	//shuffle
	for (int times = 0; times<100; ++times) {
		for (int i = 0; i<105; ++i) {
			int j = rnd() % 105;
			int t = silenceArray[i];
			silenceArray[i] = silenceArray[j];
			silenceArray[j] = t;
		}
	}

	for (int i = 0; i<105; ++i) {
		sequence.push_back(new Click(clicktime));
		sequence.push_back(new Silence(silenceArray[i]));
	}

}

void SoundVector::createRegularRhythmSequence() {
	int clicktime = 40;
	int Hz = 2;
	resetSequence();
	sequence.push_back(new Click(clicktime));
	sequence.push_back(new Silence((1000/Hz)-clicktime));

}

void SoundVector::createRandomRhythmSequence() {
	/*
	*   平均：500ms間隔(2Hz)
	*   1Hz, 2Hz, 4Hz, 8Hzのリズム(f)
	*   25こずつ合計100にしとく
	*/
	int clicktime = 40;//<125
	int silenceArray[100];
	resetSequence();
	for (int i = 0; i<25; ++i) {
		silenceArray[i] = 1000 - clicktime;
	}
	for (int i = 25; i<50; ++i) {
		silenceArray[i] = 500 - clicktime;
	}
	for (int i = 50; i<75; ++i) {
		silenceArray[i] = 250 - clicktime;
	}
	for (int i = 75; i < 100; ++i) {
		silenceArray[i] = 125 - clicktime;
	}
	//shuffle
	for (int times = 0; times<100; ++times) {
		for (int i = 0; i<100; ++i) {
			int j = rnd() % 100;
			int t = silenceArray[i];
			silenceArray[i] = silenceArray[j];
			silenceArray[j] = t;
		}
	}

	for (int i = 0; i<100; ++i) {
		sequence.push_back(new Click(clicktime));
		sequence.push_back(new Silence(silenceArray[i]));
	}

}

void SoundVector::createTestSequence() {
	resetSequence();
	sequence.push_back(new PureTone(1, 60, 1000));
	sequence.push_back(new PureTone(2, 60, 1000));
	sequence.push_back(new PureTone(1, 60, 1000));
	sequence.push_back(new PureTone(2, 60, 1000));
	sequence.push_back(new PureTone(1, 60, 1000));
	sequence.push_back(new PureTone(2, 60, 1000));
	sequence.push_back(new PureTone(1, 60, 1000));
	sequence.push_back(new PureTone(2, 60, 1000));
	sequence.push_back(new PureTone(1, 60, 1000));
	sequence.push_back(new PureTone(2, 60, 1000));
}

void SoundVector::createPitchSequence(int id = 0) {
	/*
	*   500ms間隔(2Hz)
	*   24(C), 27(D), 30(E),36(G),40(A), 48(C) kHzの五音音階
	*   最小公倍数 = 1080
	*   45, 40, 36, 30, 27, 22.5 個ずつ計200.5個(400STEP)
	*   23, 20, 18, 15, 13, 11　個ずつ計 100 個
	*
	*/
	int pitchLength = 400;
	int interval = 100;
	double pitchArray[100];
	resetSequence();

	for (int i = 0; i<23; ++i) {
		pitchArray[i] = 24;
	}
	for (int i = 23; i<43; ++i) {
		pitchArray[i] = 27;
	}
	for (int i = 43; i<61; ++i) {
		pitchArray[i] = 30;
	}
	for (int i = 61; i<76; ++i) {
		pitchArray[i] = 36;
	}
	for (int i = 76; i<89; ++i) {
		pitchArray[i] = 40;
	}
	for (int i = 89; i<100; ++i) {
		pitchArray[i] = 48;
	}

	//shuffle
	for (int times = 0; times<100; ++times) {
		for (int i = 0; i<100; ++i) {
			int j = rnd() % 100;
			double t = pitchArray[i];
			pitchArray[i] = pitchArray[j];
			pitchArray[j] = t;
		}
	}

	for (int i = 0; i<100; ++i) {
		sequence.push_back(new PureTone(id, pitchArray[i], 60, pitchLength));
		sequence.push_back(new Silence(interval));
	}
}

void SoundVector::createRandomPitchSequence(int id = 0) {
	/*
	*   500ms間隔(2Hz)
	*   24(C), 27(D), 30(E),36(G),40(A), 48(C) kHzの五音音階
	*   17個ずつ102個の音列にする
	*
	*/
	int pitchLength = 400;
	int interval = 100;
	double pitchArray[102];
	resetSequence();

	for (int i = 0; i<17; ++i) {
		pitchArray[i] = 24;
	}
	for (int i = 17; i<34; ++i) {
		pitchArray[i] = 27;
	}
	for (int i = 34; i<51; ++i) {
		pitchArray[i] = 30;
	}
	for (int i = 51; i<68; ++i) {
		pitchArray[i] = 36;
	}
	for (int i = 68; i<85; ++i) {
		pitchArray[i] = 40;
	}
	for (int i = 85; i<102; ++i) {
		pitchArray[i] = 48;
	}

	//shuffle
	for (int times = 0; times<100; ++times) {
		for (int i = 0; i<102; ++i) {
			int j = rnd() % 102;
			double t = pitchArray[i];
			pitchArray[i] = pitchArray[j];
			pitchArray[j] = t;
		}
	}

	for (int i = 0; i<102; ++i) {
		sequence.push_back(new PureTone(id, pitchArray[i], 60, pitchLength));
		sequence.push_back(new Silence(interval));
	}
}
void SoundVector::createRegularPitchSequence(int id = 0) {
	/*
	*   500ms間隔(2Hz)
	*   24(C), 27(D), 30(E),36(G),40(A), 48(C) kHzの五音音階
	*   とりあえず上昇音階にする
	*
	*/
	int pitchLength = 400;
	int interval = 100;

	resetSequence();
	sequence.push_back(new PureTone(id, 24, 60, pitchLength));
	sequence.push_back(new Silence(interval));
	sequence.push_back(new PureTone(id, 27, 60, pitchLength));
	sequence.push_back(new Silence(interval));
	sequence.push_back(new PureTone(id, 30, 60, pitchLength));
	sequence.push_back(new Silence(interval));
	sequence.push_back(new PureTone(id, 36, 60, pitchLength));
	sequence.push_back(new Silence(interval));
	sequence.push_back(new PureTone(id, 40, 60, pitchLength));
	sequence.push_back(new Silence(interval));
	sequence.push_back(new PureTone(id, 48, 60, pitchLength));
	sequence.push_back(new Silence(interval));
}
