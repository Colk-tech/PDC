#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <sys/time.h> 

int main(void)
{
	int n;
	struct timespec start, end;
	struct timespec start2, end2;
	double elapsed;
	double elapsed2;

	/* 開始時刻の記録 */
	clock_gettime(CLOCK_REALTIME,&start);
	clock_gettime(CLOCK_MONOTONIC,&start2);
	printf("start_time = sec:%ld nsec:%ld\n", start.tv_sec, start.tv_nsec);
	printf("start_time = sec:%ld nsec:%ld\n", start2.tv_sec, start2.tv_nsec);

	/* 計測したい処理 */
	for (n=0; n<10; n++){
		printf("\t%d",n);
		fflush(stdout);
		usleep(100000); /* 10^5 マイクロ秒 = 0.1秒のsleep */
	}
	printf("\n");

	/* 終了時刻の記録 */
	clock_gettime(CLOCK_REALTIME, &end);
	clock_gettime(CLOCK_MONOTONIC, &end2);
	printf("end_time = sec:%ld nsec:%ld\n", end.tv_sec, end.tv_nsec);
	printf("end_time = sec:%ld nsec:%ld\n", end2.tv_sec, end2.tv_nsec);

	/* 経過時間の計算 */
	elapsed  = (double)(end.tv_sec  - start.tv_sec);
	elapsed += (double)(end.tv_nsec - start.tv_nsec) * 1e-9;

	elapsed2  = (double)(end.tv_sec  - start.tv_sec);
	elapsed2 += (double)(end.tv_nsec - start.tv_nsec) * 1e-9;

	printf("total processing time: %lf sec\n", elapsed);
	printf("total processing time: %lf sec\n", elapsed2);
	return EXIT_SUCCESS;
}
