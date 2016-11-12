/*
 * Author: Abdullah Khan
 * s3: Albedo Image
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
using Matrix3 = array<array<double, 3>, 3>;

// Matrix operations
// Matrix operations

double GetDeterminant(Matrix3 A)
{
	double a = (A[0][0] * A[1][1] * A[2][2]) + (A[0][1] * A[1][2] * A[2][0]) + (A[0][2] * A[1][0] * A[2][1]);
	double b = (A[2][0] * A[1][1] * A[0][2]) + (A[2][1] * A[1][2] * A[0][0]) + (A[2][2] * A[1][0] * A[0][1]);
	return a-b;
}

/*
Implemented from the information given here:
http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
Much easier than handling co-factors.
*/
Matrix3 GetInverse(Matrix3 A, double determinant)
{
	Matrix3 B = {};
	double invdet = 1/determinant;

	// First row
	B[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]) * invdet;
	B[0][1] = (A[0][3] * A[2][1] - A[0][1] * A[2][2]) * invdet;
	B[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) * invdet;

	// Second row
	B[1][0] = (A[1][2] * A[2][0] - A[1][0] * A[2][2]) * invdet;
	B[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) * invdet;
	B[1][2] = (A[0][2] * A[1][0] - A[0][0] * A[1][2]) * invdet;

	// Third row
	B[2][0] = (A[1][0] * A[2][1] - A[1][1] * A[2][0]) * invdet;
	B[2][1] = (A[0][1] * A[2][0] - A[0][0] * A[2][1]) * invdet;
	B[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) * invdet;
	return B;
}

int main(int argc, char ** argv)
{
	if (argc != 7)
	{
		cout <<
		"Usage: " << argv[0] << " {input directions} {image 1} {image 2} {image 3} {threshold} {output}"
		<< endl;
		return 0;
	}

	const string directions(argv[1]);
	const string image1(argv[2]);
	const string image2(argv[3]);
	const string image3(argv[4]);
	const int threshold = atoi(argv[5]);
	const string output(argv[6]);

	Matrix3 matrix = {};

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
	
	// Find determinant and invert the matrix.
	double det = GetDeterminant(matrix);
	Matrix3 inverse = GetInverse(matrix, det);

	{
		for (unsigned int i = 0; i < object1.num_rows(); i++)
		{
			for (unsigned int j = 0; j < object1.num_columns(); j++)
			{
				double b1 = object1.GetPixel(i,j);
				double b2 = object2.GetPixel(i,j);
				double b3 = object3.GetPixel(i,j);
				if (b1 >= threshold && b2 >= threshold && b3 >= threshold)
				{
					// Calculate current normal, and magnitude.
					double x = inverse[0][0] * b1 + inverse[0][1] * b2 + inverse[0][2] * b3;
					double y = inverse[1][0] * b1 + inverse[1][1] * b2 + inverse[1][2] * b3;
					double z = inverse[2][0] * b1 + inverse[2][1] * b2 + inverse[2][2] * b3;
					double mag = sqrt( x*x + y*y + z*z );
					int val = b1*mag;
					object1.SetPixel(i, j, val); // Change pixel value.
				}
				else { object1.SetPixel(i,j,0); } // Make it black.
			}
		}
	}

	// Write image to output.
	if (!WriteImage(output, object1))
	{
		cout << "Can't write image to file " << output << endl;
		return 0;
	}
	return 0;
}
