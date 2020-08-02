#include <iostream>
#include <fstream>
#include <string>
#include "Base_Image.h" //cluster image header
#include "Large_Image.h" //wally image header
#include "Reference_Image.h" //reference image header

using namespace std;

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
// Read .txt file with image of size (R rows x C columns), and convert to an array of doubles
double* read_text(string fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i > sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			//cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
}

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and 1 for binary images.
void write_pgm(string filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i < sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC) * sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}
int main()
{
	//read images
	double* scene = read_text("Cluttered_scene.txt", 768, 1024); //clustered image
	double* scene2 = read_text("Wally_grey.txt", 49, 36); //wally image
	cout << "Images read" << endl;

	//cluster matrix
	cluster *c = new cluster(768, 1024);
	c->populate(); //populates the cluster matrix with default values
	cout << "Cluster Matrix populated" << endl;
	
	//index value for the pixel value of the images
	int i = 0;

	for (int row = 0; row < 768; row++)
	{
		for (int col = 0; col < 1024; col++)
		{
			c->set(row, col, scene[i]); //sets the pixel value at the designated row and column in the matrix
			i++;
		}
	}	

	//wally matrix
	wally *w = new wally(49, 36);
	w->populate(); //populates the wally matrix with default values
	cout << "Wally Matrix populated" << endl;

	//index value for the pixel value of the images
	i = 0;

	for (int row = 0; row < 49; row++)
	{
		for (int col = 0; col < 36; col++)
		{
			w->set(row, col, scene2[i]); //sets the pixel value at the designated row and column in the matrix
			i++;
		}
	}

	//reference matrix
	reference *r = new reference(49, 36);
	r->populate(); //populates the reference matrix with default values
	cout << "Reference Matrix populated" << endl;

	cout << "Trying to find wally..." << endl; //output telling the user that wally is being searched for

	i = 0; //the index point for a pixel in the cluster image
	int point = 1; //next index point on the next cycle

	int checker = 0; //will increment if there is a match with both reference and wally matrix pixel values
	int checkermax = 0; //will hold the highest value for the check
	int imin = 0; //minimum index value to find wally
	int imax = 0; //maximum index value to find wally

	while (point < 736259)
	{
		int row = 0; //the starting row point for the reference matrix
		int rowm = 49; //the ending row point for the reference matrix
		int col = 0; //the starting column point for the reference matrix
		int colm = 36; //the ending column point for the reference matrix

		//Dual for loop that will set the matrix points
		for (row; row < rowm; row++)
		{
			for (col; col < colm; col++)
			{
				r->set(row, col, scene[i]); //sets a pixel value for the reference matrix for the given rows and columns
				if (r->get(row, col) == w->get(row, col)) //compares reference pixel with wally pixel
				{
					checker += 1; //if reference pixel and wally pixel match, checker will increment
				}
				i++; //increment index	
			}
			col -= colm; //sets first column back to original position
			i += 988; //if end of column has been reached it will go to the next row and gather pixel from specified index location
		}

	
		if (checker > checkermax) //checks the best nearest neighbour search for the best match
		{
			checkermax = checker; //will set the current best search to a variable named checkermax
			imax = i; //last pixel of the reference for the best match
			imin = i - 50176; //first pixel of the reference for the best match
		}
		
		i = point; //will then start another search to the next index value
		point++; //increment point for the next iteration
		checker = 0; //reset checker value for the next iteration
		
	}
	
	//a best match has been found and will now change pixel values to show where wally is
	//the image will be coloured in black to indicate where wally is
	while (imin < imax) 
	{
		for (int finalrow = 0; finalrow < 49; finalrow++) //for loop to cycle the rows
		{
			for (int finalcol = 0; finalcol < 36; finalcol++) //for loop to cycle the columns
			{
				scene[imin] = 0; //will set the pixel at the given point to 0 which would be black
				imin++; //increments the imin variable so it can move onto the next pixel
			}
			imin += 988; //once the first row is done this will move it on to the next row
		}
	}
	
	cout << "wally found" << endl; //and output indicating wally has been found to the console

	write_pgm("found.pgm", scene, 768, 1024, 255); //write the image of wally found and call it "found.pgm"
	cout << "Image writen" << endl; //output indicating the image has been written to file
	cout << "You can find the image found.pgm in the folder of this executable file where you will find a blacked out box where wally is" << endl;
	
	delete scene; //delete variable to clear memory
	delete scene2; //delete variable to clear memory
	c->~cluster(); //destructor called
	w->~wally(); //destructor called 
	r->~reference(); //destructor called
	
	system("pause");
	return 0;
}
//matrix for clustered image 768 rows 1024 columns
//matrix for wally image 49 rows 36 columns
//point = 736259
//147618
