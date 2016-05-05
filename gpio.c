/*
 * Library for manipulating GPIO's on the Onion Omega
 *
 * Copyright (C) 2016 Sildradassen Software
 *
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gpio.h"

#define GPIO_MAIN_DIRECTORY "/sys/class/gpio/"
#define GPIO_MAX_NUMBER 30

static int gpio_list[GPIO_MAX_NUMBER] = {0};

int gpio_get(int gpio_number)
{
    FILE *fp;
    char filename[50] = GPIO_MAIN_DIRECTORY;
    char str[3];
    int value;

    if (gpio_list[gpio_number] != 1) {
        return EXIT_FAILURE;
    }

    strcat(filename, "gpio");
    sprintf(str, "%d", gpio_number);
    strcat(filename, str);
    strcat(filename, "/value");

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    value = getc(fp);

    fclose(fp);

    return value - 48; /* 48 is the ascii-value for '0' */
}

int gpio_set_direction(int gpio_number, char in_or_out[])
{
    FILE *fp;
    char filename[50] = GPIO_MAIN_DIRECTORY;
    char str[3];

    if (gpio_list[gpio_number] != 1) {
        return EXIT_FAILURE;
    }
    
    strcat(filename, "gpio");
    sprintf(str, "%d", gpio_number);
    strcat(filename, str);
    strcat(filename, "/direction");

    fp = fopen(filename, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    fprintf(fp, in_or_out);
    fclose(fp);
    return EXIT_SUCCESS;
}

int gpio_set(int gpio_number, int value)
{
    FILE *fp;
    char filename[50] = GPIO_MAIN_DIRECTORY;
    char str[3];

    if (gpio_list[gpio_number] != 1) {
        return EXIT_FAILURE;
    }

    if (value > 0) {
        value = 1;
    }

    strcat(filename, "gpio");
    sprintf(str, "%d", gpio_number);
    strcat(filename, str);
    strcat(filename, "/value");

    fp = fopen(filename, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    sprintf(str, "%d", value);
    fprintf(fp, str);
    fclose(fp);

    return EXIT_SUCCESS;
}

int gpio_open(int gpio_number)
{
    FILE *fp;
    const char filename[] = "/sys/class/gpio/export";
    char str[3];

    gpio_list[gpio_number] = 1;

    fp = fopen(filename, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    sprintf(str, "%d", gpio_number);
    fprintf(fp, str);
    fclose(fp);

    return EXIT_SUCCESS;
}

int gpio_close(int gpio_number)
{
    FILE *fp;
    const char filename[] = "/sys/class/gpio/unexport";
    char str[3];

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open %s\n", filename);
        return EXIT_FAILURE;
    }

    sprintf(str, "%d", gpio_number);
    fprintf(fp, str);
    fclose(fp);
    return EXIT_SUCCESS;
}

int gpio_close_all()
{
    int i;
    for (i = 0; i < GPIO_MAX_NUMBER; i++) {
        if (gpio_list[i] == 1) {
            gpio_close(i);
            gpio_list[i] = 0;
        }
    }
    return EXIT_SUCCESS;
}

int delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause ) {
        now = clock();
    }
    return EXIT_SUCCESS;
}

int random(int min_value, int max_value)
{
    return rand() % (max_value + 1 - min_value) + min_value;
}
