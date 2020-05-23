#include"Boardcomputer.h"

Condition* generateWeather()
{
	srand(time(0));
	bool snow = false;
	bool rain = false;
	bool fog = false;
	int temperature = rand() % 45 - 15;
	if (temperature < 2) snow = rand() % 2;
	else rain = rand() % 2;	
	bool night = (rand() % 100) < 33;
	if (!snow) fog = (rand() % 100) < 20;
	int roadquality = rand() % 5 + 1;
	Condition* condition = new Condition(rain, fog, night, snow, roadquality, temperature);
	return condition;
}

Condition::Condition(bool rain, bool fog, bool night, bool snow, int roadquality, int temperature)
{
	isRainy = rain;
	isFoggy = fog;
	isSnowy = snow;
	isNight = night;
	roadQuality = roadquality;
	tempr = temperature;
}

Engine::Engine()
{
	srand(time(0));
	fuel = rand() % 50 + 50;
	oil = rand() % 50 + 50;
	enginePower = 0;
}

vector<int> Engine::status()
{
	vector<int> vec(4);
	vec[0] = fuel;
	vec[1] = oil;
	vec[2] = enginePower;
	vec[3] = isOn;
	return vec;
}

void Engine::start()
{
	isOn = true;
}

void Engine::changeSpeed(int value)
{
	enginePower += 33 * value;
}

void Lights::changeLights(int value)
{
	switch (value)
	{
	case 1: forwardlights = Far;
		break;
	case 2: forwardlights = Close;
		break;
	case 3: forwardlights = Off;
		break;
	}
}

int Lights::status()
{
	int num = 0;
	switch (forwardlights)
	{
	case lights::Far: num = 1;
		break;
	case lights::Close: num = 2;
		break;
	case lights::Off: num = 0;
		break;
	default:
		break;
	}
	return num;
}

void Cooler::changeStatus(int value)
{
	switch (value)
	{
	case 1: stat = Cooling;
		break;
	case 2: stat = Heating;
		break;
	case 0: stat = Off;
		break;
	}
}

int Cooler::status()
{
	int num = 0;
	switch (stat)
	{
	case CoolerStatus::Cooling: num = 1;
		break;
	case CoolerStatus::Heating: num = 2;
		break;
	case CoolerStatus::Off: num = 0;
		break;
	}
	return num;
}

void WindshieldWiper::wipeWindow()
{
	if (!isOn) isOn = true;
	else isOn = false;
}

int WindshieldWiper::status()
{
	return isOn;
}

void Sensor::activate()
{
	isOn = true;
}

void WeatherSensor::scan(Condition* cond)
{
	isNight = cond->isNight;
	temperature = cond->tempr;
	if (cond->isRainy)
	{
		if (cond->isFoggy) weatherType = 4;
		else weatherType = 2;
	}
	else if (cond->isSnowy) weatherType = 5;
	else if (cond->isFoggy) weatherType = 3;
	else weatherType = 1;
}

vector<int> WeatherSensor::showCondition()
{
	vector<int> vec(3);
	vec[1] = isNight;
	vec[2] = temperature;
	vec[0] = weatherType;
	return vec;
}

void RoadSensor::scan(Condition* cond)
{
	roadcondition = cond->roadQuality;
}

vector<int> RoadSensor::showCondition()
{
	vector<int> vec(2);
	vec[0] = roadcondition;
	vec[1] = int(isSlipperyRoad);
	return vec;
}

string KeyboardControl::CommandsInterpret(string cmds)
{
	int num = int(cmds[0]) - 48;
	string comand;
	int spd;
	switch (num)
	{
	case 1: comand = "Start/off engine";
		break;
	case 2: comand = "Increase speed";
		break;
	case 3: comand = "Decrease speed";
		break;
	case 4: comand = "Turn on/off cooler";
		break;
	case 5: comand = "Estimate road";
		break;
	case 6: comand = "Show weather status";
		break;
	case 7: comand = "Show road status";
		break;
	case 8: comand = "Engine status";
		break;
	case 9: comand = "Show parts status";
		break;
	case 0: comand = "Turn off computer";
		break;
	default: "None";
		break;
	}
	return comand;
}

string VoiceControl::CommandsInterpret(string cmds)
{
	if (cmds == "Start/off engine") return cmds;
	if (cmds == "Increase speed") return cmds;
	if (cmds == "Decrease speed") return cmds;
	if (cmds == "Turn on/off cooler") return cmds;
	if (cmds == "Estimate road") return cmds;
	if (cmds == "Show weather status") return cmds;
	if (cmds == "Engine status") return cmds;
	if (cmds == "Show parts status") return cmds;
	if (cmds == "Turn off computer") return cmds;
	return "None";
}

string ControlPanel::input()
{
	string a;
	getline(std::cin, a);
	return a;
}

string GPS::showRoadInfo()
{
	buildRoad();
	string info;
	info += "The distance to the destination is ";
	info += to_string(distance);
	info += ".\nRoad traffic is ";
	info += Isloaded ? "low.\n\n" : "high.\n\n";
	return info;
}

void GPS::buildRoad()
{
	srand(time(0));
	distance = rand() % 300 + 100;
	Isloaded = rand() % 1;
}

void DisplayPanel::displayInitialize()
{
	cout << "Initializing computer...\n";
	Sleep(3000);
	cout << "Board computer initialized succesfully!!\n\n";
	cout << "Checking the status, parts and sensors...\n";
	Sleep(2000);
	cout << "Succesfully!\n\n";
}

void DisplayPanel::displayShow(string info)
{
	cout << info;
}

void DisplayPanel::engineInfo(vector<string> info)
{
	displayShow("Current engine status:\n");
	string status[4] = { "Fuel amount: ", "Oil amount: ", "Engine power: ", "Power: " };
	for (int i = 0; i < 4; i++)
	{
		cout << status[i] << info[i] << endl;
	}
	cout << endl;
}

void DisplayPanel::weatherInfo(string info)
{
	cout << "Estimating weather outside...\n";
	Sleep(3000);
	cout << info;
}

void DisplayPanel::displayStatus(vector<int> status)
{
	string info;
	info += "Current car status:\n";
	info += "Lights: ";
	switch (status[0])
	{
	case 0: info += "Off\n";
		break;
	case 1: info += "Far\n";
		break;
	case 2: info += "Close\n";
		break;
	}
	info += 
	info += "Cooler: ";
	switch (status[1])
	{
	case 0: info += "Off\n";
		break;
	case 1: info += "Cooling\n";
		break;
	case 2: info += "Heating\n";
		break;
	}
	info += "Windshield wiper: ";
	info += (bool(status[2])) ? "On\n" : "Off\n";
	displayShow(info);
}

vector<bool> MicroclimateSystem::estimateWeather()
{
	vector<bool> weatherType(7);
	vector<int> cond = weathersensor.showCondition();
	weatherType[0] = bool(cond[1]);
	weatherType[1] = cond[2] > 16 ? 1 : 0;
	weatherType[2] = cond[2] < 5 ? 1 : 0;
	weatherType[3] = (cond[0] == 2 || cond[0] == 4) ? 1 : 0;
	weatherType[4] = (cond[0] == 3 || cond[0] == 4) ? 1 : 0;
	weatherType[5] = (cond[0] == 5) ? 1 : 0;
	weatherType[6] = (cond[0] == 1) ? 1 : 0;
	return weatherType;
}

string MicroclimateSystem::showStatus()
{
	string stat;
	stat += "Microclimate system automaticly adapted to the current weather conditions.\n";
	for (string str : status)
	{
		stat += str + "\n";
	}
	return stat;
}

int MicroclimateSystem::estimateVisibility()
{
	int visibility = 0;
	vector<int> cond = weathersensor.showCondition();
	visibility += cond[1];
	visibility += (cond[0] == 4) ? 2 : 1;
	if (cond[0] == 1) visibility--;
	return visibility;
}

vector<int> MicroclimateSystem::devicesStatus()
{
	vector<int> stat(3);
	stat[0] = lights.status();
	stat[1] = cooler.status();
	stat[2] = wWiper.status();
	return stat;
}

void MicroclimateSystem::controller()
{
	
	
		vector<bool> weather = estimateWeather();
		if (weather[0])
		{
			lights.changeLights(2);
			status.push_back("Night outside. Close lights is being on");
		}
		if (weather[3])
		{
			wWiper.wipeWindow();
			status.push_back("Rain outside. Windshield wiper is on");
		}
		if (weather[4])
		{
			lights.changeLights(1);
			status.push_back("Fog outside. Far lights is being on");
		}
		if (weather[5])
		{
			lights.changeLights(2);
			wWiper.wipeWindow();
			status.push_back("Snow outside. Windshield wiper is on");
		}
		if (weather[1])
		{
			cooler.changeStatus(1);
			status.push_back("Hot outside. Cooler is working in cooling status");
			coolerWork = true;
		}
		if (weather[2])
		{
			cooler.changeStatus(2);
			status.push_back("Cold outside. Cooler is working in heating status");
		}
		if (estimateVisibility() == 0) status.push_back("The visiblity is good.");
		if (estimateVisibility() == 1)
		{
			string information;
			information += "The visiblity is moderate. ";
			lights.changeLights(2);
			information += "Close lights are On";
			status.push_back(information);
		}
		if (estimateVisibility() >= 2)
		{
			string information;
			information += "The visiblity is bad. ";
			lights.changeLights(2);
			information += "Far lights are On";
			status.push_back(information);
		}
}

string MicroclimateSystem::showWeather()
{
	vector<int> cond = weathersensor.showCondition();
	string result = "The weather is ";
	switch (cond[0])
	{
	case 1: result += "clear. ";
		break;
	case 2: result += "rainy. ";
		break;
	case 3: result += "foggy. ";
		break;
	case 4: result += "rainy and foggy. ";
		break;
	case 5: result += "snowy. ";
		break;
	}
	result += (bool(cond[0])) ? "It is night. " : "It is day. ";
	if (estimateVisibility() == 0) result += "The visiblity is good.\n";
	if (estimateVisibility() == 1) result += "The visiblity is moderate.\n";
	if (estimateVisibility() >= 2) result += "The visiblity is bad.\n";
	result += "Temperature outside is ";
	result += to_string(cond[2]);
	result += "\n\n";
	return result;
}

string MicroclimateSystem::OnOffCooler()
{
	string info;
	if (coolerWork)
	{
		cooler.changeStatus(0);
		info = "Cooler is offed.\n";
	}
	else {
		if (estimateWeather()[1]) cooler.changeStatus(1);
		if (estimateWeather()[1]) cooler.changeStatus(1);
		info = "Cooler is started.\n";
	}
	return info;
}

MicroclimateSystem::MicroclimateSystem(Condition* cond)
{
	weathersensor = *(new WeatherSensor);
	weathersensor.scan(cond);
}

vector<string> BoardComputer::engineStatus()
{
	vector<string> stat(4);
	stat[0] = to_string(engine.status()[0]);
	stat[1] = to_string(engine.status()[1]);
	stat[2] = to_string(engine.status()[2]);
	stat[3] = bool(engine.status()[3]) ? "On" : "Off";
	return stat;
}

BoardComputer::BoardComputer(Condition* cond)
{
	microclimatesytem = *(new MicroclimateSystem(cond));
	roadSensor = *(new RoadSensor);
	roadSensor.scan(cond);
}

bool BoardComputer::safetyCondition()
{
	bool safe = true;
	int speed = engine.status()[2] / 33;
	int roadcond = roadSensor.showCondition()[0];
	if ((speed + 30 * roadcond) == 210) safe = false;
	return safe;
}

void BoardComputer::Initialize()
{
	displayPanel.displayInitialize();
	isOn = true;
	automaticDecision();
	displayPanel.displayShow("\nPlease, choose your type of communication:\n  Press '1' for keyboard and '2' for voice controlling.\n\n");
	int a;
	std::cin >> a;
	while ((a != 1) && (a != 2))
	{
		displayPanel.displayShow("Error, choose 1 or 2");
		std::cin >> a;
	}
	if (a == 1)
	{
		displayPanel.displayShow("Your choice is keyboardcontrol\n");
		displayPanel.displayShow("Now here is a list of all keyboard buttons and their functioning:\n\n");
		displayPanel.displayShow("For 'Start/off engine' press '1'.\n");
		displayPanel.displayShow("For 'Increase speed' press '2'.\n");
		displayPanel.displayShow("For 'Decrease speed' press '3'.\n");
		displayPanel.displayShow("For 'Turn on/off cooler' press '4'.\n");
		displayPanel.displayShow("For 'Estimate road' press '5'.\n");
		displayPanel.displayShow("For 'Show weather status' press '6'.\n");
		displayPanel.displayShow("For 'Show road status' press '7'.\n");
		displayPanel.displayShow("For 'Engine status' press '8'.\n");
		displayPanel.displayShow("For 'Show parts status' press '9'.\n");
		displayPanel.displayShow("For 'Turn off computer' press '0'.\n");
		displayPanel.displayShow("What commands should I execute??\n");
		cin.ignore(255, '\n');
		commands = keyboardControl.CommandsInterpret(keyboardControl.input());
		
	}
	if (a == 2)
	{
		displayPanel.displayShow("Your choice is voicecontrol\n"
			"Here is a list of all comands, choose the one:\n"
			"'Start/off engine', 'Increase speed', 'Decrease speed',\n"
			"'Turn on/off cooler', 'Estimate road', 'Show weather status',\n"
			"'Show road status', 'Engine status', 'Show parts status'\n"
			"'Turn off computer'\n");
		displayPanel.displayShow("Input your command:\n");
		string cmnd;
		cin.ignore(255, '\n');
		commands = voiceControl.CommandsInterpret(voiceControl.input());
	}
	while (commands != "Turn off computer")
	{
		execute();
		while ((a != 1) && (a != 2))
		{
			displayPanel.displayShow("Error, choose 1 or 2");
			std::cin >> a;
		}
		if (a == 1)
		{
			displayPanel.displayShow("Input your command:\n");
			commands = keyboardControl.CommandsInterpret(keyboardControl.input());
		}
		if (a == 2)
		{
			string cmd;
			displayPanel.displayShow("Input your command:\n");
			commands = voiceControl.CommandsInterpret(voiceControl.input());
		}
		
	}
	displayPanel.displayShow("Computer program is shooting down...");
	isOn = false;
	
}

void BoardComputer::execute()
{

	if (commands == "Start/off engine")
	{
		if (!bool(engine.status()[3]))
		{
			displayPanel.displayShow("Engine is starting...\n");
			engine.start();
			displayPanel.displayShow("Engine is started!\n\n");
			displayPanel.engineInfo(engineStatus());
		}
	}
	if (commands == "Increase speed")
	{
		if (bool(engine.status()[3]))
		{
			
			if (safetyCondition())
			{
				displayPanel.displayShow("Engine power has been increased for 990\n");
				engine.changeSpeed(30);
				displayPanel.displayShow("Vehicle speed has been increased for 30 km/h\n");
			}
			else {
				displayPanel.displayShow("The trip is too dangerous, increasing speed more is restricted!!!\n");
			}
			displayPanel.displayShow("Current speed is: ");
			displayPanel.displayShow(to_string(engine.status()[2] / 33));
			displayPanel.displayShow("km/h\n\n");
		}
		else {
			displayPanel.displayShow("You can't increase speed while engine is off!!\n\n");
		}
	}
	if (commands == "Decrease speed")
	{
		if (engine.status()[2] != 0)
		{
			displayPanel.displayShow("Engine power has been decreased for 990\n");
			engine.changeSpeed(30);
			displayPanel.displayShow("Vehicle speed has been decreased for 30 km/h\n");
			displayPanel.displayShow("Current speed is: ");
			displayPanel.displayShow(to_string(engine.status()[2] / 30));
			displayPanel.displayShow("\n\n");
		}
		else displayPanel.displayShow("Error, can't decrease speed because vehicle is stopped\n\n");
	}
	if (commands == "Turn on/off cooler")
	{
		displayPanel.displayShow(microclimatesytem.OnOffCooler());
	}
	if (commands == "Show weather status")
	{
		displayPanel.weatherInfo(microclimatesytem.showWeather());
	}
	if (commands == "Show road status")
	{
		vector<int> road = roadSensor.showCondition();
		displayPanel.displayShow("Analyzing road status.\n");
		string stat;
		switch (road[0])
		{
		case 1: stat += "Road type is perfect. Maximum speed allowed 180 km/h\n";
			break;
		case 2: stat += "Road type is good. Maximum speed allowed 150 km/h\n";
			break;
		case 3: stat += "Road type is moderate. Maximum speed allowed 120 km/h\n";
			break;
		case 4: stat += "Road type is bad. Maximum speed allowed 90 km/h\n";
			break;
		case 5: stat += "Road type is very bad. Maximum speed allowed 60 km/h\n";
			break;
		}
		if (bool(road[1]))
		{
			stat += "Careful, the road is slippery!\n";
		}
		displayPanel.displayShow(stat);
		cout << endl;
	}
	if (commands == "Estimate road")
	{
		displayPanel.displayShow("Estimating road...\n");
		Sleep(2000);
		displayPanel.displayShow(gps.showRoadInfo());
	}
	if (commands == "Engine status")
	{
		displayPanel.engineInfo(engineStatus());
	}
	if (commands == "Show parts status")
	{
		displayPanel.displayStatus(microclimatesytem.devicesStatus());
	}
	if (commands == "None")
	{
		displayPanel.displayShow("Error, input a proper command!!!\n\n");
		Sleep(2000);
	}
}

void BoardComputer::automaticDecision()
{
	microclimatesytem.controller();
	displayPanel.displayShow(microclimatesytem.showStatus());
}

