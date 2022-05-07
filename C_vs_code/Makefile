
all:	
	g++ -Wall  -c Game.cpp -o obj/Release/Game.o
	g++ -Wall  -c main.cpp -o obj/Release/main.o
	g++ -Wall  -c Map.cpp -o obj/Release/Map.o
	g++ -Wall  -c Objects.cpp -o obj/Release/Objects.o
	g++ -Wall  -c Police.cpp -o obj/Release/Police.o
	g++ -Wall  -c Texture_m.cpp -o obj/Release/Texture_m.o
	g++ -o out/begin obj/Release/Game.o obj/Release/main.o obj/Release/Map.o obj/Release/Objects.o obj/Release/Police.o obj/Release/Texture_m.o -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -s
	
	