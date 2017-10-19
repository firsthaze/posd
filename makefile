all: hw3

hw3: mainVariable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainVariable.o -lgtest
else
	g++ -o hw3 mainVariable.o -lgtest -lpthread
endif

mainVariable.o: mainVariable.cpp utVariable.h term.h variable.h number.h struct.h atom.h
	g++ -std=gnu++0x -c mainVariable.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o *.gch hw3 hw2
endif
stat:
	wc *.h *.cpp
