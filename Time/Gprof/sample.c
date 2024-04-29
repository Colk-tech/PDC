// gprof: sample.c
//
#include <stdio.h>
#include <stdlib.h>

int a(void) {
    int i = 0, g = 0;
    for (i = 0; i < 100000; i++) {
        g += i;
    }
    return g;
}

int b(void) {
    int i = 0, g = 0;
    for (i = 0; i < 4; i++) {
        g += a();
    }
    return g;
}

int main(void) {
    int i, j, g = 0;
    for (i = 0; i < 10000; i++) {
        a();
        b();
    }
    for (j = 0; j < 30000; j++) {
        g += j;
    }
    return EXIT_SUCCESS;
}
