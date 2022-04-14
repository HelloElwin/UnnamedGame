FLAGS = -pedantic-errors -std=c++11

bin/utils.o: src/utils.cpp src/utils.h
	g++ $(FLAGS) -c $< -o $@

bin/player.o: src/player.cpp src/player.h src/map.h src/utils.h
	g++ $(FLAGS) -c $< -o $@

bin/map.o: src/map.cpp src/player.h src/map.h src/utils.h
	g++ $(FLAGS) -c $< -o $@

bin/main.o: src/main.cpp src/map.h src/utils.h 
	g++ $(FLAGS) -c $< -o $@

bin/block_fill.o: src/block_fill.cpp src/block_fill.h
	g++ $(FLAGS) -c $< -o $@

bin/windowsize.o: src/windowsize.cpp src/windowsize.h
	g++ $(FLAGS) -c $< -o $@

bin/bar.o: src/bar.cpp src/bar.h
	g++ $(FLAGS) -c $< -o $@

main: bin/main.o bin/map.o bin/utils.o bin/player.o bin/block_fill.o bin/windowsize.o bin/bar.o
	g++ $(FLAGS) $^ -o main


clean:
	rm -f bin/*

.PHONY: clean
