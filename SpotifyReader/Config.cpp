#include "Config.h"
#include <obs-frontend-api.h>
#include <util/config-file.h>
#include "Logger.h"

// Main Configuration
// This Class is based on https://github.com/Palakis/obs-ndi/blob/master/src/Config.cpp

#define SECTION_NAME "SongReader"

#define PARAM_WEBSERVER_ENABLED "MainOutputEnabled"
#define PARAM_WEBSERVER_PORT "MainOutputName"

#define PARAM_FILE_ENABLED "PreviewOutputEnabled"
#define PARAM_FILE_PATH "PreviewOutputName"

/// <summary>
/// Static Config Instance
/// </summary>
Config* Config::_instance = nullptr;

/// <summary>
/// Constructor initializing default config
/// </summary>
Config::Config() :
	WebServerEnabled(true),
	WebServerPort("8080"),
	FileEnabled(false),
	FilePath("current_song.txt")
{
	config_t* obs_config = obs_frontend_get_global_config();
	if (obs_config) {
		config_set_default_bool(obs_config, SECTION_NAME, PARAM_WEBSERVER_ENABLED, WebServerEnabled);
		config_set_default_string(obs_config, SECTION_NAME, PARAM_WEBSERVER_PORT, WebServerPort.toUtf8().constData());

		config_set_default_bool(obs_config, SECTION_NAME, PARAM_FILE_ENABLED, FileEnabled);
		config_set_default_string(obs_config, SECTION_NAME, PARAM_FILE_PATH, FilePath.toUtf8().constData());
		Logger("Config::Config()");
	}
	else Logger("Config::Config() obs_config unknown");
}

/// <summary>
/// Config loading method
/// </summary>
void Config::Load() {
	config_t* obs_config = obs_frontend_get_global_config();
	if (obs_config) {
		WebServerEnabled = config_get_bool(obs_config, SECTION_NAME, PARAM_WEBSERVER_ENABLED);
		WebServerPort = config_get_string(obs_config, SECTION_NAME, PARAM_WEBSERVER_PORT);

		FileEnabled = config_get_bool(obs_config, SECTION_NAME, PARAM_FILE_ENABLED);
		FilePath = config_get_string(obs_config, SECTION_NAME, PARAM_FILE_PATH);
		Logger("Config::Load()");
	}
	else Logger("Config::Load() obs_config unknown");
}

/// <summary>
/// Config saving method
/// </summary>
void Config::Save() {
	config_t* obs_config = obs_frontend_get_global_config();
	if (obs_config) {
		config_set_bool(obs_config, SECTION_NAME, PARAM_WEBSERVER_ENABLED, WebServerEnabled);
		config_set_string(obs_config, SECTION_NAME, PARAM_WEBSERVER_PORT, WebServerPort.toUtf8().constData());

		config_set_bool(obs_config, SECTION_NAME, PARAM_FILE_ENABLED, FileEnabled);
		config_set_string(obs_config, SECTION_NAME, PARAM_FILE_PATH, FilePath.toUtf8().constData());

		config_save(obs_config);
		Logger("Config::Save()");
	}
	else Logger("Config::Save() obs_config unknown");
}

/// <summary>
/// Gets Singleton instance
/// </summary>
/// <returns>Singleton Instance</returns>
Config* Config::Current() {
	if (!_instance) _instance = new Config();
	return _instance;
}
