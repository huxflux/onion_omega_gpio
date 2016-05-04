/*
 * Testshit for GPIO library
 *
 * Copyright (C) 2016 Sildradassen Software
 *
 */

#include <stdio.h>
#include "gpio.h"

#define MIN_DELAY_VALUE 1
#define MAX_DELAY_VALUE 300

int main(int argc, char *argv[])
{
    int counter = 250;
    srand(time(NULL));

    gpio_open(15);
    gpio_open(16);
    gpio_open(17);

    gpio_set_direction(15, "out");
    gpio_set_direction(16, "out");
    gpio_set_direction(17, "out");

    /* blink leds randomly with random delay */
    while (counter > 0) {
        gpio_set(random(15, 17), random(0, 1));
        delay(random(0, random(MIN_DELAY_VALUE, MAX_DELAY_VALUE)));
        counter--;
    }

    /* Turn off all leds */
    gpio_set(17,1);
    gpio_set(16,1);
    gpio_set(15,1);

    gpio_close_all();

    return 0;
}
