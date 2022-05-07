#include "Game.h"

class Map {

public:
    Map(SDL_Renderer* ren_chan);
    ~Map();

    //void LoadMap(int arr[200][600]);
    void ShowMap(SDL_Renderer* ren_chan );

    SDL_Rect srcR , destR;
    SDL_Rect srcR_b , destR_b;
    int Attribute(int row, int col);
    //int map[200][600];

private:
    SDL_Texture* road;
    SDL_Texture* wall;
    SDL_Texture* whole_map;

};

