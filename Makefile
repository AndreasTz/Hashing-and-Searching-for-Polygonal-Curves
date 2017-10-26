all: exe

exe: main.o FileReading.o Grid.o HelpClasses.h Hashing.h
	g++ -std=c++11 -o exe main.o FileReading.o Grid.o HelpClasses.h Hashing.h

main.o: main.cpp FileReading.cpp FileReading.h Grid.h Grid.cpp Hashing.h HelpClasses.h
	g++ -std=c++11 -c main.cpp FileReading.cpp FileReading.h Grid.h Grid.cpp Hashing.h HelpClasses.h

FileReading.o: FileReading.cpp FileReading.h Hashing.h HelpClasses.h Grid.cpp Grid.h
	g++ -std=c++11 -c FileReading.cpp FileReading.h Hashing.h HelpClasses.h Grid.cpp Grid.h

Grid.o: Grid.cpp Grid.h HelpClasses.h Hashing.h
	g++ -std=c++11 -c Grid.cpp Grid.h HelpClasses.h Hashing.h

clean:
	rm -rfi *o *.gch exe
