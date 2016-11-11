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

double Determinant(array<array<double, 3>, 3> a, int n)
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

void CoFactor(array<array<double, 3>, 3> a, int n, array<array<double, 3>, 3> &b)
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

void Transpose(array<array<double, 3>, 3> &a, int n)
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

void InverseDet(array<array<double, 3>, 3> &a, double det)
{
   for (int i=0; i < 3; i++)
   {
      for (int j=0; j < 3; j++)
      {
         a[i][j] = (1/det) * a[i][j];
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
	array<array<double, 3>, 3> cofactor = {};

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
	
	cout << "Original Matrix: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	
	double det = Determinant(matrix,3);
	
	cout << "Cofactor Matrix: " << endl;
	CoFactor(matrix, 3, cofactor);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << cofactor[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << endl;
	
	Transpose(cofactor, 3);
	InverseDet(cofactor, det);
	cout << "Inverse Matrix: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << cofactor[i][j] << " ";
		}
		cout << endl;
	}

	// Write image to output.
	if (!WriteImage(output, needle_map))
	{
		cout << "Can't write image to file " << output << endl;
		return 0;
	}
	return 0;
}

