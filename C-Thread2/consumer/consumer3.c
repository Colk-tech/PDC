/*
 * consumer.c -- 生産者消費者問題
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *producer(void *), *consumer(void *);

#define BUFFER_SIZE     4               /* バッファの大きさ */
struct buffer {
    int rp;                        /* 読み出す位置 */
    int wp;                        /* 書き込む位置 */
    int itemnum;                      /* バッファ内の要素数 */
    int data[BUFFER_SIZE];          /* データを保存する場所 */
    pthread_mutex_t mutex;         /* この構造体の相互排除のための mutex */
    pthread_cond_t not_full;      /* バッファに空きがあるという条件 */
    pthread_cond_t not_empty;     /* バッファにデータがあるという条件 */
};

void put(struct buffer *b, int v) /* バッファに値を書き込む操作 */
{
    pthread_mutex_lock(&b->mutex);
    while (b->itemnum == BUFFER_SIZE) {
        //    printf("put() : buffer is full : wait\n" );fflush(stdout);
        /* バッファに空きがあるという条件が満たされるのを待つ */
        pthread_cond_wait(&b->not_full, &b->mutex);
    }
    b->data[b->wp] = v; /* 位置wpの配列dataの値をv とする。*/
//  printf("put() into data[%d]\n", b->wp );fflush(stdout);
    b->wp = (b->wp + 1) % BUFFER_SIZE;
    (b->itemnum)++;
    //sleep(1);
    /* バッファにデータがある という条件が満たされたことを通知 */
    pthread_cond_signal(&b->not_empty);
    pthread_mutex_unlock(&b->mutex);
}

int get(struct buffer *b) /* バッファから値を読み出す操作 */
{
    int v;
    pthread_mutex_lock(&b->mutex);
    while (b->itemnum == 0) {
//     printf("get () : itemnum is 0 : wait\n" );fflush(stdout);
        /* バッファにデータがある という条件が満たされるのを待つ */
        pthread_cond_wait(&b->not_empty, &b->mutex);
    }
    v = b->data[b->rp];
//  printf("get from data[%d]\n", b->rp );fflush(stdout);
    b->rp = (b->rp + 1) % BUFFER_SIZE;
    b->itemnum--;
    //sleep(1);
    /* バッファに空きがあるという条件が満たされたことを通知 */
    pthread_cond_signal(&b->not_full);
    pthread_mutex_unlock(&b->mutex);
    return (v);
}

int main(void) {
    pthread_t t1;
    pthread_t t2;
    struct buffer *b;

    b = (struct buffer *) malloc(sizeof(struct buffer));
    if (b == NULL) {
        perror("no memory for struct buffer\n");
        exit(EXIT_FAILURE);
    }

    b->rp = 0;
    b->wp = 0;
    b->itemnum = 0;
    pthread_mutex_init(&b->mutex, NULL); /* 変数mutexの初期化 */
    pthread_cond_init(&b->not_full, NULL); /* 条件変数not_fullの初期化 */
    pthread_cond_init(&b->not_empty, NULL); /* 条件変数not_emptyの初期化 */

    pthread_create(&t1, NULL, producer, (void *) b);
    pthread_create(&t2, NULL, consumer, (void *) b);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&b->mutex);
    free(b);

    return EXIT_SUCCESS;
}

void *producer(void *x)  /* 生産者 */
{
    struct buffer *b;
    b = (struct buffer *) x;
    int i, v;
    for (i = 0; i < 10; i++) {
        v = i;
        printf("producer(): going to put( %d )\n", v);
        fflush(stdout);
        put(b, v);
//    printf("   put( %d ) done.\n", v );fflush(stdout);
    }
    pthread_exit(NULL);
}

void *consumer(void *x) /* 消費者 */
{
    struct buffer *b;
    b = (struct buffer *) x;
    int i, v;
    for (i = 0; i < 10; i++) {
//      printf("consumer(): going to get().\n");fflush( stdout);
        v = get(b);
        printf("consumer(): get() : got %d.\n", v);
        fflush(stdout);
    }
    pthread_exit(NULL);
}

