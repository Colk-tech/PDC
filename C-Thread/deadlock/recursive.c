/*
 * recursive.c : デッドロックしない利息計算
 */

#include <pthread.h>
#include <stdio.h>

#if defined(__APPLE__)
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#endif

#define RATE 0.05

void *thread_A(void *x), *thread_B(void *x);

int shared_resource;

pthread_mutex_t mutex1;

void deposit(int n) /* 預金の処理 */
{
    pthread_mutex_lock(&mutex1);
    shared_resource += n; /* 元金にn円を加算 */
    pthread_mutex_unlock(&mutex1);
}

void add_interest() /* 利息を加える処理 */
{
    int risoku;
    pthread_mutex_lock(&mutex1);
    risoku = (int) (shared_resource * RATE); /* 利息の計算 */
    deposit(risoku); /* 預金に利息を加算 */
    pthread_mutex_unlock(&mutex1);
}


int main() {
    pthread_t t1;
    pthread_t t2;

    shared_resource = 1000000;

    //  pthread_mutex_init( &mutex1, NULL );

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&mutex1, &attr);

    pthread_create(&t1, NULL, thread_A, NULL);
    pthread_create(&t2, NULL, thread_B, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("main(): shared_resource = %d\n", shared_resource); /* 預金高の確認 */
    return 0;
}

void *thread_A(void *x) {
    printf("thread_A(): deposit( 10000 ) ... \n"); /* これから10000円預金することの確認 */
    deposit(10000);        /* 10000円預金する */
    printf("thread_A(): deposit( 10000 ) done. \n"); /* 10000円預金したことの確認 */
    printf("thread_A(): shared_resource = %d\n", shared_resource); /* 預金高の確認 */
    pthread_exit(NULL);
}

void *thread_B(void *x) {
    printf("thread_B(): add_interest() ... \n"); /* これから利息を加算することの確認 */
    add_interest();           /* 利息を加算する処理の呼出し */
    printf("thread_B(): add_interest() done. \n"); /* 利息が加算されたことの確認 */
    printf("thread_B(): shared_resource = %d\n", shared_resource); /* 預金高の確認 */
    pthread_exit(NULL);
}
