#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <fstream>
using namespace std;


class datahandler
{
public:
	datahandler();


	void generateFileName(int num);
	void generateRandomOrder();
	void applyAmplitude(double maxAmp);
	void normalize(double r, double u, double l, double c);

	int getOrder(int n);
	double getSampRate();
	int getDataSize();
	double* getData1Ptr();
	double* getData2Ptr();
	double getAmplitude();
	int getTotalNumberOfData();
	char* getFileName();

	int readfile();

	~datahandler();

private:
	double data1[20000] = { 0, }, data2[20000] = { 0, };
	int data1size, data2size;
	int *dataorder;
	int datanum;
	char filename1[32], filename2[32];
	double samplingrate;
	double amplitude;
};

#endif // DATAHANDLER_H
