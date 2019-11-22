#pragma once

#include <QThread>
#include <QDebug>

class TimeThread : public QThread
{
	Q_OBJECT
public:
	TimeThread(QObject *parent = 0);
	~TimeThread();
	int getValue();

protected:
	void run() override;

signals:
	void countTime(int& t);

private:
	int cnt;
};
