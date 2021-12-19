#include "Main.h"
#include <QAction>
#include <QMainWindow>
#include <obs-module.h>
#include <obs-frontend-api.h>
#include "./SongReader.h"
#include "Settings.h"

#include "Config.h"
#include "MyThread.h"
#include "Logger.h"

/* Defines common functions (required) */
OBS_DECLARE_MODULE();
OBS_MODULE_USE_DEFAULT_LOCALE("obs-songreader", "en-US");
MODULE_EXPORT const char* obs_module_name(void) { return "Spotify Songreader"; }
MODULE_EXPORT const char* obs_module_description(void) { return "Reads the Spotify state by the main Window Title"; }

Settings* output_settings;
std::thread interval;

/// <summary>
/// Module Load
/// </summary>
bool obs_module_load(void) {
    Logger("obs_module_load");

    // Config & Thread Setup
    Config::Current()->Load();
    MyThread::Current()->Start();

    // Main Interval checking spotify state
    interval = std::thread([]() {
        while (true) {
            SongReader::Current()->getSpotifyState();
            auto sleep_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000);
            std::this_thread::sleep_until(sleep_time);
        }
    });

    // UI Setup
    QMainWindow* main_window = (QMainWindow*)obs_frontend_get_main_window();
    QAction* menu_action = (QAction*)obs_frontend_add_tools_menu_qaction(obs_module_text("SongReader.Menu.Settings"));
    output_settings = new Settings(main_window);
    menu_action->connect(menu_action, &QAction::triggered, [] {
        output_settings->ToggleShowHide();
    });

    Logger("./obs_module_load");
    return true;
}

/// <summary>
/// Module Unload - Cleanup!
/// </summary>
void obs_module_unload(void) {
    Logger("obs_module_unload");
    MyThread::Current()->Stop();
    interval.native_handle();
    Logger("exiting");
}
