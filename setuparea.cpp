#include "setuparea.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QDebug>

SetupArea::SetupArea(QWidget *parent)
	: QWidget(parent)
{
	QGroupBox* editGroup = new QGroupBox(tr("Modify Actuate Value"));

	QLabel* explain = new QLabel(tr("Please initialize the strength of vibration. \nValue has to be in the range of 10-100, highest value means stronger. \n"));

	QLabel* rightLabel = new QLabel(tr("Right : "));
	rightEditor = new QLineEdit;
	rightEditor->setText("15");
	rightEditor->setFocus();

	QLabel* upperLabel = new QLabel(tr("Upper : "));
	upperEditor = new QLineEdit;
	upperEditor->setText("15");

	QLabel* leftLabel = new QLabel(tr("Left : "));
	leftEditor = new QLineEdit;
	leftEditor->setText("15");

	QLabel* centerLabel = new QLabel(tr("Center : "));
	centerEditor = new QLineEdit;
	centerEditor->setText("15");

	QGridLayout* gridLayout = new QGridLayout;
	QFormLayout* leftLayout = new QFormLayout;
	leftLayout->addRow(explain);
	leftLayout->addRow(rightLabel, rightEditor);
	leftLayout->addRow(upperLabel, upperEditor);
	leftLayout->addRow(leftLabel, leftEditor);
	leftLayout->addRow(centerLabel, centerEditor);

	QImage* img = new QImage;
	QLabel* imgLabel = new QLabel;

	if (!img->load("C:\\Users\\320\\Documents\\Visual Studio 2015\\Projects\\QtExperimentApp\\QtExperimentApp\\SubBackGround.jpg", "JPG")) {
		qDebug() << "Failed to road the background image.";
	}

	gridLayout->addLayout(leftLayout, 0, 0);
	gridLayout->addWidget(imgLabel, 0, 1);

	imgLabel->setPixmap(QPixmap::fromImage(*img));

	setLayout(gridLayout);

}

double SetupArea::getValue(int place) {
	bool flag = false;
	double result;
	switch (place) {
	case RIGHT:
		result = rightEditor->text().toInt(&flag);
		break;
	case UPPER:
		result = upperEditor->text().toInt(&flag);
		break;
	case LEFT:
		result = leftEditor->text().toInt(&flag);
		break;
	case CENTER:
		result = centerEditor->text().toInt(&flag);
		break;
	}

	qDebug() << "getValue : " << result;

	if (flag) {
		return result * 0.01;
	}
	else {
		return 0.0;
	}
}

SetupArea::~SetupArea()
{
}
