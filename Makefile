FLAGS = -pedantic-errors -std=c++11

utils.o: utils.cpp utils.h
	g++ $(FLAGS) -c $<

player.o: player.cpp player.h map.h utils.h
	g++ $(FLAGS) -c $<

map.o: map.cpp player.h map.h utils.h
	g++ $(FLAGS) -c $<

main.o: main.cpp map.h utils.h 
	g++ $(FLAGS) -c $<

block_fill.o: block_fill.cpp block_fill.h
	g++ $(FLAGS) -c $<

main: main.o map.o utils.o player.o block_fill.o
	g++ $(FLAGS) $^ -o main


clean:
	rm -f main main.o map.o player.o utils.o

.PHONY: clean
