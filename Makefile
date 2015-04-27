Zombie_Game: Zmain.o Zombies.o
	g++ -std=c++11 Zmain.o Zombies.o -o Zombie_Game

Zmain.o: Zmain.cpp Zombies.h
	g++ -c -std=c++11 Zmain.cpp

Zombies.o: Zombies.cpp Zombies.h
	g++ -c -std=c++11 Zombies.cpp

clean:
	rm *.o Zombie_Game
