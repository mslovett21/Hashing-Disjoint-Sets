all: main

main: main.o command_manager.o hashtable.o hashentry.o priorityqueue.o disjointset.o setnode.o
	 g++ -std=c++11 -g main.o command_manager.o hashtable.o hashentry.o priorityqueue.o disjointset.o setnode.o -o main
	
main.o: main.cpp command_manager.h command_manager.cpp
	g++ -std=c++11 -c main.cpp

command_manager.o: command_manager.cpp command_manager.h hashtable.h hashtable.cpp disjointset.cpp disjointset.h
	g++ -std=c++11 -c command_manager.cpp

disjointset.o: disjointset.cpp disjointset.h setnode.h setnode.cpp priorityqueue.cpp priorityqueue.h
	g++ -std=c++11 -c disjointset.cpp

hashtable.o: hashtable.cpp hashtable.h hashentry.h hashentry.cpp
	g++ -std=c++11 -c hashtable.cpp

hashentry.o: hashentry.cpp hashentry.h
	g++ -std=c++11 -c hashentry.cpp

priorityqueue.o: priorityqueue.cpp priorityqueue.h
	g++ -std=c++11 -c priorityqueue.cpp

setnode.o: setnode.cpp setnode.h
	g++ -std=c++11 -c setnode.cpp



 clean:
	rm *.o
	rm main
