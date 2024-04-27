/*
 * consumer2.c -- 生産者消費者問題
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
 
void *producer(void *), *consumer(void *);
 
#define BUFFER_SIZE     4               /* バッファの大きさ */
struct buffer
{
  int rp ;                        /* 読み出す位置 */
  int wp ;                        /* 書き込む位置 */
  int itemnum ;                      /* バッファ内の要素数 */
  int data[BUFFER_SIZE];          /* データを保存する場所 */
  pthread_mutex_t mutex ;         /* このバッファの排他制のためのロック */
};
 
//バッファに対する操作
void put( struct buffer *b,int v ) /* バッファに値を書き込む操作 */
{
  pthread_mutex_lock( &b->mutex );
  while( b->itemnum == BUFFER_SIZE )
	; /* バッファに空きができるのを待つ */
  b->data[ b->wp ] = v ;
  printf("put() into data[%d]\n", b->wp );fflush(stdout);
  b->wp = (b->wp +1) % BUFFER_SIZE;
  (b->itemnum) ++ ;
  pthread_mutex_unlock( &b->mutex );
}
 
//バッファに対する操作
int get( struct buffer *b ) /* バッファから値を読み出す操作 */
{
  int v ;
  pthread_mutex_lock( &b->mutex );
  while( b->itemnum == 0 )
	; /* バッファにデータが入るのを待つ */
  v = b->data[ b->rp ] ;
  printf("get() from data[%d]\n", b->rp );fflush(stdout);
  b->rp = (b->rp +1) % BUFFER_SIZE;
  b->itemnum -- ; 
  pthread_mutex_unlock( &b->mutex );
  return( v );
}
 
int main(void)
{
  pthread_t t1 ;
  pthread_t t2 ;
  struct buffer *b  ;

  b = (struct buffer *)malloc(sizeof(struct buffer));
  if( b == NULL )
    {
      perror("no memory for struct buffer\n");
      exit( EXIT_FAILURE );
    }

  b->rp = 0 ;
  b->wp = 0 ;
  b->itemnum = 0 ;
  pthread_mutex_init( &b->mutex, NULL ); /* 変数mutexの初期化 */

  pthread_create( &t1, NULL, producer, (void *)b );
  pthread_create( &t2, NULL, consumer, (void *)b );
  pthread_join( t1, NULL );
  pthread_join( t2, NULL );

  pthread_mutex_destroy( &b->mutex );
  free(b);

  return EXIT_SUCCESS;
}
 
void *producer( void *x )  /* 生産者 */ 
{
  struct buffer *b;
  b=(struct buffer *)x;
  int i,v ;
  for( i = 0 ; i<10 ; i++ )
    {
      v = i ;
      printf("producer(): going to put( %d )\n",v );fflush(stdout);
      put( b,v );
      printf("   put( %d ) done.\n", v );fflush(stdout);
    }
  pthread_exit(NULL);
}
 
void *consumer( void *x) /* 消費者 */ 
{
  struct buffer *b;
  b=(struct buffer *)x;
  int i, v ;
  for( i = 0 ; i<10 ; i++ )
    {
      printf("consumer(): going to get().\n");fflush( stdout);
      v = get( b );
      printf("   got %d.\n", v );fflush( stdout);
    }
  pthread_exit(NULL);
}

