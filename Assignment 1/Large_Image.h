#pragma once
#include <iostream>

using namespace std;

class wally
{
private:
	double** arr;
	int rowsize;
	int colsize;
public:
	//overload functions
	wally();
	wally(int rows, int cols);
	~wally();

	//functions
	void populate();
	void set(int x, int y, double value);
	void print();
	double get(int x, int y);
};