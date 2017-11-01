all: exe

exe: main.o FileReading.o Grid.o HelpClasses.h Hashing.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h Dtw.cpp Dtw.h
	g++ -std=c++11 -o exe main.o FileReading.o Grid.o HelpClasses.h Hashing.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h Dtw.cpp Dtw.h

main.o: main.cpp FileReading.cpp FileReading.h Grid.h Grid.cpp Hashing.h HelpClasses.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h
	g++ -std=c++11 -c main.cpp FileReading.cpp FileReading.h Grid.h Grid.cpp Hashing.h HelpClasses.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h

FileReading.o: FileReading.cpp FileReading.h Hashing.h HelpClasses.h Grid.cpp Grid.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h
	g++ -std=c++11 -c FileReading.cpp FileReading.h Hashing.h HelpClasses.h Grid.cpp Grid.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h

Grid.o: Grid.cpp Grid.h HelpClasses.h Hashing.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h Dtw.cpp Dtw.h
	g++ -std=c++11 -c Grid.cpp Grid.h HelpClasses.h Hashing.h frechet.cpp frechet.h outputFunctions.cpp outputFunctions.h Dtw.cpp Dtw.h

clean:
	rm -rf *o *.gch exe
