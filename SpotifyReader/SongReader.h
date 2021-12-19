#pragma once
#include <atlstr.h>
#include <vector>
#include <iostream>
#include <psapi.h>

class SongReader
{
	TCHAR spotify[MAX_PATH] = TEXT("Spotify.exe");
	TCHAR spotify_gdi[MAX_PATH] = TEXT("GDI+ Window (Spotify.exe)");
	TCHAR spotify_ime[MAX_PATH] = TEXT("Default IME");
	TCHAR spotify_ui[MAX_PATH] = TEXT("MSCTFIME UI");
	TCHAR spotify_empty[MAX_PATH] = TEXT("");
	TCHAR spotify_idle[MAX_PATH] = TEXT("Spotify Premium");
	TCHAR current_title[500];
	TCHAR unknown[MAX_PATH] = TEXT("<unknown>");
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	HANDLE hProcess;
	HMODULE hMod;
	std::vector <HWND> vWindows;
	TCHAR title[500];
	char tplt_idle[500] = { "{\"error\":false,\"open\":true,\"playing\":false}\n" };
	char tplt_offline[500] = { "{\"error\":false,\"open\":false}\n" };

	DWORD aProcesses[1024], cbNeeded, cProcesses, dwempty;
	unsigned short appcount = 0;
	unsigned short appcountbefore = -1;
	unsigned int i;

	std::string currentText = "";
	static SongReader* _instance;
public: 
	void writeText(bool error, bool open, bool playing, std::string song);
	void GetProcessMainWindows(DWORD dwProcessID, std::vector <HWND>& vWindows);
	void FindSpotifyWindowTitles(DWORD processID);
	std::string getSpotifyState();
	std::string getCurrentSong();
	static SongReader* Current();
	SongReader();
};
