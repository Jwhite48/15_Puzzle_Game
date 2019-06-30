output: main.o matrix.o helper.o
	g++ main.o matrix.o helper.o -o output

main.o: main.cpp
	g++ -c main.cpp

matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp

helper.o: helper.cpp helper.h
	g++ -c helper.cpp

clean:
	rm *.o output
