#ifndef ANSWERAREA_H
#define ANSWERAREA_H

#include <QMessageBox>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QRadioButton>
#include "ScribbleArea.h"
#include "daqcontroller.h"
#include "datahandler.h"
#include "intensitygraph.h"
#include <QButtonGroup>
#include <QFile>

class ScribbleArea;
class datahandler;
class DAQController;
class IntensityGraph;

class AnswerArea : public QWidget
{
	Q_OBJECT

public:
	AnswerArea(QWidget *parent = 0);
	~AnswerArea();

	QWidget* initCheckBoxArea();
	void setWeight(double* w);

public slots:
	void buttonClickedSlot();
	void sendStopMessageToDAQ();
	void buttonsEnable();
	void buttonsDisable();

protected:
	void saveResult();
	void resetAnswerArea();

private:
	QButtonGroup* startRadioBtnGroup;
	QButtonGroup* endRadioBtnGroup;
	QPushButton* repeatButton;
	QPushButton* nextButton;
	QImage* image;
	IntensityGraph* graphArea;
	ScribbleArea* refImgArea;
	QPainter* painter;
	QTimer* timer;
	QFile* outFile;

	int repeat;
	int cnt;
	datahandler data;
	DAQController daq;
	double weight[4];
};

#endif // !ANSWERAREA_H
