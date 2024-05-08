/*
 * simple1.c -- スレッドを２つ作るプログラム
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *func1(void *x);

void *func2(void *x);

int main(void) {
    pthread_t t1;
    pthread_t t2;
    int a = 10;
    int b = 20;

    pthread_create(&t1, NULL, func1, (void *) &a); /* スレッド1の生成 */
    pthread_create(&t2, NULL, func2, (void *) &b); /* スレッド2の生成 */

    printf("main()\n");
    pthread_join(t1, NULL); /* スレッド1の終了 */
    pthread_join(t2, NULL); /* スレッド2の終了 */
    return EXIT_SUCCESS;
}

void *func1(void *x) { /* スレッド1の処理 */
    int i;
    int p;

    // int 型のポインタに変換 → * で実体にアクセス
    p = *((int *) x);
    for (i = 0; i < 3; i++) {
        printf("func1( %d ): %d \n", p, i);
    }
    pthread_exit(NULL);
}

void *func2(void *x) { /* スレッド2の処理 */
    int i;
    int p;

    // int 型のポインタに変換 → * で実体にアクセス
    p = *((int *) x);
    for (i = 0; i < 3; i++) {
        printf("func2( %d ): %d \n", p, i);
    }
    pthread_exit(NULL);
}
