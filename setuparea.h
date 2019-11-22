#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QImage>
#include <QLabel>
#include <QTextEdit>

enum PLACE {RIGHT, UPPER, LEFT, CENTER};

class SetupArea : public QWidget
{
	Q_OBJECT

public:
	SetupArea(QWidget *parent = Q_NULLPTR);
	~SetupArea();

	double getValue(int place);

private:
	QLineEdit* rightEditor;
	QLineEdit* leftEditor;
	QLineEdit* upperEditor;
	QLineEdit* centerEditor;
};
