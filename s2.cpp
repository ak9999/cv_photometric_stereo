/*
 * Author: Abdullah Khan
 * s1: Locate sphere in an image and compute the center and radius.
 */

#include <iostream>
#include <string>
#include <fstream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	if (argc != 6)
	{
		cout <<
		"Usage: " << argv[0] << " {input parameters file} {image 1} {image 2} {image 3} {output directions file}"
		<< endl;
		return 0;
	}

	const string parameters(argv[1]);
	const string image1(argv[2]);
	const string image2(argv[3]);
	const string image3(argv[4]);
	const string output_directions(argv[5]);

	int center_x, center_y, radius;

	{
		fstream params(parameters);
		if(!params.is_open())
		{
			cout << parameters << " can't be opened for reading." << endl;
			return 0;
		}
		params >> center_x >> center_y >> radius;
		params.close();
	} // Read parameter file into variables.

	Image sphere1, sphere2, sphere3;
	if (!ReadImage(image1, &sphere1))
	{
		cout << "Can\'t read file " << image1 << ", sorry." << endl;
		return 0;
	}
	if (!ReadImage(image2, &sphere2))
	{
		cout << "Can\'t read file " << image2 << ", sorry." << endl;
		return 0;
	}
	if (!ReadImage(image3, &sphere3))
	{
		cout << "Can\'t read file " << image3 << ", sorry." << endl;
		return 0;
	}

	return 0;
}
