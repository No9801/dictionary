dictionary.exe: dictionary.o dictionaryFunction.o word.o
	g++ dictionary.o dictionaryFunction.o word.o -o dictionary

dictionary.o: dictionary.cpp Makefile
	g++ -c dictionary.cpp -O2

dictionaryFunction.o: dictionaryFunction.cpp Makefile
	g++ -c dictionaryFunction.cpp -O2

word.o: word.cpp Makefile
	g++ -c word.cpp -O2
	
clean:
	rm *.o
	
clean-all: clean
	rm *.exe