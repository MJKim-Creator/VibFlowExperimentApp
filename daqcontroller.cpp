#include "daqcontroller.h"

DAQController::DAQController()
{

}


void DAQController::init() {
	if (taskHandle1 != 0 || taskHandle2 != 0) {
		// call function for clear the task
		stop();
	}

	// create new task on both handlers
	DAQmxCreateTask("task1", &taskHandle1);
	DAQmxCreateTask("task2", &taskHandle2);

	// create analog output channel ao0 and ao1 on dev1
	DAQmxCreateAOVoltageChan(taskHandle1, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, NULL);
	DAQmxCreateAOVoltageChan(taskHandle1, "Dev1/ao1", "", -10.0, 10.0, DAQmx_Val_Volts, NULL);

	// create analog output channel ao0 and ao1 on dev2
	DAQmxCreateAOVoltageChan(taskHandle2, "Dev2/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, NULL);
	DAQmxCreateAOVoltageChan(taskHandle2, "Dev2/ao1", "", -10.0, 10.0, DAQmx_Val_Volts, NULL);
}

void DAQController::setSampleClock(double samplingRate, int sampleSize) {
	this->sampleSize = sampleSize;
	this->samplingRate = samplingRate;

	// set sampling rate and size for each channel
	DAQmxCfgSampClkTiming(taskHandle1, "", samplingRate, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, sampleSize);
	DAQmxCfgSampClkTiming(taskHandle2, "", samplingRate, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, sampleSize);
}

void DAQController::write(double* data1, double* data2) {
	DAQmxWriteAnalogF64(taskHandle1, sampleSize, 0, 15.0, DAQmx_Val_GroupByScanNumber, data1, &written, NULL);
	DAQmxWriteAnalogF64(taskHandle2, sampleSize, 0, 15.0, DAQmx_Val_GroupByScanNumber, data2, &written, NULL);

}

void DAQController::start() {
	DAQmxStartTask(taskHandle1);
	DAQmxStartTask(taskHandle2);

//	DAQmxWaitUntilTaskDone(taskHandle2, 15.0);
}

void DAQController::stop() {
	DAQmxStopTask(taskHandle1);
	DAQmxStopTask(taskHandle2);

	DAQmxClearTask(taskHandle1);
	DAQmxClearTask(taskHandle2);

	taskHandle1 = 0;
	taskHandle2 = 0;
}



DAQController::~DAQController()
{

}
