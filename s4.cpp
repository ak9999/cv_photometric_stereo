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
void InverseDet(Matrix3 &a, double det);

/*
 * The following functions were taken from
 * 		https://www.cs.rochester.edu/~brown/Crypto/assts/projects/adj.html
 * and edited to work with types Matrix3 and changed to be more like Modern C++.
 */
double Determinant(Matrix3 a, int n);
Matrix3 CoFactor(Matrix3 a, int n);
void Transpose(Matrix3 &a, int n);

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
	
	double det = Determinant(matrix,3);
	Matrix3 inverse = CoFactor(matrix, 3);
	Transpose(inverse, 3);
	InverseDet(inverse, det);

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
					double x = inverse[0][0] * b1 + inverse[0][1] * b2 + inverse[0][2] * b3;
					double y = inverse[1][0] * b1 + inverse[1][1] * b2 + inverse[1][2] * b3;
					double z = inverse[2][0] * b1 + inverse[2][1] * b2 + inverse[2][2] * b3;
					double mag = sqrt( x*x + y*y + z*z );
					object1.SetPixel(i, j, b1*mag);
				}
				else { object1.SetPixel(i,j,0); }
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

double Determinant(Matrix3 a, int n)
{
	int i,j,j1,j2;
	double det = 0;
	Matrix3 m = {};

	if (n < 1) { return 0; }
	else if (n == 1) { det = a[0][0]; }
	else if (n == 2) { det = a[0][0] * a[1][1] - a[1][0] * a[0][1]; }
	else
	{
		det = 0;
		for (j1=0;j1<n;j1++) {
			for (i=1;i<n;i++) {
				j2 = 0;
				for (j=0;j<n;j++) {
					if (j == j1) continue;
					m[i-1][j2] = a[i][j];
					j2++;
				}
			}
			det += pow(-1.0,j1+2.0) * a[0][j1] * Determinant(m,n-1);
		}
	}
	return(det);
}

Matrix3 CoFactor(Matrix3 a, int n)
{
	int i,j,ii,jj,i1,j1;
	double det;
	Matrix3 b = {};
	Matrix3 c = {};

	for (j=0;j<n;j++) {
		for (i=0;i<n;i++) {

		/* Form the adjoint a_ij */
			i1 = 0;
			for (ii=0;ii<n;ii++) {
				if (ii == i)
					continue;
				j1 = 0;
				for (jj=0;jj<n;jj++) {
					if (jj == j)
						continue;
					c[i1][j1] = a[ii][jj];
					j1++;
				}
				i1++;
			}

		/* Calculate the determinate */
			det = Determinant(c,n-1);

		/* Fill in the elements of the cofactor */
			b[i][j] = pow(-1.0,i+j+2.0) * det;
		}
	}
	return b;
}

void Transpose(Matrix3 &a, int n)
{
	double tmp;

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			tmp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = tmp;
		}
	}
}

void InverseDet(Matrix3 &a, double det)
{
	for (int i=0; i < 3; i++)
	{
		for (int j=0; j < 3; j++)
		{
			a[i][j] = (1/det) * a[i][j];
		}
	}
}
