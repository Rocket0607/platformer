CC=g++

debug: ./src/main.cpp
	$(CC) -c src/*.cpp -std=c++14 -m64 -g -Wall -I include && g++ *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image && ./bin/debug/main

release: ./src/main.cpp
	$(CC) -c src/*.cpp -std=c++14 -m64 -O3 -Wall -I include && g++ *.o -o bin/release/main -s -lSDL2main -lSDL2 -lSDL2_image && ./bin/release/main

clean:
	rm -r *.o && rm ./bin/debug/main && rm ./bin/release/main
