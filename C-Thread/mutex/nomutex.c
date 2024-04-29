/*
 *   nomutex.c -- ロックなしで共有資源にアクセスするプログラム
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_A(void *x), *thread_B(void *x);

int shared_resource;

int main(void) {
    pthread_t t1;
    pthread_t t2;
    shared_resource = 0;

    pthread_create(&t1, NULL, thread_A, NULL); /* スレッド1の生成 */
    pthread_create(&t2, NULL, thread_B, NULL); /* スレッド2の生成 */
    pthread_join(t1, NULL); /* スレッド1の終了まち */
    pthread_join(t2, NULL); /* スレッド2の終了まち */

    printf("main(): shared_resource == %d\n", shared_resource);
    /* 共有資源の値を出力 */
    return EXIT_SUCCESS;
}

void *thread_A(void *x) { /* スレッド1の処理, 1を100万回加える */
    int i;
    for (i = 0; i < 1000000; i++) {
        shared_resource++;
    }
    pthread_exit(NULL);
}

void *thread_B(void *x) { /* スレッド2の処理, 1を100万回加える */
    int i;
    for (i = 0; i < 1000000; i++) {
        shared_resource++;
    }
    pthread_exit(NULL);
}
