global:
	gcc -c global.c
	gcc -o hw1 global.o -lpthread
	./hw1
time:
	gcc -c timefunction.c
	gcc -c time.c
	gcc -o hw2_1 time.o timefunction.o -lpthread
	./hw2_1
time2:
	gcc -c timefunction.c
	gcc -c time2.c
	gcc -o hw2_2 time2.o timefunction.o -lpthread
	./hw2_2



