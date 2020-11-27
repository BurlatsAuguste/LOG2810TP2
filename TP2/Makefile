all:tp2

tp2: tp2.o etat.o Machine.o
	g++ -Wall tp2.o etat.o -o tp2

etat.o: etat.cpp etat.hpp
	g++ -Wall -c etat.cpp -o etat.o

Machine.o: Machine.cpp Machine.hpp
	g++ -Wall -c Machine.cpp -o Machine.o

tp2.o: tp2.cpp
	g++ -Wall -c tp2.cpp -o tp2.o

clean:
	rm -f tp2 *.o