#include "Game.h"
#include <bits/stdc++.h>
#include "client.hpp"
#include "server.hpp"
#include "Texture_m.h"
#include <chrono>

using namespace std;
//#include "objects.h"

Game *game = nullptr;

GameObject* player;
Police* P1;
//The music that will be played
Mix_Music *gMusic;

int main(int argc, char *argv[])
{

    bool playing_as_officer = true;
    //int cnt =0;
	game = new Game();
	game->init("GameWindow", 1000, 800, false);

	player = new GameObject( game->return_ren_chan() , "up.bmp",280 , 100 );
	string from_server;
    string from_client;
    string other_player_location ;
    string person = "empty";
    string screen = "police_imgs/police_choice.png";
    int time = 1;
    if ( !playing_as_officer){
        //Server lmao;
        while (game->running())
        {
            //game->temp_clear();
            //game->check_exit();
            game->handleEvents( player );
            //game2->handleEvents( P1, player );
            game->update( player );
/*
            if( game->collision ){
                from_client = lmao.message( "goti_"+to_string( abs(player->destR_map.x) + player->x_cord )+"_"+ to_string( (abs(player->destR_map.y) + player->y_cord) )+"_"+ player->player_img );
                SDL_Delay(40);
                cout<<"ho gai coll";
                break;
            }else{
                from_client = lmao.message( "ffff_"+to_string( abs(player->destR_map.x) + player->x_cord )+"_"+ to_string( (abs(player->destR_map.y) + player->y_cord) )+"_"+ player->player_img );
            }
            if( from_client[0] == 'T'){
                cout<< from_client <<endl ;
                game->collision = true;
            }
            */
            other_player_location = from_client.substr(5, from_client.length()-5);
            cout<< other_player_location <<endl ;

            //game2->update( P1, player );
            game->render( player , other_player_location);
            //game2->render2( P1, player );
            SDL_Delay(10);  


        }

    }else{
        Client lmao;
        int pick = 0;
        game->show( "entered/start/start.png" );

        SDL_Delay(4000);
        while(person[0] == 'e'){
            SDL_Event event;
            SDL_PollEvent(&event);
            game->show( screen.c_str() );

            from_server = lmao.message("not_ready");
            if(from_server[0] == 'q'){
                game->isRunning = false;
                break;
            }
            if( event.type == SDL_QUIT )
            {
                game->isRunning = false;
                from_server = lmao.message("quit");
            }else{
                if( event.type == SDL_KEYDOWN )
                {
                    switch( event.key.keysym.sym )
                    {

                        case SDLK_1:
                        person = "police_imgs/police_1.png";
                        screen= "entered/wait.png";                       
                        
                        break;
                        case SDLK_2:
                        person = "police_imgs/police_2.png";
                        screen= "entered/wait.png"; 
                        
                        break;
                        case SDLK_3:
                        person = "police_imgs/police_3.png";
                        screen= "entered/wait.png"; 

                        break;

                        
                    }
                }
            }
        }
        
        P1 = new Police( game->return_ren_chan() , person.c_str() , 500 , 270 );
        P1->destR_map.x = -3046;
        P1->destR_map.y = 0;
        from_server = lmao.message("ready");
        
        while( from_server[0] != 'r'){
            if(from_server[0] == 'q'){
                game->isRunning = false;
                break;
            }
            from_server = lmao.message("ready");
            game->show( screen.c_str() );
        }

        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        gMusic = Mix_LoadMUS( "music/bg.mp3" );
        Mix_VolumeMusic(200);
        Mix_PlayMusic( gMusic, -1 );
        auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        while (game->running())
        {
            //game->check_exit();
            
            game->handleEvents2( P1 );
            //game2->handleEvents( P1, player );
            
            game->update2( P1 );
            //cout<<P1->shift_time_spent<<endl;
            if( std::chrono::duration_cast<std::chrono::seconds>(end - start).count() == time){
                if(P1->yulu_counter >0){
                    P1->yulu_counter--;
                }
                P1->health --;
                time++;
                P1->shift_time_spent ++;
            }
            if( (game->collision) ){
                from_server = lmao.message( "TRUE_"+to_string( abs(P1->destR_map.x) + P1->x_cord )+"_"+ to_string( (abs(P1->destR_map.y) + P1->y_cord) )+"_"+ P1->Police_img );
            
            }else {
                from_server = lmao.message( "FALS_"+to_string( abs(P1->destR_map.x) + P1->x_cord )+"_"+ to_string( (abs(P1->destR_map.y) + P1->y_cord) )+"_"+ P1->Police_img );
            
            }
            if(from_server[0] == 'q'){
                game->isRunning = false;
                break;
            }
            //cout<<P1->health<<endl;
           
            if((from_server[0] == 'l') ){
                game->isRunning = false;
                game->lost();
                cout<<"haar gya";
                SDL_Delay(4000);
                break;
            }
            other_player_location = from_server.substr(5, from_server.length()-5);
           // cout<< other_player_location <<endl;
            //game2->update( P1, player );

            game->render2( P1 , other_player_location );
            //game2->render2( P1, player );
            SDL_Delay(10);
            if(!game->isRunning){
                from_client = lmao.message("quit");
            }
            if( from_server[0] == 'g'){
                game->won();
                SDL_Delay(4000);
                break;
            }
            end = std::chrono::system_clock::now();

        }

    }


	game->clean();
	return 0;
}








