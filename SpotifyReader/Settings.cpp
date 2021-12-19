#include "Settings.h"
#include "Config.h"
#include "MyThread.h"

// This Class is heavily based on https://github.com/Palakis/obs-ndi

/// <summary>
/// Constructor setting up the UI
/// </summary>
/// <param name="parent"></param>
Settings::Settings(QWidget* parent) : QDialog(parent), ui(new Ui::Settings)
{
	ui->setupUi(this);
	connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(onFormAccepted()));
}

/// <summary>
/// Event Handler for form closing - Updates the config & restarts the web server
/// </summary>
void Settings::onFormAccepted() {
	Config* conf = Config::Current();

	conf->WebServerEnabled = ui->portGroupBox->isChecked();
	conf->WebServerPort = ui->portNumber->text();
	
	conf->FileEnabled = ui->fileGroupBox->isChecked();
	conf->FilePath = ui->fileName->text();

	conf->Save();

	MyThread::Current()->Restart();

}

/// <summary>
/// Event Handler when the settings page is shown - filling UI with current config
/// </summary>
/// <param name="event"></param>
void Settings::showEvent(QShowEvent* event) {
	Config* conf = Config::Current();

	ui->portGroupBox->setChecked(conf->WebServerEnabled);
	ui->portNumber->setText(conf->WebServerPort);
	
	ui->fileGroupBox->setChecked(conf->FileEnabled);
	ui->fileName->setText(conf->FilePath);
}

/// <summary>
/// Toggling UI Visibility
/// </summary>
void Settings::ToggleShowHide() {
	setVisible(!isVisible());
}

/// <summary>
/// Destructor deleting UI
/// </summary>
Settings::~Settings() {
	delete ui;
}
