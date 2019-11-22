#include "intensitygraph.h"

IntensityGraph::IntensityGraph(QWidget *parent)
	: QWidget(parent)
{
	timeBar = new QProgressBar;
	timeBar->setRange(0, 80);
	sliders = new QSlider*[7];
	QWidget* widget1 = new QWidget;
	QWidget* widget2 = new QWidget;
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* sliderlayout = new QHBoxLayout;
	QHBoxLayout* progresslayout = new QHBoxLayout;
	QLabel* spacer = new QLabel;
	cnt = 0;

	for (int i = 0; i < 7; i++) {
		sliders[i] = new QSlider(this);
		sliders[i]->setFocusPolicy(Qt::ClickFocus);
		sliders[i]->setSingleStep(1);
		sliders[i]->setValue(50);
		sliderlayout->addWidget(sliders[i]);
	}

	sliders[0]->setEnabled(false);
	
	spacer->setFixedSize(10, 50);
	progresslayout->addWidget(spacer);
	progresslayout->addWidget(timeBar);

	widget1->setLayout(sliderlayout);
	widget1->setFixedSize(300, 315);

	widget2->setLayout(progresslayout);
	widget2->setFixedSize(310, 40);

	mainlayout->addWidget(widget1);
	mainlayout->addWidget(widget2);
	setLayout(mainlayout);
}

int IntensityGraph::getValue(int idx) {
	if (idx >= 7) return -1;
	else return sliders[idx]->value();
}


void IntensityGraph::updateTimeBar() {
	if (cnt > timeBar->maximum()) {
		timer->stop();
		timeBar->reset();
		emit endTimer();
		cnt = 0;
		delete timer;
	}else{
		timeBar->setValue(cnt);
		cnt++;
		update();
	}
}

void IntensityGraph::reset() {
	for (int i = 0; i < 7; i++) {
		sliders[i]->setValue(50);
	}
}

void IntensityGraph::startTimer() {
	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeBar()));
	timer->start(40);
}



IntensityGraph::~IntensityGraph()
{

}
