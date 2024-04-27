/*
 * mutex.c -- 共有資源をロックしてアクセスするプログラム
 */
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
  
void *thread_A(void *x), *thread_B(void *x);
int     shared_resource ;
pthread_mutex_t mutex0 ;

int main(void) {
  pthread_t t1 ;
  pthread_t t2 ;
  shared_resource = 0 ;

  pthread_mutex_init( &mutex0, NULL );

  pthread_create( &t1, NULL, thread_A, NULL ); /* スレッド1の生成 */
  pthread_create( &t2, NULL, thread_B, NULL ); /* スレッド2の生成 */
  pthread_join( t1, NULL ); /* スレッド1の終了まち */
  pthread_join( t2, NULL ); /* スレッド2の終了まち */

  printf("main(): shared_resource == %d\n", shared_resource );
         /* 共有資源の値を出力 */
  return EXIT_SUCCESS;
}
 
void *thread_A(void *x) { /* スレッド1の処理, 1を100万回加える */
  int i;
  for( i = 0 ; i<1000000 ; i++ )
    {
      pthread_mutex_lock( &mutex0 ); /* 共有資源をロック */
      shared_resource++;
      pthread_mutex_unlock( &mutex0 ); /* 共有資源を開放 */
    }
  pthread_exit(NULL);
}
 
void *thread_B(void *x) { /* スレッド2の処理, 1を100万回加える */
  int i;
  for( i = 0 ; i<1000000 ; i++ ) {
    pthread_mutex_lock( &mutex0 ); /* 共有資源をロック */
    shared_resource++;
    pthread_mutex_unlock( &mutex0 ); /* 共有資源を開放 */
  }
  pthread_exit(NULL);
}
