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

array<array<double, 3>, 3> Invert(array<array<double, 3>, 3> mat, double det);

double Determinant(array<array<double, 3>, 3> a, int n=3)
{
   int i,j,j1,j2;
   double det = 0;
   array<array<double, 3>, 3> m = {};

   if (n < 1) { /* Error */

   } else if (n == 1) { /* Shouldn't get used */
      det = a[0][0];
   } else if (n == 2) {
      det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
   } else {
      det = 0;
      for (j1=0;j1<n;j1++) {
         for (i=1;i<n;i++) {
            j2 = 0;
            for (j=0;j<n;j++) {
               if (j == j1)
                  continue;
               m[i-1][j2] = a[i][j];
               j2++;
            }
         }
         det += pow(-1.0,j1+2.0) * a[0][j1] * Determinant(m,n-1);
      }
   }
   return(det);
}

void CoFactor(array<array<double, 3>, 3> a,int n, array<array<double, 3>, 3> &b)
{
   int i,j,ii,jj,i1,j1;
   double det;
   array<array<double, 3>, 3> c = {};

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
}

void Transpose(array<array<double, 3>, 3>  &a,int n)
{
   int i,j;
   double tmp;

   for (i=1;i<n;i++) {
      for (j=0;j<i;j++) {
         tmp = a[i][j];
         a[i][j] = a[j][i];
         a[j][i] = tmp;
      }
   }
}

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
	double **mat1 = new double*[3];
	for (int i = 0; i < 3; ++i)
		mat1[i] = new double[3];

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
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << endl;
	
	Transpose(matrix, 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	//long double determinant = GetDeterminant(matrix);
	double det1 = Determinant(matrix);
	cout << det1 << endl;
	
	//auto invert = Invert(matrix, det1);
	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		cout << invert[i][j] << " ";
	//	}
	//	cout << endl;
	//}

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

array<array<double, 3>, 3> Invert(array<array<double, 3>, 3> mat, double det)
{
	double invdet = 1 / det;

	array<array<double, 3>, 3> inv_mat = {};
	inv_mat[0][0] = mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2] * invdet;
	inv_mat[0][1] = mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2] * invdet;
	inv_mat[0][2] = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1] * invdet;
	inv_mat[1][0] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2] * invdet;
	inv_mat[1][1] = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0] * invdet;
	inv_mat[1][2] = mat[1][0] * mat[0][2] - mat[0][0] * mat[1][2] * invdet;
	inv_mat[2][0] = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1] * invdet;
	inv_mat[2][1] = mat[2][0] * mat[0][1] - mat[0][0] * mat[2][1] * invdet;
	inv_mat[2][2] = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1] * invdet;
	return inv_mat;
}
