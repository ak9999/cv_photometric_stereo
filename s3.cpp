/*
 * Author: Abdullah Khan
 * s2: Brightness and directions.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

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

	// {
	// 	fstream in(directions);
	// 	if(!in.is_open())
	// 	{
	// 		cout << directions << " can't be opened for reading." << endl;
	// 		return 0;
	// 	}
	// 	params >> center_x >> center_y >> radius;
	// 	params.close();
	// } // Read parameter file into variables.

	// Image sphere1, sphere2, sphere3;
	// if (!ReadImage(image1, &sphere1))
	// {
	// 	cout << "Can\'t read file " << image1 << ", sorry." << endl;
	// 	return 0;
	// }

	// if (!ReadImage(image2, &sphere2))
	// {
	// 	cout << "Can\'t read file " << image2 << ", sorry." << endl;
	// 	return 0;
	// }

	// if (!ReadImage(image3, &sphere3))
	// {
	// 	cout << "Can\'t read file " << image3 << ", sorry." << endl;
	// 	return 0;
	// }

	// {
	// 	fstream directions(output_directions, std::ios::out);
	// 	if(!directions.is_open())
	// 	{
	// 		cout << output_directions << " can't be opened for reading." << endl;
	// 		return 0;
	// 	}
	// 	directions << get<0>(scale1) << " " << get<1>(scale1) << " " << get<2>(scale1) << endl;
	// 	directions << get<0>(scale2) << " " << get<1>(scale2) << " " << get<2>(scale2) << endl;
	// 	directions << get<0>(scale3) << " " << get<1>(scale3) << " " << get<2>(scale3) << endl;
	// 	directions.close();
	// } // Read parameter file into variables.

	return 0;
}
