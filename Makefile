CC = g++
CFLAGS = -Wall -g -O3

main: main.o Gene.o Chromosome.o Population.o
	$(CC) $(CFLAGS) -o main main.o Gene.o Chromosome.o Population.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Gene.o: Gene.cpp
	$(CC) $(CFLAGS) -c Gene.cpp

Chromosome.o: Gene.cpp Chromosome.cpp
	$(CC) $(CFLAGS) -c Gene.cpp Chromosome.cpp

Population.o: Gene.cpp Chromosome.cpp Population.cpp
	$(CC) $(CFLAGS) -c Gene.cpp Chromosome.cpp Population.cpp

clean:
	rm -f core *.o
