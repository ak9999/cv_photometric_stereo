/*
 * Author: Abdullah Khan
 * s1: Locate sphere in an image and compute the center and radius.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	if (argc != 4)
	{
		cout <<
		"Usage: " << argv[0] << " {input original image} {input threshold value} {output parameters file}"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const int threshold = atof(argv[2]);
	const string output(argv[3]);

	Image img;
	if (!ReadImage(input, &img))
	{
		cout << "Can\'t read file " << input << ", sorry." << endl;
		return 0;
	}

	// Threshold image
	Threshold(img, threshold);
	img.SetNumberGrayLevels(2);

	/*
	 * Compute the centroid to find the circle's location.
	 * To compute the radius, average the differences between the leftmost and the rightmost
	 *	and the uppermost and the lowermost points of the binary circle to obtain the diameter.
	 *	Then divide by 2 to obtain the radius.
	 * The resulting parameters file is a text file consisting of a single line containing the
	 *	x-coordinate of the center, the y-coordinate of the center, and the radius of the circle,
	 *	separated by a space.
	 */

	return 0;
}