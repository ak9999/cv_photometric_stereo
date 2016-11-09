/*
 * Author: Abdullah Khan
 * s2: Brightness and directions.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <tuple>
#include <fstream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

auto get_brightest_pixel(Image &img)
{
	auto pixel = make_tuple(0,0);
	for (unsigned int i = 0; i < img.num_rows(); ++i)
	{
		for (unsigned int j = 0; j < img.num_columns(); ++j)
		{
			if (img.GetPixel(get<0>(pixel), get<1>(pixel)) < img.GetPixel(i,j))
			{
				pixel = make_tuple(i,j);
			}
		}
	}
	return pixel;
}

auto compute_normal(tuple<int,int> pixel, tuple<int,int> center, int radius)
{
	int x_diff = get<0>(pixel) - get<0>(center);
	int y_diff = get<1>(pixel) - get<1>(center);
	auto z_squared = pow(radius, 2) - pow(x_diff, 2) - pow(y_diff, 2);
	auto z = -1 * sqrt(z_squared);
	return make_tuple(x_diff, y_diff, z);
}

auto scale_normal(int brightest, tuple<int, int, int> normal)
{
	int x = get<0>(normal);
	int y = get<1>(normal);
	int z = get<2>(normal);
	double magnitude = sqrt( pow(x,2) + pow(y,2) + pow(z,2) );

	double x_new = (brightest*x)/magnitude;
	double y_new = (brightest*y)/magnitude;
	double z_new = (brightest*z)/magnitude;
	return make_tuple(x_new, y_new, z_new);
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

	auto center_sphere = make_tuple(center_x, center_y);

	Image sphere1, sphere2, sphere3;
	if (!ReadImage(image1, &sphere1))
	{
		cout << "Can\'t read file " << image1 << ", sorry." << endl;
		return 0;
	}

	auto bright1 = get_brightest_pixel(sphere1);
	int pixel1 = sphere1.GetPixel(get<0>(bright1), get<1>(bright1));
	auto normal1 = compute_normal(bright1, center_sphere, radius);
	auto scale1 = scale_normal(pixel1, normal1);

	if (!ReadImage(image2, &sphere2))
	{
		cout << "Can\'t read file " << image2 << ", sorry." << endl;
		return 0;
	}

	auto bright2 = get_brightest_pixel(sphere2);
	int pixel2 = sphere2.GetPixel(get<0>(bright2), get<1>(bright2));
	auto normal2 = compute_normal(bright2, center_sphere, radius);
	auto scale2 = scale_normal(pixel2, normal2);

	if (!ReadImage(image3, &sphere3))
	{
		cout << "Can\'t read file " << image3 << ", sorry." << endl;
		return 0;
	}

	auto bright3 = get_brightest_pixel(sphere3);
	int pixel3 = sphere3.GetPixel(get<0>(bright3), get<1>(bright3));
	auto normal3 = compute_normal(bright3, center_sphere, radius);
	auto scale3 = scale_normal(pixel3, normal3);

	{
		fstream directions(output_directions, std::ios::out);
		if(!directions.is_open())
		{
			cout << output_directions << " can't be opened for reading." << endl;
			return 0;
		}
		directions << get<0>(scale1) << " " << get<1>(scale1) << " " << get<2>(scale1) << endl;
		directions << get<0>(scale2) << " " << get<1>(scale2) << " " << get<2>(scale2) << endl;
		directions << get<0>(scale3) << " " << get<1>(scale3) << " " << get<2>(scale3) << endl;
		directions.close();
	} // Read parameter file into variables.

	return 0;
}
