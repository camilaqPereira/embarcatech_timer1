#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"


#define SEMAPHORE_DELAY 3000

const uint GPIO_RED_LED = 13;
const uint GPIO_YELLOW_LED = 12;
const uint GPIO_GREEN_LED = 11;

const uint target_mask = 0b11100000000000;
static volatile uint semaphore_activation_mask = 4;

/* Function prototype*/
bool semaphore_callback(struct repeating_timer *timer);

int main()
{
    struct repeating_timer semaphore_timer;

    /* Initialize pins*/
    stdio_init_all();

    gpio_init_mask(target_mask);
    gpio_set_dir_masked(target_mask, target_mask);

    /* Set repeating timer*/

    add_repeating_timer_ms(SEMAPHORE_DELAY, &semaphore_callback, NULL, &semaphore_timer);

    while (true) {
        printf("TIC TAC: 1 second!\n");
        sleep_ms(1000);
    }
}



bool semaphore_callback(struct repeating_timer *timer){
    gpio_put_masked(target_mask, semaphore_activation_mask << 11);
    semaphore_activation_mask = semaphore_activation_mask >> 1;

    if(!semaphore_activation_mask) semaphore_activation_mask = 4;
}