#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    struct timespec t1, t2;

    clock_gettime(CLOCK_REALTIME, &t1);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    printf("REALTIME = sec:%ld nsec:%ld\n", t1.tv_sec, t1.tv_nsec);
    printf("MONOTONIC = sec:%ld nsec:%ld\n\n", t2.tv_sec, t2.tv_nsec);

    printf("sizeof tv_sec is : %lu byte\n", sizeof(t1.tv_sec));

    return EXIT_SUCCESS;
}
