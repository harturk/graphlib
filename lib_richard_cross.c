#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *imageR = &data;

int convolving2x2(int j, int i, int weight[2][2])
{
    int pixelValue = 0;

    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            int greyScaleR = imageR->pix[(j + y) * imageR->width + (i + x)].r * 0.299;
            int greyScaleG = imageR->pix[(j + y) * imageR->width + (i + x)].g * 0.587;
            int greyScaleB = imageR->pix[(j + y) * imageR->width + (i + x)].b * 0.114;
            pixelValue = pixelValue + weight[x][y] * (greyScaleR + greyScaleG + greyScaleB);
        }
    }

    return pixelValue;
}

void richardCross()
{
    int r = read_ppm("images/lena.ppm", imageR);

    // Roberts Cross
    if (r == 0)
    {

        int gxWeight[2][2] = {
            {1, 0},
            {0, -1}};

        int gyWeight[2][2] = {
            {0, 1},
            {-1, 0}};

        for (int j = 1; j < imageR->height - 1; j++)
        {
            for (int i = 1; i < imageR->width - 1; i++)
            {
                int gx = convolving2x2(j, i, gxWeight);
                int gy = convolving2x2(j, i, gyWeight);

                imageR->pix[j * imageR->width + i].r = abs(gx) + abs(gy);
                imageR->pix[j * imageR->width + i].g = abs(gx) + abs(gy);
                imageR->pix[j * imageR->width + i].b = abs(gx) + abs(gy);
            }
        }

        write_ppm("./4-rc_test.ppm", imageR);
        free_ppm(imageR);
    }
}