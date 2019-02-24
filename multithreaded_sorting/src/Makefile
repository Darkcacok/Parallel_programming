exe: sort sortmp
	g++ -g main.cpp sort.o sortmp.o -fopenmp -o exe
sort:
	g++ -c -g sort.cpp

sortmp:
	g++ -c -g sortmp.cpp -fopenmp

clean:
	rm *.o exe