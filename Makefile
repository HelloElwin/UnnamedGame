FLAGS = -pedantic-errors -std=c++11

utils.o: utils.cpp utils.h
	g++ $(FLAGS) -c $<

map.o: map.cpp map.h utils.h
	g++ $(FLAGS) -c $<

main.o: main.cpp map.h utils.h
	g++ $(FLAGS) -c $<

main: main.o map.o utils.o
	g++ $(FLAGS) $^ -o main


clean:
	rm -f main main.o map.o

.PHONY: clean
