#include "timethread.h"

TimeThread::TimeThread(QObject *parent) : QThread(parent) {
	cnt = 0;
}

TimeThread::~TimeThread() {
}

void TimeThread::run() {
	while (1) {
		msleep(40);
		cnt++;
		qDebug() << "thread : " << cnt;
		emit countTime(cnt);
		if (cnt >= 100) exec();
	}
}

int TimeThread::getValue() {
	return cnt;
}