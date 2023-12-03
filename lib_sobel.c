#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *imageSob = &data;

int convolving3x3(int j, int i, int weight[3][3])
{
    int pixelValue = 0;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            int greyScaleR = imageSob->pix[(j + y) * imageSob->width + (i + x)].r * 0.299;
            int greyScaleG = imageSob->pix[(j + y) * imageSob->width + (i + x)].g * 0.587;
            int greyScaleB = imageSob->pix[(j + y) * imageSob->width + (i + x)].b * 0.114;
            pixelValue = pixelValue + weight[x][y] * (greyScaleR + greyScaleG + greyScaleB);
        }
    }

    return pixelValue;
}

void sobel()
{
    int r = read_ppm("images/lena.ppm", imageSob);

    if (r == 0)
    {

        int gxWeight[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}};

        int gyWeight[3][3] = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}};

        for (int j = 1; j < imageSob->height - 1; j++)
        {
            for (int i = 1; i < imageSob->width - 1; i++)
            {
                int gx = convolving3x3(j, i, gxWeight);
                int gy = convolving3x3(j, i, gyWeight);

                imageSob->pix[j * imageSob->width + i].r = abs(gx) + abs(gy);
                imageSob->pix[j * imageSob->width + i].g = abs(gx) + abs(gy);
                imageSob->pix[j * imageSob->width + i].b = abs(gx) + abs(gy);
            }
        }

        write_ppm("./3-sobel_test.ppm", imageSob);
        free_ppm(imageSob);
    }
}