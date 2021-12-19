#pragma once

#include <QDialog>
#include <ui_Settings.h>

class Settings : public QDialog {
	Q_OBJECT
public:
	explicit Settings(QWidget* parent = Q_NULLPTR);
	~Settings();
	void showEvent(QShowEvent* event);
	void ToggleShowHide();

private slots:
	void onFormAccepted();

private:
	Ui::Settings* ui;
};
