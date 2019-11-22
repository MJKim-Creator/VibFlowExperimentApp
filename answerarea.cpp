#include "answerarea.h"


AnswerArea::AnswerArea(QWidget *parent)
	: QWidget(parent)
{
	graphArea = new IntensityGraph;

	refImgArea = new ScribbleArea;
	refImgArea->setBackgroundFilePath("C:\\Users\\320\\Documents\\Visual Studio 2015\\Projects\\QtExperimentApp\\QtExperimentApp\\background_vibratorplaced.jpg");
	refImgArea->setBackground();
	refImgArea->setRectSize(QSize(480, 360));

	QGroupBox* imgbox = new QGroupBox(tr("Reference image"));
	QGroupBox* answerbox = new QGroupBox(tr("Answers"));
	QVBoxLayout* dummyImg = new QVBoxLayout;
	QHBoxLayout* dummyAnswer = new QHBoxLayout;

	dummyImg->addWidget(refImgArea);
	imgbox->setLayout(dummyImg);

	dummyAnswer->addWidget(initCheckBoxArea());
	dummyAnswer->addWidget(graphArea);
	answerbox->setLayout(dummyAnswer);

	imgbox->setFixedSize(500, 400);
	answerbox->setFixedSize(550, 400);

	//	setAttribute(Qt::WA_StaticContents);
	QHBoxLayout* mainlayout = new QHBoxLayout;
	mainlayout->addWidget(imgbox);
	mainlayout->addWidget(answerbox);
	setLayout(mainlayout);



	show();

	repeat = 0;
	cnt = 0;
	data.generateRandomOrder();
	connect(repeatButton, SIGNAL(clicked()), graphArea, SLOT(startTimer()));
	connect(repeatButton, SIGNAL(clicked()), this, SLOT(buttonsDisable()));
	connect(graphArea, SIGNAL(endTimer()), this, SLOT(buttonsEnable()));

	outFile = new QFile("001.txt");

	if (!outFile->open(QIODevice::WriteOnly | QIODevice::Text))
		qDebug() << "Cannot open the output file.";
}

QWidget* AnswerArea::initCheckBoxArea() {
	QWidget* widget = new QWidget;
	QVBoxLayout *checkboxArea = new QVBoxLayout;

	QGroupBox* startRadioBox = new QGroupBox(tr("Starting Point"));
	QGroupBox* endRadioBox = new QGroupBox(tr("Ending Point"));

	startRadioBtnGroup = new QButtonGroup;
	endRadioBtnGroup = new QButtonGroup;

	QRadioButton** radios = new QRadioButton*[8];
	QStringList strlist;

	strlist.push_back("Top");
	strlist.push_back("Left");
	strlist.push_back("Center");
	strlist.push_back("Right");

	strlist.push_back("Top");
	strlist.push_back("Left");
	strlist.push_back("Center");
	strlist.push_back("Right");

	for (int i = 0; i < 8; i++) {
		radios[i] = new QRadioButton(strlist.at(i));
	}

	repeatButton = new QPushButton(tr("Play"));
	nextButton = new QPushButton(tr("Next Stage"));
	connect(repeatButton, SIGNAL(clicked()), this, SLOT(buttonClickedSlot()));
	connect(nextButton, SIGNAL(clicked()), this, SLOT(buttonClickedSlot()));

	QVBoxLayout* vbox1 = new QVBoxLayout;
	QVBoxLayout* vbox2 = new QVBoxLayout;

	for (int i = 0; i < 8; i++) {
		if (i < 4) {
			vbox1->addWidget(radios[i]);
			startRadioBtnGroup->addButton(radios[i]);
		}
		else {
			vbox2->addWidget(radios[i]);
			endRadioBtnGroup->addButton(radios[i]);
		}
	}

	vbox1->addStretch(2);
	vbox2->addStretch(2);

	startRadioBox->setLayout(vbox1);
	endRadioBox->setLayout(vbox2);

	checkboxArea->addWidget(repeatButton);
	checkboxArea->addWidget(startRadioBox);
	checkboxArea->addWidget(endRadioBox);
	checkboxArea->addWidget(nextButton);

	widget->setLayout(checkboxArea);
	widget->setFixedSize(QSize(200, 360));
	return widget;
}

void AnswerArea::setWeight(double* w)
{
	for (int i = 0; i < 4; i++) {
		weight[i] = w[i];
	}
}

void AnswerArea::buttonClickedSlot() {
//	repeatButton->setEnabled(false);
//	nextButton->setEnabled(false);

	if (((QPushButton*)sender())->text() == "Play") {
		qDebug() << "Play button clicked";
		qDebug() << "Random number : " << data.getOrder(cnt);

		if (cnt >= data.getTotalNumberOfData() && repeat < 3) {
			repeat++;
			cnt = 0;
			data.generateRandomOrder();
		}

		int num = data.getOrder(cnt);

		if (num % 2 != 0) {
			// odd: not normalized data
			int temp = 0;
			data.generateFileName(num);
			data.readfile();
			// find minimum value from normalized data
			for (int i = 1; i < 4; i++) {
				if (weight[temp] > weight[i]) {
					temp = i;
				}
			}

			// give all the same value
			data.normalize(weight[temp], weight[temp], weight[temp], weight[temp]);
			qDebug() << data.getFileName();
		}
		else {
			// even : normalized data
			num = num - 1;
			data.generateFileName(num);
			data.readfile();
			data.normalize(weight[0], weight[1], weight[2], weight[3]);
			qDebug() << data.getFileName();
		}
			
		data.applyAmplitude(1.0);
		daq.init();
		daq.setSampleClock(data.getSampRate(), data.getDataSize() / 2);
		daq.write(data.getData1Ptr(), data.getData2Ptr());
		daq.start();

	} else if (((QPushButton*)sender())->text() == "Next Stage") {
		qDebug() << "Next stage button clicked";

		if (repeat >= 3) {
			QMessageBox::StandardButton ret;
			ret = QMessageBox::warning(this, tr("Experiment"),
				tr("Experiment test set is finished.\n"
					"Thank you for your effort!"), QMessageBox::Ok);
			return;
		}

		// both start and end were chosen from user
		if (startRadioBtnGroup->checkedButton() != 0 && endRadioBtnGroup->checkedButton() != 0) {
			saveResult();
			cnt++;
			resetAnswerArea();
			update();
		}
		else {
			QMessageBox::StandardButton ret;
			ret = QMessageBox::warning(this, tr("AnswerArea"),
				tr("Didn't choose the start or ending point."),
				QMessageBox::Ok);
			return;
		}

	}
}

void AnswerArea::saveResult() {
	QTextStream out(outFile);
	int startInt, endInt;

	if (startRadioBtnGroup->checkedButton()->text() == "Right") {
		startInt = 0;
	}
	else if (startRadioBtnGroup->checkedButton()->text() == "Top") {
		startInt = 1;
	}
	else if (startRadioBtnGroup->checkedButton()->text() == "Left") {
		startInt = 2;
	}
	else if (startRadioBtnGroup->checkedButton()->text() == "Center") {
		startInt = 3;
	}
	else {
		startInt = -1;
	}

	if (endRadioBtnGroup->checkedButton()->text() == "Right") {
		endInt = 0;
	}
	else if (endRadioBtnGroup->checkedButton()->text() == "Top") {
		endInt = 1;
	}
	else if (endRadioBtnGroup->checkedButton()->text() == "Left") {
		endInt = 2;
	}
	else if (endRadioBtnGroup->checkedButton()->text() == "Center") {
		endInt = 3;
	}
	else {
		endInt = -1;
	}

	out << data.getOrder(cnt) << " " << startInt << " " << endInt << " ";
	qDebug() << "to file : " << data.getOrder(cnt) << " " << startInt << " " << endInt << " ";

	for (int i = 0; i < 7; i++) {
		out << graphArea->getValue(i) << " ";
	}

	out << endl;
}

void AnswerArea::resetAnswerArea() {
	graphArea->reset();

	startRadioBtnGroup->setExclusive(false);
	startRadioBtnGroup->checkedButton()->setChecked(false);
	startRadioBtnGroup->setExclusive(true);

	endRadioBtnGroup->setExclusive(false);
	endRadioBtnGroup->checkedButton()->setChecked(false);
	endRadioBtnGroup->setExclusive(true);
}


AnswerArea::~AnswerArea()
{
}


void AnswerArea::sendStopMessageToDAQ() {
	daq.stop();
}

void AnswerArea::buttonsEnable() {
	repeatButton->setEnabled(true);
	nextButton->setEnabled(true);
}

void AnswerArea::buttonsDisable() {
	repeatButton->setEnabled(false);
	nextButton->setEnabled(false);
}