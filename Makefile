all: exe

exe: test10.o FileReading.o Grid.o HelpClasses.h Hashing.h
	g++ -std=c++11 -o exe test10.o FileReading.o Grid.o HelpClasses.h Hashing.h

test10.o: test10.cpp FileReading.cpp FileReading.h Grid.h Grid.cpp Hashing.h HelpClasses.h
	g++ -std=c++11 -c test10.cpp FileReading.cpp FileReading.h Grid.h Grid.cpp Hashing.h HelpClasses.h

FileReading.o: FileReading.cpp FileReading.h Hashing.h HelpClasses.h Grid.cpp Grid.h
	g++ -std=c++11 -c FileReading.cpp FileReading.h Hashing.h HelpClasses.h Grid.cpp Grid.h

Grid.o: Grid.cpp Grid.h HelpClasses.h Hashing.h
	g++ -std=c++11 -c Grid.cpp Grid.h HelpClasses.h Hashing.h

clean:
	rm -rfi *o *.gch exe
