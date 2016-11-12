*************************************************
Title:          README.txt
Author:         Abdullah Khan
Date Created:   2016-10-09
Class:          [CSCI 493.69] Computer Vision
Professor:      Stamos
Purpose:        Homework #4
*************************************************

# "Photometric Stereo"

## A vision system that recovers the orientation and reflectance of an object’s surface using photometric stereo.

I. Parts Completed
- s1
- s2
- s3
- s4


II. Bugs Encountered
- s1: Use threshold >= 75. Anything lower than 75 will cause the program to abort.
    - I don't know why this happens.

III. Run Instructions
- Run `make` to build
- ./s1 {input original image} {input threshold value} {output parameters file}
        I used a threshold value of 100.
        Formula:
        1. Make a binary image and count all the white pixels for the area.
        2. To get the center: for every white pixel (255) I add all the x and y coordinates
        	to an accumulator.
        	Then I divide the accumulated X and Y values by the area which gives me the center
        	of the circle.
        3. For the radius I count from the center and move outwards north, south, east, and west
        	until I hit black. I take the absolute value of the difference in pixels in directions
        	opposite each other.
        	difference of left and right = abs(left - right)
        	difference of up and down = abs(up - down)
        	Then I take the mean of the two, and that's my radius.

- ./s2 {input parameters file} {image 1} {image 2} {image 3} {output directions file}
	To find the normal, I use this equation:
	(Xb - Xc)^2 + (Yb - Yc)^2 + (Z - Zc)^2 = R^2
	Where R is the radius (known), Xb and Yb are the brightest pixels in the image,
	and Xc and Yc are the center of the image.
	I solve for the difference of Zs since that's my only unknown.
	auto z_squared = pow(radius, 2) - pow(x_diff, 2) - pow(y_diff, 2);
	I take the square root of that, and multiply by -1 and that's my difference of Zs.

	Then I scale by multiplying each component by the value of the brightest pixel, and
	dividing by the magnitude of the normal vector.

Information used for inverting matrices found here:
	http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

- ./s3 {input directions} {image 1} {image 2} {image 3} {step} {threshold} {output}
		I used a step value of 9 and a threshold of 90.
		I take the directions computed and use that as my matrix, find the determinant
		and inverse of my matrix.
		For each pixel I step through, I make a vector of all brightness values for the 3 images.
		If all values are above the threshold, I multiply this vector by the inverse matrix I calculated earlier.
		I calculate my magnitude to scale the vector and draw my lines.

- ./s4 {input directions} {image 1} {image 2} {image 3} {threshold} {output}
		I used a threshold value of 100.
		Same as above, except no stepping and no drawing lines.

IV. Input and Output Files
	User's PGM images.
	Text file
