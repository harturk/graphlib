struct image_s
{
    int width;
    int height;
    struct pixel_s *pix;
};

int convolving3x3(int j, int i, int weigth[3][3]);
void sobel();