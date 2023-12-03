#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *imageG = &data;

void grey()
{
    int r = read_ppm("images/lena.ppm", imageG);

    if (r == 0)
    {
        for (int j = 0; j < imageG->height; j++)
        {
            for (int i = 0; i < imageG->width; i++)
            {
                int greyScaleR = imageG->pix[j * imageG->width + i].r * 0.299;
                int greyScaleG = imageG->pix[j * imageG->width + i].g * 0.587;
                int greyScaleB = imageG->pix[j * imageG->width + i].b * 0.114;
                imageG->pix[j * imageG->width + i].r = (greyScaleR + greyScaleG + greyScaleB);
                imageG->pix[j * imageG->width + i].g = (greyScaleR + greyScaleG + greyScaleB);
                imageG->pix[j * imageG->width + i].b = (greyScaleR + greyScaleG + greyScaleB);
            }
        }

        write_ppm("./1-grey_test.ppm", imageG);
        free_ppm(imageG);
    }
}