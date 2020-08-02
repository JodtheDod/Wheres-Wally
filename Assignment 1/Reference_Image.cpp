#include"Reference_Image.h"
#include<iostream>

using namespace std;

//functions
void reference::populate() //function that will populate an array with base values
{
	arr = new double*[rowsize];
	for (int i = 0; i < rowsize; i++)
	{
		arr[i] = new double[colsize]; //inputs base value into the array
	}
}

void reference::set(int x, int y, double value) //function that will set a value in a specified location in the array
{
	arr[x][y] = value; //sets the value to be placed in the array
}

void reference::print() //function that will print the contents of the array
{
	for (int x = 0; x < rowsize; x++) //loops through the rows of the array
	{
		for (int y = 0; y < colsize; y++) //loops through the columns of the array
		{
			cout << arr[x][y] << ' '; //outputs information from the point of the array
		}
		cout << endl;
	}
}

double reference::get(int x, int y) //function that will get information from a certain point in the array and return it to the main
{
	return arr[x][y];
}

reference::reference()
{
	rowsize = 1;
	colsize = 1;
}

reference::reference(int x, int y)
{
	rowsize = x;
	colsize = y;
}

reference::~reference()
{
	cout << "destructor invoked" << endl;
}