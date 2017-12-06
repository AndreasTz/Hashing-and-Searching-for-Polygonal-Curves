all: exe

exe: main.o Team.o Initializationpp.o LloydsAssignment.o UpdateFuncts.o VectorUtils.o Reading.o Frechet.o	PreRangeSearch.o RangeSearch.o outputFuncs.o
	g++ main.o Team.o Initializationpp.o LloydsAssignment.o UpdateFuncts.o VectorUtils.o Reading.o Frechet.o	PreRangeSearch.o RangeSearch.o outputFuncs.o -lcppunit -std=c++11 -o exe

main.o: Team.cpp Initializationpp.cpp LloydsAssignment.cpp UpdateFuncts.cpp VectorUtils.cpp Team.h Initializationpp.h LloydsAssignment.h UpdateFuncts.h VectorUtils.h Hashing.h outputFuncs.cpp outputFuncs.h
	g++ -std=c++11 -c Initializationpp.cpp Initializationpp.h LloydsAssignment.cpp LloydsAssignment.h VectorUtils.cpp VectorUtils.h main.cpp Team.h Team.cpp UpdateFuncts.cpp UpdateFuncts.h Hashing.h outputFuncs.cpp outputFuncs.h

Team.o: Team.cpp Team.h
	g++ -std=c++11 -c Team.cpp Team.h

Initializationpp.o: Initializationpp.cpp Initializationpp.h VectorUtils.h VectorUtils.cpp Frechet.cpp Frechet.h
	g++ -std=c++11 -c Initializationpp.cpp Initializationpp.h VectorUtils.h VectorUtils.cpp Frechet.cpp Frechet.h

LloydsAssignment.o: LloydsAssignment.cpp LloydsAssignment.h Team.h Team.cpp
	g++ -std=c++11 -c LloydsAssignment.cpp LloydsAssignment.h Team.h Team.cpp

VectorUtils.o: VectorUtils.cpp VectorUtils.h
	g++ -std=c++11 -c VectorUtils.cpp VectorUtils.h

UpdateFuncts.o: UpdateFuncts.cpp UpdateFuncts.h VectorUtils.cpp VectorUtils.h RangeSearch.cpp RangeSearch.h
 	g++ -std=c++11 -c UpdateFuncts.cpp UpdateFuncts.h VectorUtils.cpp VectorUtils.h RangeSearch.cpp RangeSearch.h

Reading.o: Reading.cpp Reading.h GlobalClasses.h Hashing.h PreRangeSearch.cpp PreRangeSearch.h
	g++ -std=c++11 -c Reading.cpp Reading.h GlobalClasses.h Hashing.h PreRangeSearch.cpp PreRangeSearch.h

Frechet.o: Frechet.cpp Frechet.h
	g++ -std=c++11 -c Frechet.cpp Frechet.h

PreRangeSearch.o: PreRangeSearch.cpp PreRangeSearch.h
	g++ -std=c++11 -c PreRangeSearch.cpp PreRangeSearch.h

RangeSearch.o: RangeSearch.cpp RangeSearch.h
	g++ -std=c++11 -c RangeSearch.cpp RangeSearch.h

outputFuncs.o: outputFuncs.cpp outputFuncs.h
	g++ -std=c++11 -c outputFuncs.cpp outputFuncs.h

clean:
	rm -rf *.o *.gch exe
