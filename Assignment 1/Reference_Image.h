#pragma once
#include<iostream>

using namespace std;

class reference
{
private:
	double** arr;
	int rowsize;
	int colsize;
public:
	reference();
	reference(int rows, int cols);
	~reference();

	void populate();
	void set(int x, int y, double value);
	void print(); 
	double get(int x, int y);
};