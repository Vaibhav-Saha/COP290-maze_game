#include <bits/stdc++.h>
#include "Game.h"
#include "Texture_m.h"
#include "maze.h"

int a_2[200][500] = Matrix__;
Police :: Police( SDL_Renderer* ren_chan , const char* name , int x , int y){

    renderer = ren_chan;
    player_texture = Texture_m :: Load_Texture( player_texture , ren_chan , name);
    //player_texture = Texture_m :: Load_Texture(ren_chan , name);
    Police_img = name;
    whole_map = Texture_m::Load_Texture(  whole_map , ren_chan , "map.bmp");
    //whole_map = Texture_m::Load_Texture(ren_chan , "maze.bmp");
    /*
    renderer = ren_chan;
    player_texture = Texture_m :: Load_Texture(ren_chan , name);
    Police_img = name;
    whole_map = Texture_m::Load_Texture(ren_chan , "maze.bmp");*/
    x_cord =x;
    y_cord = y;
    destR_map.x = 0;
    destR_map.y = 0;
    steps_per_event = 5;

}

void Police :: Handle_events( SDL_Event event ){



            if( event.type == SDL_KEYDOWN )
            {
            switch( event.key.keysym.sym )
            {

                case SDLK_f:
                steps_per_event = 10;
                Police_img = "down.bmp";
                player_texture = Texture_m :: Load_Texture( player_texture  , renderer ,  "down.bmp");
                break;

                case SDLK_n:
                steps_per_event =5;
                Police_img = "up.bmp";
                player_texture = Texture_m :: Load_Texture( player_texture  , renderer ,  "up.bmp");
                break;

                case SDLK_UP:

                y_cord = (y_cord -steps_per_event);
                if (destR_map.y == 0){

                    if (y_cord < 0 ){
                        y_cord = 0;
                    }
                    if ( a_2[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1) {
                        y_cord = y_cord+steps_per_event;
                    }
                }else {

                    if ( a_2[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1) {
                        y_cord = y_cord+steps_per_event;
                    }else {
                        if ( y_cord < 150){
                            y_cord = 150;
                            destR_map.y = destR_map.y+steps_per_event;
                        }
                    }
                }
                break;

                case SDLK_DOWN:
                y_cord = (y_cord +steps_per_event);
                if (destR_map.y == -400){
                    if (y_cord >= 800 ){
                        y_cord = 800-steps_per_event;
                    }
                    if ( a_2[(abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                        y_cord = (y_cord -steps_per_event);
                    }
                }else {
                    if ( a_2[(abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                        y_cord = (y_cord -steps_per_event);
                    }else {
                        if ( y_cord > 800-150){
                            y_cord = 800-150;
                            destR_map.y = destR_map.y-steps_per_event;
                        }
                    }

                }
                break;


                case SDLK_LEFT:
                x_cord = (x_cord -steps_per_event);
                if (destR_map.x == 0){
                    if (x_cord < 0 ){
                        x_cord = 0;
                    }
                    if ( a_2[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                        x_cord = (x_cord +steps_per_event);
                    }
                }else{
                    if ( a_2[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                        x_cord = (x_cord +steps_per_event);
                    }else{
                        if ( x_cord < 250){
                            x_cord = 250;
                            destR_map.x = destR_map.x+steps_per_event;
                        }
                    }
                }
                break;


                case SDLK_RIGHT:
                x_cord = (x_cord +steps_per_event);
                if (destR_map.x == -2000){
                    if (x_cord >= 1000 ){
                        x_cord = 1000-steps_per_event;
                    }
                    if ( a_2[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                        x_cord = (x_cord - steps_per_event);
                    }
                }else{
                    if ( a_2[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                        x_cord = (x_cord - steps_per_event);
                    }else{
                        if ( x_cord > 1000 -250){
                            x_cord = 1000 -250;
                            destR_map.x = destR_map.x -steps_per_event;
                        }
                    }
                }
                break;


                default:
                break;
            }
        }
}


void Police :: Update(){
        srcR.h=20;
        srcR.w=20;
        srcR.x=0;
        srcR.y=0;

        destR.h = 30;
        destR.w = 30;
        destR.x = (x_cord -15);
        destR.y = (y_cord -15);

        srcR_map.h=1200;
        srcR_map.w=3000;
        srcR_map.x=0;
        srcR_map.y=0;

        destR_map.h = 1200;
        destR_map.w = 3000;

}


void Police :: Render( SDL_Texture* player_2 , int position_1 , int position_2 ){
    SDL_RenderCopy(renderer , player_texture, NULL , &destR);

    if( (position_1 >= abs(destR_map.x) ) && (position_1 <=  abs(destR_map.x) + 1000) &&  (position_2 >= abs(destR_map.y) ) && (position_2 <= abs(destR_map.y)+800 )){
        SDL_Rect Temp_destR ;
        Temp_destR.h=30;
        Temp_destR.w=30;
        Temp_destR.x= (position_1 - abs(destR_map.x) -15)/1 ;
        Temp_destR.y= (position_2 - abs(destR_map.y) -15)/1 ;
        //SDL_DestroyRenderer(renderer);
        SDL_RenderCopy(renderer, player_2, NULL , &Temp_destR);
    }
}

void Police ::ShowMap(SDL_Renderer* ren_chan ){
    //SDL_RenderCopy(renderer, whole_map , NULL , &destR_);
    Texture_m::Show(ren_chan , whole_map , srcR_map , destR_map );

}

