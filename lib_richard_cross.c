#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *image = &data;

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

void richardCross()
{
    int r = read_ppm("images/lena.ppm", image);

    // Roberts Cross
    if (r == 0)
    {

        int gxWeigth[2][2] = {
            {1, 0},
            {0, -1}};

        int gyWeigth[2][2] = {
            {0, 1},
            {-1, 0}};

        for (int j = 1; j < image->height - 1; j++)
        {
            for (int i = 1; i < image->width - 1; i++)
            {
                int gx = convolving2x2(j, i, gxWeigth);
                int gy = convolving2x2(j, i, gyWeigth);

                image->pix[j * image->width + i].r = abs(gx) + abs(gy);
                image->pix[j * image->width + i].g = abs(gx) + abs(gy);
                image->pix[j * image->width + i].b = abs(gx) + abs(gy);
            }
        }

        write_ppm("4-rc_test.ppm", image);
        free_ppm(image);
    }
}