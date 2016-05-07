/*
 * Defines the core functions of the library.
 *
 * Part of the Artificial Intelligence for Games system.
 *
 * Copyright (c) Ian Millington 2003-2006. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */
#include <stdlib.h>

#include "timing.h"
#include "core.h"

namespace aicore
{

    void randomSeed(unsigned value)
    {
        if (value == 0) {
            srand((unsigned)TimingData::get().getClock());
        } else {
            srand(value);
        }
    }

    /* Get a random number [0,max[ */
    int randomInt(int max)
    {
        return rand() % max;
    }

	float randomReal(float max)
    {
		return max * (float(rand()) / RAND_MAX);
    }

	float randomBinomial(float max)
    {
       return randomReal(max)-randomReal(max);
    }

    bool randomBoolean()
    {
        return (rand() % 2 == 0);
    }

}; // end of namespace
