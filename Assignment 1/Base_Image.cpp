#include "Base_Image.h"
#include <iostream>

using namespace std;

//functions
void cluster::populate() //function that will populate an array with base values
{
	arr = new double*[rowsize]; 
	for (int i = 0; i < rowsize; i++)
	{
		arr[i] = new double[colsize]; //inputs base value into the array
	}
}

void cluster::set(int x, int y, double value) //function that will set a value in a specified location in the array
{
	arr[x][y] = value; //sets the value to be placed in the array
}

void cluster::print() //function that will print the contents of the array
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

//overload functions
cluster::cluster()
{
	rowsize = 1;
	colsize = 1;
}

cluster::cluster(int x, int y)
{
	rowsize = x;
	colsize = y;
}

cluster::~cluster()
{
	cout << "destructor invoked" << endl;
}