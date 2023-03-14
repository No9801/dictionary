dictionary.exe: dictionary.o dictionaryFunction.o word.o
	g++ dictionary.o dictionaryFunction.o word.o -o dictionary

dictionary-debug.exe: dictionary-debug.o dictionaryFunction.o word.o
	g++ dictionary-debug.o dictionaryFunction.o word.o -o dictionary-debug

dictionary.o: dictionary.cpp Makefile
	g++ -c dictionary.cpp -O2

dictionary-debug.o: dictionary.cpp Makefile
	g++ -c dictionary.cpp -DDEBUG -O2 -o dictionary-debug.o

dictionaryFunction.o: dictionaryFunction.cpp Makefile
	g++ -c dictionaryFunction.cpp -O2

word.o: word.cpp Makefile
	g++ -c word.cpp -O2
	
clean:
	rm *.o
	
clean-all: clean
	rm *.exe