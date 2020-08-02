#pragma once
#include <iostream>

using namespace std;

class cluster
{
private:
	double** arr;
	int rowsize;
	int colsize;
public:
	//overload functions
	cluster();
	cluster(int rows, int cols);
	~cluster();

	//functions
	void populate();
	void set(int x, int y, double value);
	void print();
	double* read(int x, int y);
};
