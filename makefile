all: hw5

hw5: mainParser.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainParser.o -lgtest
else
	g++ -o hw5 mainParser.o -lgtest -lpthread
endif

mainParser.o: mainParser.cpp utParser.h term.h variable.h number.h struct.h atom.h list.h scanner.h parser.h
	g++ -std=gnu++0x -c mainParser.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o *.gch hw5
endif
stat:
	wc *.h *.cpp
