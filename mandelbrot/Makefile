.PHONY : clean

mandel : mandelbrot.c
	gcc -Wall -o $@ $^ -framework OpenGL -framework GLUT -lm -pthread -DGL_SILENCE_DEPRECATION

single : single_thread_mandelbrot.c
	gcc -Wall -o $@ $^ -framework OpenGL -framework GLUT -lm -pthread -DGL_SILENCE_DEPRECATION

clean: 
	rm -f mandel
