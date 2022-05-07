#include "Texture_m.h"


SDL_Texture* Texture_m :: Load_Texture( SDL_Texture* pl, SDL_Renderer* ren_chan , const char* name){

    SDL_Surface* temp_surface = IMG_Load(name);
	SDL_Texture*  pl_n = SDL_CreateTextureFromSurface(ren_chan , temp_surface);
	SDL_FreeSurface(temp_surface);

	return pl_n;

}

void Texture_m::tex_clear( SDL_Texture* pl ){
    SDL_DestroyTexture( pl );
}

void Texture_m :: Show( SDL_Renderer* ren_chan , SDL_Texture* texture , SDL_Rect srcR , SDL_Rect destR){
    SDL_RenderClear( ren_chan );
    SDL_RenderCopy(ren_chan , texture , &srcR , &destR);
}

