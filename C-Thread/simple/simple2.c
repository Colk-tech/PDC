/*
 * simple2.c -- スレッドへの引数が複数あるいは ない場合
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *func1( void *x );
void *func2( void *x );

struct foo {
  int x;
  float y;
};

int main(void) {
  pthread_t t1 ;
  pthread_t t2 ;

  struct foo s;
  s.x=3;
  s.y=4.5;

  pthread_create( &t1, NULL, func1, (void *)&s ); /* スレッド1の生成 */
  pthread_create( &t2, NULL, func2, NULL); /* スレッドへの引数なし */

  printf("main()\n");
  pthread_join( t1, NULL ); /* スレッド1の終了 */
  pthread_join( t2, NULL ); /* スレッド2の終了 */
  return EXIT_SUCCESS;
}

void *func1( void *x ) { /* スレッド1の処理 */
  int i;
  struct foo *p;
  p= (struct foo*)x;

  for( i = 0 ; i<3 ; i++ ) {
    printf("func1( %d, %f ): %d \n", p->x, p->y, i );
  }
  pthread_exit(NULL);
}

void *func2( void *x ) { /* スレッド2の処理 */
  int i;
  for( i = 0 ; i<3 ; i++ ) {
    printf("func2( ): %d \n", i );
  }
  pthread_exit(NULL);
}
