/*
 * deadlock1.c : デッドロックを起こすプログラム
 */

#include <pthread.h>
#include <stdio.h>

#define RATE 0.05

void *thread_A(void *x), *thread_B(void *x);

int shared_resource;

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

int main() {
    pthread_t t1;
    pthread_t t2;
    shared_resource = 1000000;

    pthread_mutex_init(&mutex1, NULL);

    pthread_create(&t1, NULL, thread_A, 0);
    pthread_create(&t2, NULL, thread_B, 0);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("main(): shared_resource = %d\n", shared_resource); /* 預金高の確認 */
    return 0;
}

void *thread_A(void *x) {
    int i;
    pthread_mutex_lock(&mutex2);
    pthread_mutex_lock(&mutex1);

    for (i = 0; i < 100000; i++) {
        shared_resource += 5;
    }

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    pthread_exit(NULL);
}

void *thread_B(void *x) {
    int i;
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);

    for (i = 0; i < 100000; i++) {
        shared_resource += 5;
    }

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    pthread_exit(NULL);
}
