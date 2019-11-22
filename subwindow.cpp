#include "subwindow.h"
#include <QDebug>

SubWindow::SubWindow()
{
	setupArea = new SetupArea;

	QGridLayout* layout = new QGridLayout;
	layout->addWidget(setupArea);

	setWindowTitle(tr("Setup"));
	resize(800, 600);

	setLayout(layout);
}

SubWindow::~SubWindow()
{
	daq.stop();
}

void SubWindow::getInformation(double* info) {
	info[RIGHT] = setupArea->getValue(RIGHT);
	info[UPPER] = setupArea->getValue(UPPER);
	info[LEFT] = setupArea->getValue(LEFT);
	info[CENTER] = setupArea->getValue(CENTER);
}


void SubWindow::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_F3:
		data.generateFileName(101);
		data.readfile();
		data.applyAmplitude(setupArea->getValue(RIGHT));
		daq.init();
		daq.setSampleClock(data.getSampRate(), data.getDataSize() / 2);
		daq.write(data.getData1Ptr(), data.getData2Ptr());
		daq.start();
		break;
	case Qt::Key_F4:
		data.generateFileName(102);
		data.readfile();
		data.applyAmplitude(setupArea->getValue(UPPER));
		daq.init();
		daq.setSampleClock(data.getSampRate(), data.getDataSize() / 2);
		daq.write(data.getData1Ptr(), data.getData2Ptr());
		daq.start();
		break;
	case Qt::Key_F5:
		data.generateFileName(103);
		data.readfile();
		data.applyAmplitude(setupArea->getValue(LEFT));
		daq.init();
		daq.setSampleClock(data.getSampRate(), data.getDataSize() / 2);
		daq.write(data.getData1Ptr(), data.getData2Ptr());
		daq.start();
		break;
	case Qt::Key_F6:
		data.generateFileName(104);
		data.readfile();
		data.applyAmplitude(setupArea->getValue(CENTER));
		daq.init();
		daq.setSampleClock(data.getSampRate(), data.getDataSize() / 2);
		daq.write(data.getData1Ptr(), data.getData2Ptr());
		daq.start();
		break;
	}

	getInformation(infoResult);
	qDebug() << "keyEvent : " << infoResult[0] << ", " << infoResult[1] << ", " << infoResult[2] << ", " << infoResult[3];
}