#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *image = &data;

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

void sobel(int r)
{
    int r = read_ppm("images/lena.ppm", image);

    if (r == 0)
    {
        for (int j = 0; j < image->height; j++)
        {
            for (int i = 0; i < image->width; i++)
            {
                int greyScaleR = image->pix[j * image->width + i].r * 0.299;
                int greyScaleG = image->pix[j * image->width + i].g * 0.587;
                int greyScaleB = image->pix[j * image->width + i].b * 0.114;
                image->pix[j * image->width + i].r = (greyScaleR + greyScaleG + greyScaleB);
                image->pix[j * image->width + i].g = (greyScaleR + greyScaleG + greyScaleB);
                image->pix[j * image->width + i].b = (greyScaleR + greyScaleG + greyScaleB);
            }
        }

        write_ppm("1-grey_test.ppm", image);
        free_ppm(image);
    }

    return 0;
}