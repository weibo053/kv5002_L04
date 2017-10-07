#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>

#include "console.h"

void *led_toggle_white_thr(void * arg) {
    while (true) {
        led_toggle(LED_WHITE);
        usleep(1000000);
    }
    pthread_exit(NULL);
}

void *led_toggle_red_thr(void * arg) {
    while (true) {
        led_toggle(LED_RED);
        usleep(500000);
    }
    pthread_exit(NULL);
}

int main (void) {
    pthread_t thread[2];
    int rc;

    console_init();

    rc = pthread_create(&thread[0], NULL, led_toggle_white_thr, NULL);
    assert(rc == 0);

    rc = pthread_create(&thread[1], NULL, led_toggle_red_thr, NULL);
    assert(rc == 0);

    rc = pthread_join(thread[0], NULL);
    assert(rc == 0);

    rc = pthread_join(thread[1], NULL);
    assert(rc == 0);

    exit(0);
}
