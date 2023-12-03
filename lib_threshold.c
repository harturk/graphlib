#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *imageT = &data;

void threshold(int weight)
{
    int r = read_ppm("images/lena.ppm", imageT);

    if (r == 0)
    {
        for (int j = 0; j < imageT->height; j++)
        {
            for (int i = 0; i < imageT->width; i++)
            {
                int greyScaleR = imageT->pix[j * imageT->width + i].r * 0.299;
                int greyScaleG = imageT->pix[j * imageT->width + i].g * 0.587;
                int greyScaleB = imageT->pix[j * imageT->width + i].b * 0.114;
                int result = (greyScaleR + greyScaleG + greyScaleB) > weight ? 0 : 255;
                imageT->pix[j * imageT->width + i].r = result;
                imageT->pix[j * imageT->width + i].g = result;
                imageT->pix[j * imageT->width + i].b = result;
            }
        }

        write_ppm("./2-threshold_test.ppm", imageT);
        free_ppm(imageT);
    }
}