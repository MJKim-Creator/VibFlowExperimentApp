#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtexperimentapp.h"

class QtExperimentApp : public QMainWindow
{
	Q_OBJECT

public:
	QtExperimentApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtExperimentAppClass ui;
};
