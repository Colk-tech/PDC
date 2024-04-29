/*
 * reader1.c -- Reader-Writer問題:ロックのみでやってみる
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *writer(void *x), *reader(void *x);

int buf = 0;
pthread_mutex_t mutex;

// reader/writerの数
#define RNUM 1
#define WNUM 1

// 識別用のIDとしてスレッドに渡す場所
int ids[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int main(void) {
    int i;
    //スレッドIDを保持するための配列
    pthread_t rth[RNUM];
    pthread_t wth[WNUM];

    //ロックの初期化
    pthread_mutex_init(&mutex, NULL);

    // WNUM個のwriterを生成
    for (i = 0; i < WNUM; i++) {
        pthread_create(&wth[i], NULL, writer, (void *) &ids[i]);
    }
    // RNUM個のreaderを生成
    for (i = 0; i < RNUM; i++) {
        pthread_create(&rth[i], NULL, reader, (void *) &ids[i]);
    }

    // スレッドの終了を待つ
    for (i = 0; i < WNUM; i++) {
        pthread_join(wth[i], NULL);
    }
    for (i = 0; i < RNUM; i++) {
        pthread_join(rth[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}

//3秒毎にデータを書き換える
void *writer(void *x) {
    int v;
    int id = *((int *) x);
    sleep(id); //時間差をつけて開始
    printf("Writer %d start\n", id);
    for (v = 0; v < 10; v++) {
        pthread_mutex_lock(&mutex);
        buf = 10 * v + id;
        printf(" writer(%d) wrote %d.\n", id, buf);
        pthread_mutex_unlock(&mutex);
        sleep(3);
    }
    printf("Writer(%d) exit.\n", id);
    pthread_exit(NULL);
}

//1秒かけてデータを読み出し、1秒休む
void *reader(void *x) {
    int id = *(int *) x;
    int i, v;
    printf("Reader %d start\n", id);
    for (i = 0; i < 50; i++) {
        pthread_mutex_lock(&mutex);
        v = buf;
        printf("   reader(%d) read %d.\n", id, v);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("Reader %d exit.\n", id);
    pthread_exit(NULL);
}

