#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<math.h>
#include<Windows.h>
#include<ctime>


using namespace std;

struct Condition
{
	Condition(bool rain, bool fog, bool night, bool snow, int roadquality, int temperature);
	bool isRainy;
	bool isFoggy;
	bool isNight;
	bool isSnowy;
	int roadQuality;
	int tempr;
};

Condition* generateWeather();

class Engine
{
public:
	Engine();
	void changeSpeed(int kmh);
	void start();
	vector<int> status();

private:
	int enginePower;
	int fuel;
	int oil;
	bool isOn = false;

};

class DisplayPanel
{
public:
	void displayInitialize();
	void displayShow(string info);
	void engineInfo(vector<string> info);
	void weatherInfo(string info);
	void displayStatus(vector<int> status);
private:
};

class Lights
{
public:
	void changeLights(int value);
	int status();
private:
	enum lights {Far, Close, Off};
	lights forwardlights = Off;
};

class WindshieldWiper
{
public:
	void wipeWindow();
	int status();
private:
	bool isOn = false;
};

class Cooler
{
public:
	void changeStatus(int value);
	int status();
private:
	enum CoolerStatus { Cooling, Heating, Off };
	CoolerStatus stat = Off;
};

class Sensor
{
public:
	void activate();
	virtual vector<int> showCondition() = 0;
	virtual void scan(Condition* cond) = 0;

private:
	bool isOn;
	

};

class WeatherSensor : Sensor
{
public:
	vector<int> showCondition() override;
	void scan(Condition* cond) override;

private:
	int weatherType;
	bool isNight;
	int temperature;
};

class RoadSensor : Sensor
{
public:
	vector<int> showCondition() override;
	void scan(Condition* cond) override;
private:
	
	int roadcondition;
	bool isSlipperyRoad;

};

class GPS
{
public:
	string showRoadInfo();

private:
	int distance;
	void buildRoad();
	bool Isloaded;
};

class ControlPanel
{
public:
	virtual string CommandsInterpret(string cmds) = 0;
	string input();
private:
	string Commands;
	
};

class KeyboardControl : public ControlPanel
{
public:
	string CommandsInterpret(string cmds) override;

private:
	
};

class VoiceControl : public ControlPanel
{
public:
	string CommandsInterpret(string cmds) override;
private:

};

class MicroclimateSystem
{
public:
	MicroclimateSystem()
	{

	}
	MicroclimateSystem(Condition* cond);
	string showWeather();
	string showStatus();
	vector<int> devicesStatus();
	string OnOffCooler();
	void controller();

private:
	Lights lights;
	WindshieldWiper wWiper;
	Cooler cooler;
	WeatherSensor weathersensor;
	list<string> status;
	bool coolerWork = false;
	vector<bool> estimateWeather();
	int estimateVisibility();
};

class BoardComputer
{
public:
	BoardComputer(Condition* cond);
	void Initialize();
	
private:
	bool isOn;
	DisplayPanel displayPanel;
	GPS gps;
	Engine engine;
	RoadSensor roadSensor;
	MicroclimateSystem microclimatesytem;
	KeyboardControl keyboardControl;
	VoiceControl voiceControl;
	string commands;
	void automaticDecision();
	vector<string> engineStatus();
	void execute();
	bool safetyCondition();
};


