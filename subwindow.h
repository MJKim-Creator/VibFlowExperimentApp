#pragma once

#include <QDialog>
#include <QKeyEvent>
#include <QLayout>
#include "datahandler.h"
#include "daqcontroller.h"
#include "setuparea.h"

class SubWindow : public QDialog
{
	Q_OBJECT

public:
	SubWindow();
	~SubWindow();
	void getInformation(double* info);

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	SetupArea* setupArea;
	datahandler data;
	DAQController daq;
	double infoResult[4];
};
