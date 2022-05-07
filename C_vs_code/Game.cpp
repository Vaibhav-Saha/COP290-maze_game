#include "Game.h"
#include "Texture_m.h"
//#include "objects.h"
#include "Map.h"


//#include "Police.h"


//GameObject* player;
//GameObject* enemy;
//Police* P1;

Map* map_;

Game::Game()
{}

Game::~Game()
{}

string s = "";
SDL_Texture* Other_player ;
SDL_Texture* to_be_shown;
void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		isRunning = true;
	}
	
	collision = false;
	map_ = new Map(renderer);
	won_ = Texture_m :: Load_Texture( won_ , renderer ,  "win/win.png");
	lost_ = Texture_m :: Load_Texture( lost_ , renderer ,  "lose/lose.png");

}

void Game::handleEvents(  GameObject* player )
{

	SDL_Event event;
	SDL_PollEvent(&event);

	if( event.type == SDL_QUIT )
	{
		isRunning = false;
	}else{
		player->Handle_events(event );
	}
}

void Game::handleEvents2( Police* P1 )
{

     SDL_Event event;
	SDL_PollEvent(&event);
	
	if( event.type == SDL_QUIT )
     {
        isRunning = false;
     }else{
		P1->Handle_events(event );
     }

     if ( ((abs(P1->x_cord + abs(P1->destR_map.x) -position_x_n)  +  abs(P1->y_cord + abs(P1->destR_map.y) -position_y_n)) < 100 ) && (event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_c) ){
		collision = true;
	}
	
}
void Game::update( GameObject* player )
{
	//cnt++;
    player->Update();

    //enemy->Update();
    //P1->Update();
	//std::cout << cnt << std::endl;

}

void Game::update2( Police* P1 )
{
	//cnt++;
    //player->Update();
    //enemy->Update();
    P1->Update();
}


    

void Game::render( GameObject* player , string other_player_location )
{
	SDL_RenderClear(renderer);
	//map_->ShowMap(renderer);

	player->ShowMap(renderer);
    //cout<< other_player_location.length()<< endl;
 
     int aa=0,bb=0;
	bool found = false;
	int len = other_player_location.length();

	for(int i=0;i<len;i++){
		if(other_player_location[i]=='_'){
			if(found){
				bb=i;
				break;
			}
			else{
				aa=i;
				found=true;
			}
		}
	}

	position_x_p = stoi( other_player_location.substr(0,aa));
	position_y_p = stoi( other_player_location.substr(aa+1,bb-aa-1));
	version = other_player_location.substr(bb+1,len-bb-1);

	SDL_DestroyTexture(Other_player);
	Other_player  = Texture_m :: Load_Texture( Other_player , renderer , version.c_str() );


    player->Render( Other_player , position_x_p , position_y_p  );
	//enemy->Render();
    //P1->Render();
	SDL_RenderPresent(renderer);


}

void Game::render2( Police* P1 , string other_player_location )
{
	SDL_RenderClear(renderer);
	//map_->ShowMap(renderer);
	P1->ShowMap(renderer);
    //cout<< other_player_location.length()<< endl;

    int aa=0,bb=0;
	bool found = false;
	int len = other_player_location.length();

	for(int i=0;i<len;i++){
		if(other_player_location[i]=='_'){
			if(found){
				bb=i;
				break;
			}
			else{
				aa=i;
				found=true;
			}
		}
	}

	position_x_n = stoi( other_player_location.substr(0,aa));
	position_y_n = stoi( other_player_location.substr(aa+1,bb-aa-1));
	version = other_player_location.substr(bb+1,len-bb-1);

    SDL_DestroyTexture(Other_player);
    Other_player = Texture_m :: Load_Texture( Other_player , renderer ,  version.c_str());
	
    
    P1->Render( Other_player , position_x_n , position_y_n  );
	//enemy->Render();
    //P1->Render();
	SDL_RenderPresent(renderer);
}

SDL_Renderer* Game::return_ren_chan(){
    return renderer;
}

void Game::temp_clear(){
    SDL_RenderClear( renderer );
}

void Game::show( const char* name ){
	SDL_RenderClear(renderer);
	SDL_DestroyTexture(to_be_shown);
    	to_be_shown = Texture_m :: Load_Texture( to_be_shown , renderer ,  name);
	destR_screen.h=800;
	destR_screen.w=1000;
	destR_screen.x= 0 ;
	destR_screen.y= 0 ;
	SDL_RenderCopy(renderer, to_be_shown , NULL , &destR_screen);
	SDL_RenderPresent(renderer);
}
void Game:: won(){
	//SDL_RenderClear(renderer);
	SDL_Rect won_destR ;
        won_destR.h=800;
        won_destR.w=1000;
        won_destR.x= 0 ;
        won_destR.y= 0 ;
	SDL_RenderCopy(renderer, won_ , NULL , &won_destR);
	SDL_RenderPresent(renderer);
}
	
void Game::lost(){
	//SDL_RenderClear(renderer);
	SDL_Rect lost_destR ;
        lost_destR.h=800;
        lost_destR.w=1000;
        lost_destR.x= 0 ;
        lost_destR.y= 0 ;
	SDL_RenderCopy(renderer, lost_ , NULL , &lost_destR );
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


