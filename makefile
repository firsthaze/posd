all: hw7

hw7: mainIterator.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainIterator.o -lgtest
else
	g++ -o hw7 mainIterator.o -lgtest -lpthread
endif

term.o: term.cpp term.h
	g++ -std=gnu++0x -c term.cpp
struct.o: struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp
list.o: list.cpp list.h
	g++ -std=gnu++0x -c list.cpp
mainIterator.o: mainIterator.cpp utIterator.h term.o variable.h struct.o number.h atom.h list.o scanner.h parser.h node.h iterator.h
	g++ -std=gnu++0x -c mainIterator.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o *.gch hw7
endif
stat:
	wc *.h *.cpp
