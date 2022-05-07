#include "Map.h"
#include "maze.h"
#include "Texture_m.h"

int lvl1[200][500] = Matrix__;
Map::Map(SDL_Renderer* ren_chan) {
    road = Texture_m::Load_Texture( road , ren_chan, "bullet.bmp");
    wall = Texture_m::Load_Texture( wall , ren_chan , "wall.bmp");
    whole_map = Texture_m::Load_Texture( whole_map , ren_chan , "maze.bmp");
    //LoadMap(lvl1);

    srcR.x=0;
    srcR.y=0;
    srcR.w=2;
    srcR.h=2;

    destR.w=2;
    destR.h=2;
    destR.y=0;
    destR.x=0;

    srcR_b.x=0;
    srcR_b.y=0;
    srcR_b.w=3000;
    srcR_b.h=1200;

    destR_b.w=3000;
    destR_b.h=1200;
    destR_b.y=0;
    destR_b.x=0;
}
/*
void Map::LoadMap( int arr[200][600]){

    for(int row = 0; row < 200 ; row++){
        for(int col = 0; col < 600 ; col++){

            map[row][col] = arr[row][ col];
        }
    }
}*/

int Map::Attribute(int row , int col){
    return lvl1[row][col];
}


void Map::ShowMap(SDL_Renderer* ren_chan ){
    //int type = 0;
    Texture_m::Show(ren_chan , whole_map , srcR_b , destR_b );
    /*for(int row = 0; row < 200 ; row++){
        for(int col = 0; col < 600 ; col++){

            type = lvl1[row][col];

            destR.x = col*2;
            destR.y = row*2;

            if (type == 0){
                Texture_m::Show(ren_chan , wall , srcR , destR);
            } else {
                Texture_m::Show(ren_chan , road , srcR , destR);
            }
            switch(type){
            case 0:
                Texture_m::Show(ren_chan , road , srcR , destR);
                break;
            case 1:
                Texture_m::Show(ren_chan , wall , srcR , destR);
                break;
            default:
                break;
            }
        }
    }*/
}

