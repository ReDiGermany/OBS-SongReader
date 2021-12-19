#include "SongReader.h"
#include "Config.h"
#include <fstream>

// Main SongReader Logic
// Window title logic based on https://docs.microsoft.com/de-de/windows/win32/psapi/enumerating-all-processes

/// <summary>
/// Singleton Instance
/// </summary>
SongReader* SongReader::_instance = nullptr;

/// <summary>
/// Main Update logic
/// </summary>
/// <param name="error">Boolean if there was an error</param>
/// <param name="open">Boolean if spotify is open or not</param>
/// <param name="playing">Boolean if spotify is playing something or not</param>
/// <param name="song">String current title</param>
void SongReader::writeText(bool error,bool open, bool playing,std::string song) {
    Config* conf = Config::Current();
    std::string eStr = (error ? "true" : "false");
    std::string oStr = (open? "true" : "false");
    std::string pStr = (playing ? "true" : "false");
    currentText = "{\"error\":"+ eStr + ",\"open\":" + oStr + ",\"playing\":" + pStr + ",\"track\":\"" + song + "\"}";
    if (conf->FileEnabled) {
        // Write to File
        std::ofstream myfile;
        myfile.open(conf->FilePath.toLocal8Bit().data());
        myfile << song;
        myfile.close();
    }
}

/// <summary>
/// Getting the processes main Window - Based on https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/cdfa4c0c-eebc-49a6-8869-ecbd29c639fa/how-to-get-main-window-hwnd-from-processid?forum=windowssdk
/// </summary>
void SongReader::GetProcessMainWindows(DWORD dwProcessID, std::vector <HWND>& vWindows) {
    HWND hwnd = NULL;

    do{
        hwnd = FindWindowEx(NULL, hwnd, NULL, NULL);
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hwnd, &dwPID);
        if (dwPID == dwProcessID) vWindows.push_back(hwnd);
    } while (hwnd != NULL);
}

/// <summary>
/// Finding all Spotify Window Titles
/// </summary>
/// <param name="processID"></param>
void SongReader::FindSpotifyWindowTitles(DWORD processID)
{
    _tcscpy_s(szProcessName, unknown);

    // Get a handle to the process.
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (!hProcess) return;


    // Get the process name.
    if (NULL != hProcess){
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)){
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        }
    }


    if (_tcscmp(szProcessName, spotify) == 0) { // Check if process file name == "Spotify.exe"
        appcount++;
        vWindows.clear();

        GetProcessMainWindows(processID, vWindows);
        for (i = 0; i < vWindows.size(); i++) {
            _tcscpy_s(title, spotify_empty);
            GetWindowTextW(vWindows.at(i), title, 500);

            // Checking if is valid title
            if (_tcscmp(title, spotify_gdi) != 0 &&
                _tcscmp(title, spotify_ime) != 0 &&
                _tcscmp(title, spotify_ui) != 0 &&
                _tcscmp(title, current_title) != 0 &&
                _tcscmp(title, spotify_empty) != 0
                ) {

                // Updating title cache
                _tcscpy_s(current_title, title);
                if (_tcscmp(title, spotify_idle) == 0) { // Spotify not playing
                    writeText(false, true, false, "");
                }
                else { // Spotify playing
                    std::wstring arr_w(title);
                    std::string arr_s(arr_w.begin(), arr_w.end());

                    writeText(false, true, true, arr_s);
                }
            }
        }
    }

    // Release the handle to the process.
    CloseHandle(hProcess);
}

/// <summary>
/// Reads the current spotify state
/// </summary>
/// <returns>current title</returns>
std::string SongReader::getSpotifyState() {
    memset(aProcesses, 0, 1024);
    appcount = 0;
    unsigned int i;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        writeText(true, false, false, "");
        return currentText;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
    
    // Checking all processes
    for (i = 0; i < cProcesses; i++) {
        if (aProcesses[i] != 0) {
            FindSpotifyWindowTitles(aProcesses[i]);
        }
    }

    // if no process found fallback not playing
    if (appcount == 0) {
        if (appcountbefore != appcount) {
            appcountbefore = appcount;
            writeText(false,false,false,"");
        }
    }
    else appcountbefore = appcount;

    return currentText;
}

/// <summary>
/// Returns current playing song name
/// </summary>
/// <returns>string</returns>
std::string SongReader::getCurrentSong() {
    return currentText;
}

/// <summary>
/// Gets Singleton instance
/// </summary>
/// <returns>Singleton Instance</returns>
SongReader* SongReader::Current() {
    if (!_instance) {
        _instance = new SongReader();
    }
    return _instance;
}

SongReader::SongReader(){}
