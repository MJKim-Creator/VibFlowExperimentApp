#pragma once

#include <QWidget>
#include <QProgressBar>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

class IntensityGraph : public QWidget
{
	Q_OBJECT

public:
	IntensityGraph(QWidget *parent = 0);
	~IntensityGraph();
	int getValue(int idx);
	void reset();

public slots:
	void updateTimeBar();
	void startTimer();

signals:
	void endTimer();

private:
	QTimer* timer;
	
	QProgressBar* timeBar;
	QSlider** sliders;
	QSlider* timeDummy;
	int cnt;
};
