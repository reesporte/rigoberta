default: rigoberta

TextureManager.o: backend/TextureManager.cpp backend/TextureManager.h
	g++ -c backend/TextureManager.cpp -o TextureManager.o

SpriteManager.o: backend/SpriteManager.cpp backend/SpriteManager.h
	g++ -c backend/SpriteManager.cpp -o SpriteManager.o

Character.o: backend/Character.cpp backend/Character.h
	g++ -c backend/Character.cpp -o Character.o

Game.o:	backend/Game.cpp backend/Game.h
	g++ -c backend/Game.cpp -o Game.o

Screen.o: backend/Screen.cpp backend/Screen.h
	g++ -c backend/Screen.cpp -o Screen.o

rigoberta: main.cpp SpriteManager.o TextureManager.o Character.o Game.o Screen.o
	g++ -F /Library/Frameworks -o rigoberta main.cpp SpriteManager.o TextureManager.o Character.o Game.o Screen.o -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-audio -framework freetype -framework FLAC -framework ogg -framework OpenAL -framework vorbis -framework vorbisenc -framework vorbisfile -headerpad_max_install_names -v

run: rigoberta
	./rigoberta

clean:
	rm rigoberta *.o

distro: rigoberta
	./tooling_thing.sh
