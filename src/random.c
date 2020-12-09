//
// Created by Saaketh Vangati on 12/7/20.
//

#include "../include/random.h"

#include <stdlib.h>

int rand_int()
{
    return rand();
}

float rand_float()
{
    return (float) rand() / (float) RAND_MAX;
}
