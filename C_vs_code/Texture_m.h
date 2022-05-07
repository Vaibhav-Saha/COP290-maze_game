#include "Game.h"

class Texture_m {
    public:
        static void tex_clear ( SDL_Texture* pl );
        static SDL_Texture* Load_Texture ( SDL_Texture* pl,  SDL_Renderer* ren_chan , const char* name);
        static void Show(SDL_Renderer* ren_chan ,SDL_Texture* texture , SDL_Rect srcR , SDL_Rect destR);
};

