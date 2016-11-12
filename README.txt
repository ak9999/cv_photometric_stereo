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

- ./s2 {input parameters file} {image 1} {image 2} {image 3} {output directions file}

- ./s3 {input directions} {image 1} {image 2} {image 3} {step} {threshold} {output}
		I used a step value of 9 and a threshold of 90.

- ./s4 {input directions} {image 1} {image 2} {image 3} {threshold} {output}
		I used a threshold value of 100.

IV. Input and Output Files
	User's PGM images.
	Text file
