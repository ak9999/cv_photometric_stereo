/*
 * Author: Abdullah Khan
 * s1: Locate sphere in an image and compute the center and radius.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

auto get_brightest_pixel(Image &img)
{
	auto pixel = make_pair(0,0);
	for (unsigned int i = 0; i < img.num_rows(); ++i)
	{
		for (unsigned int j = 0; j < img.num_columns(); ++j)
		{
			if (img.GetPixel(pixel.first, pixel.second) < img.GetPixel(i,j))
			{
				pixel = make_pair(i,j);
			}
		}
	}
	return pixel;
}

auto get_z(int center_x, int center_y, int radius);
auto compute_normal(Image &img, pair<int,int> pixel);

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

	auto bright1 = get_brightest_pixel(sphere1);
	cout << "Brightest pixel found at: "
		 << "("  << bright1.first << "," << bright1.second << ")" << endl;
	cout << "Brightness value: " << sphere1.GetPixel(bright1.first, bright1.second) << endl;

	if (!ReadImage(image2, &sphere2))
	{
		cout << "Can\'t read file " << image2 << ", sorry." << endl;
		return 0;
	}

	auto bright2 = get_brightest_pixel(sphere2);
	cout << "Brightest pixel found at: "
		 << "("  << bright2.first << "," << bright2.second << ")" << endl;
	cout << "Brightness value: " << sphere2.GetPixel(bright2.first, bright2.second) << endl;

	if (!ReadImage(image3, &sphere3))
	{
		cout << "Can\'t read file " << image3 << ", sorry." << endl;
		return 0;
	}

	auto bright3 = get_brightest_pixel(sphere3);
	cout << "Brightest pixel found at: "
		 << "("  << bright3.first << "," << bright3.second << ")" << endl;
	cout << "Brightness value: " << sphere3.GetPixel(bright3.first, bright3.second) << endl;

	return 0;
}