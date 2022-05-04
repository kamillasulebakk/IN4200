#ifndef PARALLEL_FUNCTIONS_H
#define PARALLEL_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>

#include "../serial_code/functions.h"

void send_and_receive_overlap(image *u);
void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, const int iters);

#endif
