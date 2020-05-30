all: build run clean
build: main.c List.c project.c Resource.c Task.c
	gcc -Wall -O0 -g3 -DDEBUG main.c List.c project.c Resource.c Task.c -o task.exe
	
run: task.exe
	./task.exe
	
clean: 
	rm -rf *.o task.exe