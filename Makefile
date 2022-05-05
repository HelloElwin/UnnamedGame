FLAGS = -pedantic-errors -std=c++11

bin/utils.o: src/utils.cpp src/utils.h
	g++ $(FLAGS) -c $< -o $@

bin/player.o: src/player.cpp src/player.h src/map.h src/utils.h
	g++ $(FLAGS) -c $< -o $@

bin/elfin.o: src/elfin.cpp src/elfin.h src/map.h src/player.h
	g++ $(FLAGS) -c $< -o $@

bin/map.o: src/map.cpp src/player.h src/map.h src/utils.h src/elfin.h
	g++ $(FLAGS) -c $< -o $@

bin/main.o: src/main.cpp src/map.h src/utils.h src/interface.h src/elfin.h src/player.h src/block_fill.h
	g++ $(FLAGS) -c $< -o $@

bin/block_fill.o: src/block_fill.cpp src/block_fill.h
	g++ $(FLAGS) -c $< -o $@

bin/interface.o: src/interface.cpp src/interface.h src/utils.h src/map.h
	g++ $(FLAGS) -c $< -o $@

main: bin/main.o bin/map.o bin/utils.o bin/player.o bin/block_fill.o bin/elfin.o bin/interface.o
	g++ $(FLAGS) $^ -o main


clean:
	rm -f bin/*

.PHONY: clean
