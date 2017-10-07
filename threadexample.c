#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>

#include "console.h"

void *led_toggle_thr(void * arg) {
    while (true) {
        led_toggle((leds_t)arg);
        usleep(1000000);
    }
    pthread_exit(NULL);
}

int main (void) {
    pthread_t thread[4];
    int rc;
    unsigned long i;

    console_init();

    for (i = 0; i < 4; i += 1) {
        rc = pthread_create(&thread[i], NULL, led_toggle_thr, (void *)i);
        assert(rc == 0);
    }

    for (i = 0; i < 4; i += 1) {
        rc = pthread_join(thread[i], NULL);
        assert(rc == 0);
    }

    exit(0);
}
