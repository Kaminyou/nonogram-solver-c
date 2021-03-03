main.out:main.c nonogram.o
	gcc -o main.exe main.c nonogram.o
nonogram.o:nonogram.c
	gcc -c nonogram.c

test:
	./run_test.sh
clean:
	rm -f nonogram.o main.exe