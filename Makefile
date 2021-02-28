main: main.o isa.o
	g++ -o main main.o isa.o
main.o:
	g++ -c main.cpp -o main.o
isa.o:
	g++ -c isa.cpp -o isa.o
clean:
	rm *.o main
