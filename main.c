#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib_ppm.h"
#include "lib_grey.h"
#include "lib_richard_cross.h"
#include "lib_sobel.h"
#include "lib_threshold.h"

struct image_s data;
struct image_s *image = &data;

int main(void)
{
	grey();
	sobel();

	int th = 0;
	printf("Informe um valor para o filtro de threshold.");
	scanf("%d", &th);
	threshold(th);

	richardCross();

	return 0;
}
