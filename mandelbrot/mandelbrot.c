/*
 * mandelbrot.c
 * For Parallel and Distributed Programming
 * Based on Mandelbortset.c by Shibin K.Reeny.
 *
 * Copyright Yasuhiro Ohtaki
 * This program is free software; you can redistribute
 * it and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

/* Mandelbrotset.c
 * Copyright Shibin K.Reeny
 * This program is free software; you can redistribute
 * it and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

// Apple 系のシステムの場合は以下をインクルード
#if defined(__APPLE__)

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

// それ以外のシステムの場合は以下をインクルード
#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

// 共通のインクルード
#include <pthread.h>

#include <stdlib.h> // EXIT_SUCCESS のためにインクルード
#include <stdio.h>

// 自分のPCの画面サイズに合わせて調整して良い
#define IMAGE_X 1024
#define IMAGE_Y 768

// 計算負荷パラメータ
#define MAX_ITERATION 10000

// スレッド数
#define MAX_THREADS IMAGE_Y

/*
 *defining a RGB struct to color the pixel
 */
struct Type_rgb {
    float r;
    float g;
    float b;
};

/*
 * 画像中の各ピクセルの色を保持する配列
 */
struct Type_rgb pixels[IMAGE_Y * IMAGE_X];

/*
 * スレッドごとに分割処理を行うための構造体
 */
struct thread_data {
    int start_y;
    int end_y;
};

// その他 グローバル変数
pthread_t mandelthreads[MAX_THREADS];

struct timespec start, end;
int is_first = 1;

/*
 * 収束にかかった回数に応じて、ピクセルの色を決める関数
 */
struct Type_rgb setMyColor(int iteration) {
    struct Type_rgb col;
    if (iteration >= MAX_ITERATION) {
        /*
         * 収束しなかったら黒
         */
        col.r = col.g = col.b = 0;
    } else {
        /*
 * setting color pixel to the reset of the coordinate by the
 * number of iteration before bailout.
 */
#define PPSTEP 10
        col.b = (iteration % PPSTEP) / (float) PPSTEP;
        col.g = ((iteration / 2) % PPSTEP) / (float) PPSTEP;
        col.r = ((iteration / 4) % PPSTEP) / (float) PPSTEP;
    }
    return col;
}


/*
 * 複素平面上のある一点における収束回数を求める mandelbrotsetの下請け関数。
 * （複素平面上の点(r0,i0)における収束回数）
 * この関数は変更する必要なし。
 */
int mandel_sub(float r0, float i0) {
    /*
     * r0 :- is the real part
     * i0 :- is the imaginary
     * r and i :- is the real and imaginary part of Zn.
     * iteration :- is to keep control variable of the number of iteration
     * MAX_ITERATION :- maximum number of iteration
     *        (which is one of bailout condition)
     */

    float r, i, rtemp;
    int iteration;

    r = 0;
    i = 0;
    iteration = 0;
    /*
     * (r*r) + (i*i) < (2*2) is the 2nd bailout condition
     * i.e. the mandelbrot set is always within a radius of 2.
     */
    while (((r * r) + (i * i) < (2 * 2)) && iteration < MAX_ITERATION) {
        rtemp = (r * r) - (i * i) + r0;
        i = (2 * r * i) + i0;
        r = rtemp;
        iteration++;
    }
    return iteration;
}


/*
 * 複素平面（実部 -2.5 から 1.1, 虚部 -1.0 から 1.1の範囲）における
 * マンデルブロ集合の図全体を計算する関数。
 *
 * この関数を書き換える。あるいは、置き換える関数を作成する。
 */
void *mandelbrotset(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    /*
    * xx, yy はwindow上の座標。
    * r0,i0 はそれを上記の複素平面にマップした座標。
    */
    int xx, yy;
    float r0, i0;
    int iteration;
    long loc;

    if (is_first) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        is_first = 0;
        printf("start_ctime = sec:%ld nsec:%ld\n", start.tv_sec, start.tv_nsec);
    }

    //画面上の座標に対して
    for (yy = my_data->start_y; yy < my_data->end_y; yy++) {
        for (xx = 0; xx < IMAGE_X; xx++) {
            // 複素平面上の座標に変換
            i0 = 2.1f * (float) yy / IMAGE_Y - 1.0;
            r0 = 3.6f * (float) xx / IMAGE_X - 2.5;

            // 収束にかかる回数を計算
            iteration = mandel_sub(r0, i0);

            // 画像を保持する配列に色情報を格納
            loc = yy * IMAGE_X + xx;
            pixels[loc] = setMyColor(iteration);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (double) (end.tv_sec - start.tv_sec);
    elapsed += (double) (end.tv_nsec - start.tv_nsec) * 1e-9;

    printf("elapsed: %lf sec\n", elapsed);

    pthread_exit(NULL);
}

/*
 * ----------------------------------------------------------------------------
 */
void idle(void) {
    glutPostRedisplay();
}


void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(50, timer, 0);
}


void quit() {
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_cancel(mandelthreads[i]);
    }
    exit(0);
}


void PixInit() {
    int i;
    /*
     * Initializing all the pixels to white.
     */
    for (i = 0; i < IMAGE_X * IMAGE_Y; i++) {
        pixels[i].r = 1;
        pixels[i].g = 1;
        pixels[i].b = 1;
    }
}


void onDisplay() {
    /*
     * pixels配列の中身を描画
     */
    glDrawPixels(IMAGE_X, IMAGE_Y, GL_RGB, GL_FLOAT, pixels);
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
        case 'Q':
            quit();
            break;
        default:
            break;
    }
}


void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON :
            quit();
            break;
        default:
            break;
    }
}


void GLInit() {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(IMAGE_X, IMAGE_Y);
    glutCreateWindow("Mandelbrot");

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
}


// メイン関数でスレッドの作成部分を変更
int main(int argc, char *argv[]) {
    struct thread_data thread_data_array[MAX_THREADS];
    const int LINES_PER_THREAD = IMAGE_Y / MAX_THREADS;

    glutInit(&argc, argv);

    GLInit();
    PixInit();

    glutIdleFunc(idle);
    // glutTimerFunc(50, timer, 0);

    for (int t = 0; t < MAX_THREADS; t++) {
        thread_data_array[t].start_y = t * LINES_PER_THREAD;
        thread_data_array[t].end_y = (t + 1) * LINES_PER_THREAD;

        // 最後のスレッドは残り全部を処理
        if (t == MAX_THREADS - 1)
            thread_data_array[t].end_y = IMAGE_Y;

        int rc = pthread_create(&mandelthreads[t], NULL, mandelbrotset, (void *) &thread_data_array[t]);
        // 一応のエラー処理
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    glutMainLoop();

    return EXIT_SUCCESS;
}
