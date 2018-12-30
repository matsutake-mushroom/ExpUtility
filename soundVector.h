#pragma once
#include "..\common.h"

/*******************
* sound unit
* puretone, silence, click
*******************/

class SoundUnit {
protected:
public:
	std::string name;//"10kHz"
	int length;//ms
public:
	SoundUnit(int len);
	void writeSequenceStep(std::stringstream &output, int step, bool isEnd);
	virtual void writeSequenceChannel(std::stringstream &output, int step, int channel) = 0;//pure virtual function
};

class PureTone : public SoundUnit {
private:
	double frequency;//30[kHz]
	int amplitude;//40[dB]
	double voltage;//0.25[Vp-p]
	static bool sound_pressure_map_is_initialized;
	static std::map<std::pair<double, int>, double> default_sound_pressure_map;
	static void initSoundPressureMap();
public:
	static std::vector<std::map<std::pair<double, int>, double>> sound_pressure_map_vector;//map[{(double)kHz, (int)dB}] = (double)Vp-p; ŽÀ‘Ì‚ÍŠO‚Ì‚Ç‚±‚©
	PureTone(double kHz, int dB, int len);
	PureTone(int SoundMapID, double kHz, int dB, int len);
	void writeSequenceChannel(std::stringstream &output, int step, int channel);
	static int addSoundPressureMap();
	static void soundCalibration(double kHz, int dB, double voltage);
	static void soundCalibration(int soundMapID, double kHz, int dB, double voltage);
	static void soundCalibrationFromCSV(std::string filename);
	static void soundCalibrationFromCSV(int soundMapID, std::string filename);
};



class Click : public SoundUnit {
	double voltage;
public:
	Click(int len);
	void writeSequenceChannel(std::stringstream &output, int step, int channel);
};


class Silence : public SoundUnit {
public:
	Silence(int len);
	void writeSequenceChannel(std::stringstream &output, int step, int channel);
};
/*******************
* sound vector
* to generate WF1974 sequence file
*******************/

class SoundVector {
private:
	std::ofstream outputfile;
	std::random_device rnd;//for shuffle
public:
	std::vector<SoundUnit*> sequence;
	bool loop;
	int length;

	std::string createSequenceCommand();
	std::string createSequenceDataString();
	void resetSequence();
	void createRhythmSequence();
	void createRegularRhythmSequence();
	void createRandomRhythmSequence();
	void createTestSequence();
	void createPitchSequence(int soundMapID);
	void createRandomPitchSequence(int soundMapID);
	void createRegularPitchSequence(int soundMapID);
};

