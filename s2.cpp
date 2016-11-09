/*
 * Author: Abdullah Khan
 * s2: Brightness and directions.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <cmath>
#include <tuple>
#include <fstream>
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

auto compute_normal(pair<int,int> pixel, pair<int,int> center, int radius)
{
	int x_diff = pixel.first - center.first;
	int y_diff = pixel.second - center.second;
	auto z_squared = pow(radius, 2) - pow(x_diff, 2) - pow(y_diff, 2);
	auto z = sqrt(z_squared);
	return make_tuple(x_diff, y_diff, z);
}

auto scale_normal(tuple<int, int, int> normal)
{
	int x = get<0>(normal);
	int y = get<1>(normal);
	int z = get<2>(normal);
	auto magnitude = sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
	return make_tuple((double)(x/magnitude), (double)(y/magnitude), (double)(z/magnitude));
}

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

	auto center_sphere = make_pair(center_x, center_y);

	Image sphere1, sphere2, sphere3;
	if (!ReadImage(image1, &sphere1))
	{
		cout << "Can\'t read file " << image1 << ", sorry." << endl;
		return 0;
	}

	auto bright1 = get_brightest_pixel(sphere1);
	auto normal1 = compute_normal(bright1, center_sphere, radius);
	auto scale1 = scale_normal(normal1);

	if (!ReadImage(image2, &sphere2))
	{
		cout << "Can\'t read file " << image2 << ", sorry." << endl;
		return 0;
	}

	auto bright2 = get_brightest_pixel(sphere2);
	auto normal2 = compute_normal(bright2, center_sphere, radius);
	auto scale2 = scale_normal(normal2);

	if (!ReadImage(image3, &sphere3))
	{
		cout << "Can\'t read file " << image3 << ", sorry." << endl;
		return 0;
	}

	auto bright3 = get_brightest_pixel(sphere3);
	auto normal3 = compute_normal(bright3, center_sphere, radius);
	auto scale3 = scale_normal(normal3);

	{
		fstream directions(output_directions, std::ios::out);
		if(!directions.is_open())
		{
			cout << output_directions << " can't be opened for reading." << endl;
			return 0;
		}
		directions << get<0>(normal1) << " " << get<1>(normal1) << " " << get<2>(normal1) << endl;
		directions << get<0>(normal2) << " " << get<1>(normal2) << " " << get<2>(normal2) << endl;
		directions << get<0>(normal3) << " " << get<1>(normal3) << " " << get<2>(normal3) << endl;
		directions.close();
	} // Read parameter file into variables.

	return 0;
}
