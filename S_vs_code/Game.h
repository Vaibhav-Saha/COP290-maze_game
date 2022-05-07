#pragma once
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>


//#include "objects.h"
using namespace std;
class Police {

public :
    Police(SDL_Renderer* ren_chan , const char* name , int x , int y);
    ~Police();

    void Handle_events( SDL_Event event );
    //void Handle_events2( SDL_Event event );
    void Update();


    void ShowMap(SDL_Renderer* ren_chan );
    void Render( SDL_Texture* player_2 , int position_1 , int position_2);

    int x_cord;
    int y_cord;
    int steps_per_event;
    bool is_on_road;
    bool pop_on_screen;
    string names[5];
    SDL_Texture* entered[5];
    int entered_index;


    SDL_Texture* player_texture;
    SDL_Texture* blend;
    SDL_Rect srcR_map , destR_map;
    string Police_img;

    int x_s;
    int x_n;
    int x_b;
    int y_n;
    int y_s;
    int y_b;
    

private:


    SDL_Rect srcR_screen , destR_screen;
    SDL_Rect srcR , destR;
    SDL_Renderer* renderer;
    SDL_Texture* whole_map;
};


class GameObject {

public :
    GameObject(SDL_Renderer* ren_chan , const char* name , int x , int y);
    ~GameObject();

    void Handle_events( SDL_Event event );
    //void Handle_events2( SDL_Event event );

    void Update();


    void ShowMap(SDL_Renderer* ren_chan );
    void Render( SDL_Texture* player_2 , int position_1 , int position_2  );
    int dot_x(int x1,int y1,int x2,int y2,int z);
    int dot_y(int x1,int y1,int x2,int y2,int z);


    int x_cord;
    int y_cord;
    int steps_per_event;
    bool is_on_road;
    bool pop_on_screen;
    bool is_on_yulu;
    string names[37];
    SDL_Texture* entered[37];
    int entered_index;
    int health;
    int max_health;

    int my_money;
    int sac_task;
    int lhc_task;
    int hospital_task;
    int won;
    int yulu_counter;
    bool show_task_list;
    bool one_task_compeleted;
    bool show_congrats_pic ;

    //LTexture gTextTexture;
    //TTF_Init() ;
    TTF_Font *gFont = NULL;
    SDL_Texture* mTexture;
    SDL_Surface* textSurface;
    string textureText;

    SDL_Texture* money_bar;
    SDL_Texture* health_bar;
    SDL_Texture* health_level;
    
    SDL_Texture* hospital_task_done;
    SDL_Texture* sac_task_done;
    SDL_Texture* lhc_task_done;
    SDL_Texture* task_list;
    SDL_Texture* player_texture;
    SDL_Texture* player_texture_with_yulu;
    SDL_Texture* player_texture_without_yulu;
    SDL_Rect srcR_map , destR_map;
    string player_img;
    string player_img_with_yulu;
    string player_img_without_yulu;

    int x_s;
    int x_n;
    int x_b;
    int y_n;
    int y_s;
    int y_b;
private:

    SDL_Rect Temp_destR ;
    SDL_Rect srcR_money , destR_money;
    SDL_Rect srcR_health , destR_health;
    SDL_Rect srcR_health_level , destR_health_level;
    SDL_Rect srcR_screen , destR_screen;
    SDL_Rect srcR , destR;
    SDL_Renderer* renderer;
    SDL_Texture* whole_map;
    SDL_Texture* low_health;
    SDL_Texture* warning;

    Mix_Chunk *m_transaction;
    Mix_Chunk *m_eating;
    Mix_Chunk *m_drinking;
};



class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
    //void check_exit();

	void handleEvents( GameObject* player );
	void handleEvents2( Police* P1 );

	void render( GameObject* player , string other_player_location );
	void render2( Police* P1 , string other_player_location );

	void update( GameObject* player );
	void update2( Police* P1 );

	bool running() { return isRunning; }
	SDL_Renderer* return_ren_chan();
	void clean();

    void show( const char* name );
    void won();
    void lost();

    string version;
	SDL_Renderer *renderer;
    void temp_clear();
    bool isRunning = false;
    bool collision;

    SDL_Texture* won_;
    SDL_Texture* lost_;
    
private:
	
    SDL_Rect srcR_screen , destR_screen;
	//int cnt = 0;
	SDL_Window *window;
    int position_x_p = 100;
    int position_x_n = 100;
    int position_y_p = 100;
    int position_y_n = 100;
    
};

