/*
 * Author: Abdullah Khan
 * s2: Brightness and directions.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <cmath>
#include <cstdlib>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

/* Shortcut method for 3 x 3 matrices:
https://www.khanacademy.org/math/algebra-home/alg-matrices/alg-determinants-and-inverses-of-large-matrices/v/finding-the-determinant-of-a-3x3-matrix-method-1
*/
long double GetDeterminant(array<array<double, 3>, 3> mat);

array<array<double, 3>, 3> Invert(array<array<double, 3>, 3> mat);

int main(int argc, char ** argv)
{
	if (argc != 8)
	{
		cout <<
		"Usage: " << argv[0] << " {input directions} {image 1} {image 2} {image 3} {step} {threshold} {output}"
		<< endl;
		return 0;
	}

	const string directions(argv[1]);
	const string image1(argv[2]);
	const string image2(argv[3]);
	const string image3(argv[4]);
	const int step = atoi(argv[5]);
	const int threshold = atoi(argv[6]);
	const string output(argv[7]);

	array<array<double, 3>, 3> matrix = {};

	// Instantiate Image objects.
	Image object1, object2, object3, needle_map;
	if (!ReadImage(image1, &object1))
	{
		cout << "Can\'t read file " << image1 << ", sorry." << endl;
		return 0;
	}

	if (!ReadImage(image2, &object2))
	{
		cout << "Can\'t read file " << image2 << ", sorry." << endl;
		return 0;
	}

	if (!ReadImage(image3, &object3))
	{
		cout << "Can\'t read file " << image3 << ", sorry." << endl;
		return 0;
	}

	needle_map.AllocateSpaceAndSetSize(object1.num_rows(), object1.num_columns());
	needle_map.SetNumberGrayLevels(object1.num_gray_levels());

	{
		fstream in(directions);
		if(!in.is_open())
		{
			cout << directions << " can't be opened for reading." << endl;
			return 0;
		}
		string line;
		for (int i = 0; i < 3; i++)
		{
			getline(in, line);
			stringstream buffer(line);
			for (int j = 0; j < 3; j++)
			{
				buffer >> matrix[i][j];
			}
		}
		in.close();
	} // Read directions file into matrix.

	long double determinant = GetDeterminant(matrix);
	if (determinant == 0)
	{
		cout << "Determinant is zero. Matrix not invertible. Exiting.\n";
		return -1;
	}
	
	cout << determinant << endl;

	// Write image to output.
	if (!WriteImage(output, needle_map))
	{
		cout << "Can't write image to file " << output << endl;
		return 0;
	}
	return 0;
}

long double GetDeterminant(array<array<double, 3>, 3> mat)
{
	long double a = (mat[0][0] * mat[1][1] * mat[2][2]) + (mat[0][1] * mat[1][2] * mat[2][0]) + (mat[0][2] * mat[1][0] * mat[2][1]);
	long double b = (mat[2][0] * mat[1][1] * mat[0][2]) + (mat[2][1] * mat[1][2] * mat[0][0]) + (mat[2][2] * mat[1][0] * mat[0][1]);
	return a-b;
}
