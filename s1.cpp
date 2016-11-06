/*
 * Author: Abdullah Khan
 * s1: Locate sphere in an image and compute the center and radius.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <utility>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int GetCircleArea(Image &img);
pair<int,int> GetCircleCenter(Image &img, int area);
int GetCircleRadius(Image &img, int center_x, int center_y);

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
	img.SetNumberGrayLevels(1);

	int area = GetCircleArea(img);

	auto p = GetCircleCenter(img, area);

	int radius = GetCircleRadius(img, p.first, p.second);

	cout << "Area: " << area << endl;
	cout << "Centroid: (" << p.first << "," << p.second << ")" << endl;
	cout << "Radius: " << radius << endl;

	{
		fstream of(output, std::ios::out);
		if(!of.is_open())
		{
			cout << "Could not open " << output << " for writing. Exiting." << endl;
			return 0;
		}

		of << p.first << " " << p.second << " " << radius << endl;
		of.close();
	}

	return 0;
}

// Precondition: Image MUST be binary.
int GetCircleArea(Image &img)
{
	int area = 0;

	for (unsigned int i = 0; i < img.num_rows(); i++)
	{
		for (unsigned int j = 0; j < img.num_columns(); j++)
		{
			// Just count every white pixel.
			if (img.GetPixel(i,j) != 0) { area += 1; }
		}
	}

	return area;
}

// Precondition: Image MUST be binary.
pair<int,int> GetCircleCenter(Image &img, int area)
{
	int X = 0; int Y = 0;

	for (unsigned int i = 0; i < img.num_rows(); i++)
	{
		for (unsigned int j = 0; j < img.num_columns(); j++)
		{
			if (img.GetPixel(i,j) == 1)
			{
				X += i;
				Y += j;
			}
		}
	}
	int x = X / (double)area;
	int y = Y / (double)area;

	return make_pair(x,y);
}

// Precondition: Image MUST be binary.
int GetCircleRadius(Image &img, int center_x, int center_y)
{
	int r_up = 0; int r_down = 0; int r_left = 0; int r_right = 0;

	int counter = 0;
	int current_pixel = img.GetPixel(center_x, center_y);
	while (current_pixel != 0) // Going down.
	{
		counter++;
		current_pixel = img.GetPixel(center_x, center_y + counter);
		if (current_pixel != 0) { ++r_up; }
	}

	counter = 0; // Reset counter.
	current_pixel = img.GetPixel(center_x, center_y); // Reset current pixel.
	while (current_pixel != 0) // Going up.
	{
		counter++;
		current_pixel = img.GetPixel(center_x, center_y - counter);
		if (current_pixel != 0) { ++r_down; }
	}

	counter = 0; // Reset counter.
	current_pixel = img.GetPixel(center_x, center_y); // Reset current pixel.
	while (current_pixel != 0) // Going left.
	{
		counter++;
		current_pixel = img.GetPixel(center_x - counter, center_y);
		if (current_pixel != 0) { ++r_down; }
	}

	counter = 0; // Reset counter.
	current_pixel = img.GetPixel(center_x, center_y); // Reset current pixel.
	while (current_pixel != 0) // Going right.
	{
		counter++;
		current_pixel = img.GetPixel(center_x + counter, center_y);
		if (current_pixel != 0) { ++r_down; }
	}

	double d_leftright = abs(r_right - r_left);
	double d_updown = abs(r_down - r_up);

	int radius = (d_leftright + d_updown) / 2;

	return radius;
}
