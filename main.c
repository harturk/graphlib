#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *image = &data;

void display_pixel(uint16_t x0, uint16_t y0, uint32_t color)
{
	image->pix[y0 * image->width + x0].r = (color & 0xff0000) >> 16;
	image->pix[y0 * image->width + x0].g = (color & 0x00ff00) >> 8;
	image->pix[y0 * image->width + x0].b = (color & 0x0000ff);
}

int convolving3x3(int j, int i, int weigth[3][3])
{
	int pixelValue = 0;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			int greyScaleR = image->pix[(j + y) * image->width + (i + x)].r * 0.299;
			int greyScaleG = image->pix[(j + y) * image->width + (i + x)].g * 0.587;
			int greyScaleB = image->pix[(j + y) * image->width + (i + x)].b * 0.114;
			pixelValue = pixelValue + weigth[x][y] * (greyScaleR + greyScaleG + greyScaleB);
		}
	}

	return pixelValue;
}

int convolving2x2(int j, int i, int weigth[2][2])
{
	int pixelValue = 0;

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			int greyScaleR = image->pix[(j + y) * image->width + (i + x)].r * 0.299;
			int greyScaleG = image->pix[(j + y) * image->width + (i + x)].g * 0.587;
			int greyScaleB = image->pix[(j + y) * image->width + (i + x)].b * 0.114;
			pixelValue = pixelValue + weigth[x][y] * (greyScaleR + greyScaleG + greyScaleB);
		}
	}

	return pixelValue;
}

int main(void)
{
	int i, j, r;

	r = read_ppm("images/lena.ppm", image);

	// if (r == 0) {
	// 	printf("width: %d, height: %d\n", image->width, image->height);
	// 	for (j = 0; j < image->height; j++) {
	// 		for (i = 0; i < image->width; i++) {
	// 			printf("(%d %d) %02x %02x %02x\n", i, j,
	// 				image->pix[j * image->width + i].r,
	// 				image->pix[j * image->width + i].g,
	// 				image->pix[j * image->width + i].b);

	// 		}
	// 	}

	// 	image->pix[50 * image->width + 20].r = 255;
	// 	image->pix[50 * image->width + 20].g = 255;
	// 	image->pix[50 * image->width + 20].b = 255;

	// 	write_ppm("lena_copy.ppm", image);

	// 	free_ppm(image);
	// }

	// r = new_ppm(image, 675, 428);

	// if (r == 0) {
	// 	for (j = 0; j < 15; j++) {
	// 		for (i = 0; i < 25; i++) {
	// 			image->pix[(100 + j) * image->width + 125 + i].r = 255;
	// 			image->pix[(27 + j) * image->width + 440 + i].g = 255;

	// 			image->pix[(371 + j) * image->width + 10 + i].r = 192;
	// 			image->pix[(371 + j) * image->width + 10 + i].g = 192;
	// 			image->pix[(371 + j) * image->width + 10 + i].b = 192;
	// 		}
	// 	}

	// 	write_ppm("test.ppm", image);
	// 	free_ppm(image);
	// }

	// Grey
	// if (r == 0) {
	// 	for (j = 0; j < image->height; j++) {
	// 		for (i = 0; i < image->width; i++) {
	// 			int greyScaleR = image->pix[j * image->width + i].r * 0.299;
	// 			int greyScaleG = image->pix[j * image->width + i].g * 0.587;
	// 			int greyScaleB = image->pix[j * image->width + i].b * 0.114;
	// 			image->pix[j * image->width + i].r = (greyScaleR + greyScaleG + greyScaleB);
	// 			image->pix[j * image->width + i].g = (greyScaleR + greyScaleG + greyScaleB);
	// 			image->pix[j * image->width + i].b = (greyScaleR + greyScaleG + greyScaleB);
	// 		}
	// 	}

	// 	write_ppm("grey_test.ppm", image);
	// 	free_ppm(image);
	// }

	// Threshold (50)
	// if (r == 0) {
	// 	for (j = 0; j < image->height; j++) {
	// 		for (i = 0; i < image->width; i++) {
	// 			int greyScaleR = image->pix[j * image->width + i].r * 0.299;
	// 			int greyScaleG = image->pix[j * image->width + i].g * 0.587;
	// 			int greyScaleB = image->pix[j * image->width + i].b * 0.114;
	// 			int result = (greyScaleR + greyScaleG + greyScaleB) > 50 ? 0 : 255;
	// 			image->pix[j * image->width + i].r = result;
	// 			image->pix[j * image->width + i].g = result;
	// 			image->pix[j * image->width + i].b = result;
	// 		}
	// 	}

	// 	write_ppm("threshold_test.ppm", image);
	// 	free_ppm(image);
	// }

	// Sobel
	// j-1 i-1		j i-1	i-1 j+1
	// j-1 i 		j i		j+i i
	// j-1 i+1		j i+1	j+1 i+1

	// G(x)
	// -1			0			+1
	// -2			0			+2
	// -1			0			+1

	// G(y)
	// +1			+2			+1
	//	0			 0			 0
	// -1			-2			-1

	// if (r == 0)
	// {

	// 	int gxWeigth[3][3] = {
	// 		{-1, 0, 1},
	// 		{-2, 0, 2},
	// 		{-1, 0, 1}};

	// 	int gyWeigth[3][3] = {
	// 		{1, 2, 1},
	// 		{0, 0, 0},
	// 		{-1, -2, -1}};

	// 	for (j = 1; j < image->height - 1; j++)
	// 	{
	// 		for (i = 1; i < image->width - 1; i++)
	// 		{
	// 			int gx = convolving3x3(j, i, gxWeigth);
	// 			int gy = convolving3x3(j, i, gyWeigth);

	// 			image->pix[j * image->width + i].r = abs(gx) + abs(gy);
	// 			image->pix[j * image->width + i].g = abs(gx) + abs(gy);
	// 			image->pix[j * image->width + i].b = abs(gx) + abs(gy);
	// 		}
	// 	}

	// 	write_ppm("sobel_test.ppm", image);
	// 	free_ppm(image);
	// }

	// Roberts Cross
	if (r == 0)
	{

		int gxWeigth[2][2] = {
			{1, 0},
			{0, -1}};

		int gyWeigth[2][2] = {
			{0, 1},
			{-1, 0}};

		for (j = 1; j < image->height - 1; j++)
		{
			for (i = 1; i < image->width - 1; i++)
			{
				int gx = convolving2x2(j, i, gxWeigth);
				int gy = convolving2x2(j, i, gyWeigth);

				image->pix[j * image->width + i].r = abs(gx) + abs(gy);
				image->pix[j * image->width + i].g = abs(gx) + abs(gy);
				image->pix[j * image->width + i].b = abs(gx) + abs(gy);
			}
		}

		write_ppm("rc_test.ppm", image);
		free_ppm(image);
	}

	return 0;
}
