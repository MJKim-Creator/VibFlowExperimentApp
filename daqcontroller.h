#ifndef DAQCONTROLLER_H
#define DAQCONTROLLER_H

#include <NIDAQmx.h>


class DAQController
{
public:
	DAQController();
	~DAQController();

	void init();
	void setSampleClock(double samplingRate, int sampleSize);

	void write(double* data1, double* data2);
	void start();
	void stop();

private:
	TaskHandle taskHandle1 = 0;
	TaskHandle taskHandle2 = 0;
	double samplingRate;
	int sampleSize;
	int32 written;
};

#endif // DAQCONTROLLER_H
