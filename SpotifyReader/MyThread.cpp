#include "MyThread.h"
#include "SongReader.h"
#include <iostream>
#include "Config.h"
#include <httplib.h>
#include "Logger.h"

/// <summary>
/// WebServer instance
/// </summary>
httplib::Server svr;

/// <summary>
/// WebServer Thread function - Server by https://github.com/yhirose/cpp-httplib
/// </summary>
void run() {
    Logger("task1()");
    Config* conf = Config::Current();
    if (conf->WebServerEnabled) {

        svr.Get("/", [](const httplib::Request&, httplib::Response& res) {

            res.set_content(SongReader::Current()->getCurrentSong(), "application/json; charset=cp1252");
            });

        svr.listen("0.0.0.0", conf->WebServerPort.toInt());
    }
}

/// <summary>
/// Singelton Instance
/// </summary>
MyThread* MyThread::_instance = nullptr;

/// <summary>
/// Constructor starting thread
/// </summary>
MyThread::MyThread() { Start(); }

/// <summary>
/// Destructor stopping thread
/// </summary>
MyThread::~MyThread() { Stop(); }

/// <summary>
/// Thread safe starting (only if not joinable)
/// </summary>
void MyThread::Start() {
    if (!thread.joinable()) {
        Logger("MyThread::Start()");
        thread = std::thread(run);
    }
    else Logger("MyThread::Start() failed. joinable");
}

/// <summary>
/// Thread safe stopping (only if joinable - forces stop)
/// </summary>
void MyThread::Stop() {
    svr.stop();
    if (thread.joinable()) {
        Logger("MyThread::Stop()");
        thread.join();
        Logger("MyThread::Stop() joined");
        thread.native_handle();
        Logger("MyThread::Stop() handled");
    }
    else Logger("MyThread::Stop() failed. not joinable");
}

/// <summary>
/// Stopping and Starting the thread
/// </summary>
void MyThread::Restart() {
    Logger("MyThread::Restart()");
    Stop();
    Start();
}

/// <summary>
/// Gets Singleton instance
/// </summary>
/// <returns>Singleton Instance</returns>
MyThread* MyThread::Current() {
    if (!_instance)
        _instance = new MyThread();
    return _instance;
}
