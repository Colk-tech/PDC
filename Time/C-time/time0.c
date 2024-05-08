#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    struct timespec t1, t2;

    // システムの現在時刻をナノ秒単位で取得する。
    // しかし実際にその精度があるわけではない。
    clock_gettime(CLOCK_REALTIME, &t1);

    // ある開始時点からの単調増加の時間で表現されるクロックが取得できる。
    // 開始時点がどの時点となるかは規定されていない。
    // この時計は、システム時間の不連続な変化 (例えば、システム管理者がシステム時間を⼿動で変更した場合など) の影響を受けない。
    clock_gettime(CLOCK_MONOTONIC, &t2);

    printf("REALTIME = sec:%ld nsec:%ld\n", t1.tv_sec, t1.tv_nsec);
    printf("MONOTONIC = sec:%ld nsec:%ld\n\n", t2.tv_sec, t2.tv_nsec);

    printf("sizeof tv_sec is : %lu byte\n", sizeof(t1.tv_sec));

    return EXIT_SUCCESS;
}
