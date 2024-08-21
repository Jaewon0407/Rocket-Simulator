SRCS = src/main.cpp

make:
	clang++ -std=c++17 $(SRCS) -g -o ./build/rocket -I include -L lib -lglm -lglfw.3.4 -lGLEW.2.2.0 -framework OpenGL
clean:
	rm -f ./rocket