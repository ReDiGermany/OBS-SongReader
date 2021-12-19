#pragma once
#include <QString>
#include <obs-module.h>

class Config {
public:
	Config();
	static void OBSSaveCallback(obs_data_t* save_data, bool saving, void* private_data);
	static Config* Current();
	void Load();
	void Save();

	bool WebServerEnabled;
	QString WebServerPort;

	bool FileEnabled;
	QString FilePath;

private:
	static Config* _instance;
};
