# SongReader

An OBS Plugin that reads the Spotify playstate by its window title.

## Features

- **Save To File**: Saves the current title into a given file
- **Share via http**: A Simple Webserver providing json based information about the current play state. [WebServer](#WebServer)

## Downloads

Binaries for Windows are available on the [Releases](https://github.com/ReDiGermany/OBS-SongReader/releases)

## WebServer

The WebServer is running on \*:8080 per default but you can change it in the settings pane (Tools -> SongReader Settings)

```json
{
  "error": false,
  "open": true,
  "playing": true,
  "track": "Diamond Eyes - Flutter"
}
```

- _error_: true if there was an error
- _open_: true if spotify client is open
- _playing_: true if spotify client is playing something
- _track_: the current track (main interpret - track name)
  C:\Users\Max ReDiGermany\source\repos\SpotifyReader

## Development

- Compile as .dll
- Use C++20
- Windows SDK >= 10.0.20348.0
- Additional Includes:
- - cpp-httplib-master
- - obs-studio\libobs
- - obs-studio\UI\obs-frontend-api
- - Qt\5.15.2\msvc2019_64\include\QtCore
- - Qt\5.15.2\msvc2019_64\include\QtWidgets
- - Qt\5.15.2\msvc2019_64\include\QtGui
- - Qt\5.15.2\msvc2019_64\include\QtPlatformCompositorSupport
- - Qt\5.15.2\msvc2019_64\include\QtPlatformHeaders
- - Qt\5.15.2\msvc2019_64\include\QtThemeSupport
- Additional Links:
- - obs-studio\build\libobs\Debug\obs.lib
- - obs-studio\build\UI\obs-frontend-api\Debug\obs-frontend-api.lib
- - Qt\5.15.2\msvc2019_64\lib\Qt5Core.lib
- - Qt\5.15.2\msvc2019_64\lib\Qt5Widgets.lib
- - Qt\5.15.2\msvc2019_64\lib\Qt5Gui.lib
- - Qt\5.15.2\msvc2019_64\lib\Qt5PlatformCompositorSupport.lib
- - Qt\5.15.2\msvc2019_64\lib\Qt5ThemeSupport.lib

## Inheritances

- Web Server by [yhirose/cpp-httplib](https://github.com/yhirose/cpp-httplib)
- UI Based on [Palakis/obs-ndi](https://github.com/Palakis/obs-ndi)
