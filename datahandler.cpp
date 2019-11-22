#include "datahandler.h"
#include <ctime>
#include <QDebug>

datahandler::datahandler()
{
	datanum = 20;
	dataorder = new int[datanum];
	filename1[0] = '\0';
	filename2[0] = '\0';
	srand((unsigned int)time(NULL));

}

void datahandler::generateFileName(int num) {
	filename1[0] = '\0';
	filename2[0] = '\0';

	if (num < 10) {
		strcat(filename1, "00");
		strcat(filename2, "00");
	}
	else if (num<100) {
		strcat(filename1, "0");
		strcat(filename2, "0");
	}

	char temp[4];
	_itoa_s(num, temp, 4, 10);
	strcat(filename1, temp);
	strcat(filename2, temp);
	strcat(filename1, "_1.dat");
	strcat(filename2, "_2.dat");
}


void datahandler::generateRandomOrder() {
	int temp, i, j;
	for (i = 0; i<datanum; i++) {
		temp = rand() % datanum + 1;
		for (j = 0; j<i; j++) {
			if (dataorder[j] == temp) {
				break;
			}
		}
		if (j != i) {
			i--;
		}
		else {
			dataorder[i] = temp;
		}
	}

	qDebug() << "random order : ";
	for (int i = 0; i < datanum; i++) {
		qDebug() << i << " : " << dataorder[i];
	}
}

void datahandler::applyAmplitude(double maxAmp) {
	amplitude = maxAmp;
	for (int i = 0; i<data1size; i++) {
		data1[i] *= maxAmp;
		data2[i] *= maxAmp;
	}
}


int datahandler::readfile() {
	ifstream file1, file2;

	file1.open(filename1, ios::binary | ios::in);
	file2.open(filename2, ios::binary | ios::in);

	if (!file1.is_open() || !file2.is_open()) {
		printf("cannot open the file.");
		return 0;
	}


	file1 >> samplingrate;
	file2 >> samplingrate;
	file1 >> data1size;
	file2 >> data2size;

	for (int i = 0; i<data1size; i++) {
		file1 >> data1[i];
		file2 >> data2[i];
	}

	return 1;
}

double datahandler::getSampRate() {
	return samplingrate;
}

int datahandler::getDataSize() {
	return data1size;
}


int datahandler::getOrder(int n) {
	return dataorder[n];
}

double* datahandler::getData1Ptr() {
	return data1;
}

double* datahandler::getData2Ptr() {
	return data2;
}

double datahandler::getAmplitude() {
	return amplitude;
}

int datahandler::getTotalNumberOfData() {
	return datanum;
}

char* datahandler::getFileName(){
	return filename1;
}


void datahandler::normalize(double r, double u, double l, double c) {
	for (int i = 0; i<data1size; i++) {
		if (i % 2 != 0) {
			data1[i] *= r;
			data2[i] *= l;
		}
		else {
			data1[i] *= u;
			data2[i] *= c;
		}
	}
}

datahandler::~datahandler() {
	delete dataorder;
}