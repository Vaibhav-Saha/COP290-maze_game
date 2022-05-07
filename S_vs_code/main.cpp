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

    
    bool playing_as_officer = false;
    
    //int cnt =0;
	game = new Game();
	game->init("GameWindow", 1000, 800, false);
    
    //game->lost();
    
    
	
	P1 = new Police( game->return_ren_chan() , "up.bmp",285 , 200);
    
    string from_server;
    string from_client;
    string other_player_location ;
    string person = "empty";
    string screen = "player_imgs/job_choice.png";
    int time = 1;
    if ( !playing_as_officer){
        Server lmao;
        int pick = 0;
        game->show( "entered/start/start.png" );

        SDL_Delay(4000);
        while(person[0] == 'e'){
            SDL_Event event;
            SDL_PollEvent(&event);
            game->show( screen.c_str() );

            from_client = lmao.message("not_ready");
            if(from_client[0] == 'q'){
                game->isRunning = false;
                break;
            }
            if( event.type == SDL_QUIT )
            {
                game->isRunning = false;
                from_client = lmao.message("quit");

            }else{
                if( event.type == SDL_KEYDOWN )
                {
                    switch( event.key.keysym.sym )
                    {

                        case SDLK_1:
                        if(pick == 0){
                            pick = 1;
                            screen= "player_imgs/student_choice.png";
                        }else if (pick == 1){
                            person = "player_imgs/student_boy.png";
                        
                        }else if (pick == 2){
                            person = "player_imgs/dayscholar_boy.png";
                        
                        }else if (pick == 3){
                            person = "player_imgs/wanderer_boy.png";
                        
                        }
                        
                        
                        break;
                        case SDLK_2:
                        if(pick == 0){
                            pick = 2;
                            screen= "player_imgs/dayscholar_choice.png";
                        }else if (pick == 1){
                            person = "player_imgs/student_girl.png";
                        
                        }else if (pick == 2){
                            person = "player_imgs/dayscholar_girl.png";
                        
                        }else if (pick == 3){
                            person = "player_imgs/wanderer_girl.png";
                        
                        }
                        
                        break;
                        case SDLK_3:
                        if(pick == 0){
                            pick = 3;
                            screen= "player_imgs/wanderer_choice.png";
                        }

                        break;

                        
                    }
                }
            }
        }
        
        player = new GameObject( game->return_ren_chan() , person.c_str() , 414 , 72 );
        from_client = lmao.message("ready");
        screen= "entered/wait.png"; 
        while( from_client[0] != 'r'){
            if(from_client[0] == 'q'){
                game->isRunning = false;
                break;
            }
            from_client = lmao.message("ready");
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
            //game->temp_clear();
            //game->check_exit();
            
            game->handleEvents( player );
            //game2->handleEvents( P1, player );
            game->update( player );
            if( std::chrono::duration_cast<std::chrono::seconds>(end - start).count() == time){
                if(player->yulu_counter >0){    
                    player->yulu_counter--;
                }
                player->health = player->health - 1;
                time++;
            }
            //cout<< player->health << endl;
            if( (game->collision) || (player->health <= 0) ){
                
                from_client = lmao.message( "goti_"+to_string( abs(player->destR_map.x) + player->x_cord )+"_"+ to_string( (abs(player->destR_map.y) + player->y_cord) )+"_"+ player->player_img );
                game->lost();

                SDL_Delay(4000);
                cout<<"ho gai coll";
                
                break;
            }else{
                from_client = lmao.message( "ffff_"+to_string( abs(player->destR_map.x) + player->x_cord )+"_"+ to_string( (abs(player->destR_map.y) + player->y_cord) )+"_"+ player->player_img );
            }
            if( from_client[0] == 'T'){
                cout<< from_client <<endl ;
                game->collision = true;
            }
            if(from_client[0] == 'q'){
                game->isRunning = false;
                break;
            }
            other_player_location = from_client.substr(5, from_client.length()-5);
           // cout<< other_player_location <<endl ;


            game->render( player , other_player_location);            
            SDL_Delay(10);  
            if(!game->isRunning){
                from_client = lmao.message("quit");
            }
            if((std::chrono::duration_cast<std::chrono::seconds>(end - start).count() >= 3*60) || (player->won == 1) ){
                from_client = lmao.message( "lost_");
                game->won();
                SDL_Delay(4000);
                cout<<"geet gya";
                
                break;
            }
            end = std::chrono::system_clock::now();
        }

    }else{
        //Client lmao;
        while (game->running())
        {
            //game->check_exit();

            game->handleEvents2( P1 );
            //game2->handleEvents( P1, player );

            game->update2( P1 );
/*
            if(game->collision){
                string other_player_location = lmao.message( "TRUE_"+to_string( abs(P1->destR_map.x) + P1->x_cord )+"_"+ to_string( (abs(P1->destR_map.y) + P1->y_cord) )+"_"+ P1->Police_img );
            
            }else {
                string other_player_location = lmao.message( "FALS_"+to_string( abs(P1->destR_map.x) + P1->x_cord )+"_"+ to_string( (abs(P1->destR_map.y) + P1->y_cord) )+"_"+ P1->Police_img );
            
            }
            //string other_player_location = lmao.message("client to server");
            cout<< other_player_location <<endl;
            //game2->update( P1, player );
*/
            game->render2( P1 , other_player_location );
            //game2->render2( P1, player );
            SDL_Delay(10);

            //if(game->collision){
            //   break;
            //}

        }

    }
    Mix_FreeMusic( gMusic );
    Mix_Quit();
	game->clean();
	return 0;
}








