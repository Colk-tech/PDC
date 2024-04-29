#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h> // sqrt を使うんで

#define NUM 10000  // NUM以下の素数を求める

int main(void) {
    unsigned i, j, k;
    unsigned prime[NUM];
    unsigned sq_num = (int) sqrt((double) NUM);

    struct timespec start, end;
    double elapsed;

    // prime[i] は 整数 i+1 に対応：prime[0]は整数1
    // 1ならば素数（の候補）
    // 0ならば合成数（素数ではない）

    // 全ての数を素数候補にする
    for (i = 0; i < NUM; i++)
        prime[i] = 1;

    /* 開始時間の計測 */
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("start_ctime = sec:%ld nsec:%ld\n", start.tv_sec, start.tv_nsec);

    //エラトステネスの篩
    prime[0] = 0;    // 1は素数ではない
    for (i = 1; i < sq_num; i++) { // 2以上 sqrt(NUM) について 
        if (prime[i] == 1) {          // i+1 が素数なら
            j = i + 1; //本来の数値
            for (k = j + j; k <= NUM; k += j) {
                prime[k - 1] = 0;  // 素数の倍数は素数ではない
            }
        }
    }

    /* 終了時間の計測 */
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("end_ctime = sec:%ld nsec:%ld\n", end.tv_sec, end.tv_nsec);

    /* 表示 */
    for (i = 0; i < NUM; i++)
        if (prime[i] == 1)  // 1が立っていたら i+1 が素数
            printf("%3d\t", i + 1);
    putchar('\n');

    /* 経過時間の計算 */
    elapsed = (double) (end.tv_sec - start.tv_sec);
    elapsed += (double) (end.tv_nsec - start.tv_nsec) * 1e-9;

    printf("total processing time: %lf sec\n", elapsed);
    return EXIT_SUCCESS;
}
