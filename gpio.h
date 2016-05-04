/*
 * Library for manipulating GPIO's on the Onion Omega
 *
 * Copyright (C) 2016 Sildradassen Software
 *
 */

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int gpio_get(int gpio_number);
int gpio_set_direction(int gpio_number, char in_or_out[]);
int gpio_set(int gpio_number, int value);
int gpio_open(int gpio_number);
int gpio_close(int gpio_number);
int gpio_close_all();
int delay(int ms);
int random(int min_value, int max_value);
