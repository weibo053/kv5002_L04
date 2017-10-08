#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>

#include "console.h"

typedef struct {
    leds_t led;
    int    rate;
} thread_args_t;

void *led_toggle_thr(void * arg) {
    leds_t led = ((thread_args_t *)arg)->led;
    int delay = (int)(1000000 / ((thread_args_t *)arg)->rate);

    while (true) {
        led_toggle(led);
        usleep(delay);
    }
    pthread_exit(NULL);
}

int main (void) {
    pthread_t thread[4];
    thread_args_t args[] = {
        {LED_WHITE, 1},
        {LED_RED,   2},
        {LED_GREEN, 4},
        {LED_BLUE,  8}
    };
    int rc;
    unsigned long i;

    console_init();

    for (i = 0; i < 4; i += 1) {
        rc = pthread_create(&thread[i], NULL, led_toggle_thr, &args[i]);
        assert(rc == 0);
    }

    for (i = 0; i < 4; i += 1) {
        rc = pthread_join(thread[i], NULL);
        assert(rc == 0);
    }

    exit(0);
}
