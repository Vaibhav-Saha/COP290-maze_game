#include "Game.h"
#include "Texture_m.h"
#include "maze.h"
#include <bits/stdc++.h>





//Rendered texture



using namespace std;
int a[200][500] = Matrix__;
GameObject :: GameObject( SDL_Renderer* ren_chan , const char* name , int x , int y){
    renderer = ren_chan;
    
    player_texture_with_yulu = Texture_m :: Load_Texture( player_texture_with_yulu , ren_chan , "down.bmp" );
    player_texture_without_yulu = Texture_m :: Load_Texture( player_texture_without_yulu , ren_chan , name);
    player_texture =  player_texture_without_yulu;

    player_img = name;
    player_img_without_yulu = name;
    player_img_with_yulu = "down.bmp" ;
    money_bar = Texture_m::Load_Texture(  money_bar , ren_chan , "bars/money_bar.png");
    health_bar = Texture_m::Load_Texture(  health_bar, ren_chan , "bars/health_bar.png");
    health_level = Texture_m::Load_Texture(  health_level, ren_chan , "bars/health.png");

    whole_map = Texture_m::Load_Texture(  whole_map , ren_chan , "map.bmp");
    warning = Texture_m::Load_Texture(  warning , ren_chan , "dot.bmp");
    
    x_cord =x;
    y_cord = y;
    destR_map.x = 0;
    destR_map.y = 0;
    steps_per_event = 5;

    is_on_road = true;
    is_on_yulu = false;
    pop_on_screen = false;

    entered_index = 0;
    names[0] = "maze.bmp";
    entered[0] = Texture_m :: Load_Texture( entered[0] , renderer ,  names[0].c_str());
    
    names[0] = "entered/side_space/side_space.png";
    names[1] = "entered/road/road.png";
    names[2] = "entered/biotech_lawn/biotech_lawn.png";
    names[3] = "entered/gate/gate.png";
    names[4] = "entered/mech_d/mech_d.png";
    names[5] = "entered/hostel_girls/hostel_girls.png";
    names[6] = "entered/hostel_boys/hostel_boys.png";
    names[7] = "entered/entry/entry.png";
    names[8] = "entered/night_mess/night_mess.png";
    names[9] = "entered/yulu/yulu.png";
    names[10] = "entered/residential_area/residential_area.png";
    names[11] = "entered/ccd/ccd.png";
    names[12] = "entered/ground/ground.png";
    names[13] = "entered/volley_court/volley_court.png";
    names[14] = "entered/main_building/main_building.png";
    names[15] = "entered/lhc/lhc.png";
    names[16] = "entered/pentonic/pentonic.png";
    names[17] = "entered/delhi16/delhi16.png";
    names[18] = "entered/rajdhani/rajdhani.png";
    names[19] = "entered/scoop/scoop.png";
    names[20] = "entered/dod/dod.png";
    names[21] = "entered/tennis_court/tennis_court.png";
    names[22] = "entered/amul/amul.png";
    names[23] = "entered/library/library.png";
    names[24] = "entered/staff_canteen/staff_canteen.png";
    names[25] = "entered/masala_mix/masala_mix.png";
    names[26] = "entered/apollo/apollo.png";
    names[27] = "entered/hospital/hospital.png";
    names[28] = "entered/shiru/shiru.png";
    names[29] = "entered/ich/ich.png";
    names[30] = "entered/park/park.png";
    names[31] = "entered/parking_area/parking_area.png";
    names[32] = "entered/bsa_ground/bsa_ground.png";
    names[33] = "entered/athletic_ground/athletic_ground.png";
    names[34] = "entered/sac/sac.png";
    names[35] = "entered/mother_dairy/mother_dairy.png";
    names[36] = "entered/grocery/grocery.png";

    
    for (int i=0 ; i<37;i++){
        entered[i] = Texture_m :: Load_Texture( entered[i] , renderer ,  names[i].c_str());
    }
     
    my_money = 100;
    health = 100;
    max_health = 100;
    food_task = 0;
    lhc_task = 0;
    hospital_task = 0;
    

    //Open the font
    TTF_Init();
    gFont = TTF_OpenFont( "Helvetica-BoldOblique.ttf", 28 );

    //Render text
    textureText = to_string(health);
    

}

int GameObject :: dot_y(int x1,int y1,int x2,int y2,int z){
    int ans;
    
    ans = y2-((y2-y1)*(x2-z)/(x2-x1));

    return ans;
}

int GameObject :: dot_x(int x1,int y1,int x2,int y2,int z){
    int ans=x2-((y2-z)*(x2-x1)/(y2-y1));
    return ans;
}

void GameObject :: Handle_events( SDL_Event event ){



            if( event.type == SDL_KEYDOWN )
            {
            switch( event.key.keysym.sym )
            {

                case SDLK_f:
                steps_per_event = 10;
                player_img = "down.bmp";
                player_texture  = Texture_m :: Load_Texture( player_texture  , renderer , "down.bmp");
                break;

                case SDLK_n:
                steps_per_event = 5;
                player_img = "up.bmp";
                player_texture  = Texture_m :: Load_Texture( player_texture , renderer , "up.bmp");
                break;

                case SDLK_UP:
                if(is_on_road){
                    y_cord = (y_cord -steps_per_event);
                    if (destR_map.y == 0){

                        if (y_cord < 0 ){
                            y_cord = 0;
                        }
                        if ( a[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1) {
                            y_cord = y_cord+steps_per_event;
                        }
                    }else {

                        if ( a[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1) {
                            y_cord = y_cord+steps_per_event;
                        }else {
                            if ( y_cord < 150){
                                y_cord = 150;
                                destR_map.y = destR_map.y+steps_per_event;
                            }
                        }
                    }
                }else{

                }
                break;

                case SDLK_DOWN:
                if(is_on_road){
                    y_cord = (y_cord +steps_per_event);
                    if (destR_map.y == -400){
                        if (y_cord >= 800 ){
                            y_cord = 800-steps_per_event;
                        }
                        if ( a[(abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                            y_cord = (y_cord -steps_per_event);
                        }
                    }else {
                        if ( a[(abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                            y_cord = (y_cord -steps_per_event);
                        }else {
                            if ( y_cord > 800-150){
                                y_cord = 800-150;
                                destR_map.y = destR_map.y-steps_per_event;
                            }
                        }

                    }
                }else{

                }
                break;


                case SDLK_LEFT:
                if(is_on_road){
                    x_cord = (x_cord -steps_per_event);
                    if (destR_map.x == 0){
                        if (x_cord < 0 ){
                            x_cord = 0;
                        }
                        if ( a[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                            x_cord = (x_cord +steps_per_event);
                        }
                    }else{
                        if ( a[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                            x_cord = (x_cord +steps_per_event);
                        }else{
                            if ( x_cord < 250){
                                x_cord = 250;
                                destR_map.x = destR_map.x+steps_per_event;
                            }
                        }
                    }
                }else{

                }
                break;


                case SDLK_RIGHT:
                if(is_on_road){
                x_cord = (x_cord +steps_per_event);
                    if (destR_map.x == -2000){
                        if (x_cord >= 1000 ){
                            x_cord = 1000-steps_per_event;
                        }
                        if ( a[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                            x_cord = (x_cord - steps_per_event);
                        }
                    }else{
                        if ( a[ (abs(destR_map.y)  + y_cord)/6 ][ (abs(destR_map.x)+ x_cord)/6 ] != 1){
                            x_cord = (x_cord - steps_per_event);
                        }else{
                            if ( x_cord > 1000 -250){
                                x_cord = 1000 -250;
                                destR_map.x = destR_map.x -steps_per_event;
                            }
                        }
                    }
                }else{

                }
                break;

                
                //  (entered_index == 22) /*amul*/
                //  (entered_index == 26) /*apollo*/
                //  (entered_index == 10) /*ccd*/
                //  (entered_index == 17) /*delhi16*/
                //  (entered_index == 36) /*grocery*/
                //  (entered_index == 27) /*hospital*/
                //  (entered_index == 29) /*ich*/
                //  (entered_index == 25) /*masala_mix*/
                //  (entered_index == 35) /*mother_dairy*/
                //  (entered_index == 19) /*scoop*/    
                //  (entered_index == 16) /*pentonic*/
                //  (entered_index == 18) /*rajdhani*/
                //  (entered_index == 8) /*night_mess*/
                //  (entered_index == 28) /*shiru*/
                //  (entered_index == 24) /*staff_canteen*/
                //  (entered_index == 9) /*yulu*/
                
                case SDLK_y:
                if( !is_on_yulu ){
                    if( (!is_on_road) && (my_money > 10) && (entered_index == 9) /*yulu*/){
                        my_money = my_money -10;
                        steps_per_event = 10;
                        is_on_yulu = true;
                    }
                }else{
                    if( (!is_on_road) && (entered_index == 9) /*yulu*/){
                        steps_per_event = 5;
                        is_on_yulu = false;
                    }
                }
                
                break;

                case SDLK_6:
                if( (!is_on_road) && my_money > 10 ){
                    if (    //(entered_index == 22) /*amul*/ 
                             (entered_index == 26) /*apollo*/ 
                            //|| (entered_index == 10) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            //|| (entered_index == 36) /*grocery*/
                            //|| (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            //|| (entered_index == 8) /*night_mess*/
                            //|| (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/ ){
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }


                }break;
                
                case SDLK_5:
                if( (!is_on_road) && my_money > 10 ){
                    if (    //(entered_index == 22) /*amul*/ 
                             (entered_index == 26) /*apollo*/ 
                            //|| (entered_index == 10) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            || (entered_index == 36) /*grocery*/
                            //|| (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            //|| (entered_index == 8) /*night_mess*/
                            //|| (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/ ){
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }


                }break;
                
                case SDLK_4:
                if( (!is_on_road) && my_money > 10 ){
                    if (    //(entered_index == 22) /*amul*/ 
                            (entered_index == 26) /*apollo*/ 
                            || (entered_index == 10) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            || (entered_index == 36) /*grocery*/
                            || (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            //|| (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/ ){
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if( (entered_index == 19) /*scoop*/    
                        || (entered_index == 16) /*pentonic*/) {
                            my_money = my_money -10;
                        }


                }break;
                
                case SDLK_3:
                if( (!is_on_road) && my_money > 10 ){
                    if (    (entered_index == 22) /*amul*/ 
                            || (entered_index == 26) /*apollo*/ 
                            || (entered_index == 10) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            || (entered_index == 36) /*grocery*/
                            || (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            || (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            || (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/ ){
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if( (entered_index == 19) /*scoop*/    
                        || (entered_index == 16) /*pentonic*/) {
                            my_money = my_money -10;
                        }


                }break;
                
                case SDLK_2:
                if( (!is_on_road) && my_money > 10 ){
                    if (    (entered_index == 22) /*amul*/ 
                            || (entered_index == 26) /*apollo*/ 
                            || (entered_index == 10) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            || (entered_index == 36) /*grocery*/
                            || (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            || (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            || (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/ ){
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if( (entered_index == 19) /*scoop*/    
                        || (entered_index == 16) /*pentonic*/) {
                            my_money = my_money -10;
                        }


                }break;
                
                case SDLK_1:
                if( (!is_on_road) && my_money > 10 ){
                    if (    (entered_index == 22) /*amul*/ 
                            || (entered_index == 26) /*apollo*/ 
                            || (entered_index == 10) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            || (entered_index == 36) /*grocery*/
                            || (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            || (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            || (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/ ){
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }

                    if( (entered_index == 19) /*scoop*/    
                        || (entered_index == 16) /*pentonic*/) {
                            my_money = my_money -10;
                        }


                }break;


                case SDLK_e:
                x_s = (abs(destR_map.x)+ x_cord - 18 )/6;
                x_b = (abs(destR_map.x)+ x_cord + 18 )/6;
                y_s = (abs(destR_map.y)  + y_cord -18 )/6;
                y_b = (abs(destR_map.y)  + y_cord +18 )/6;
                x_n = (abs(destR_map.x)+ x_cord )/6;
                y_n = (abs(destR_map.y)  + y_cord )/6;
                if ( (a[y_n][x_s] > 1) && (a[y_n][x_s+2] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a[y_n][x_s];
                    }else{
                        is_on_road = true;
                        pop_on_screen = false;
                        entered_index = 1 ;
                    }
                }
                if ( (a[y_n][x_b] > 1) && (a[y_n][x_b-2] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a[y_n][x_b];
                    }else{
                        is_on_road = true;
                        pop_on_screen = false;
                        entered_index = 1 ;
                    }
                }
                if (( a[y_s][x_n] > 1) && ( a[y_s+2][x_n] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a[y_s][x_n];
                    }else{
                        is_on_road = true;
                        pop_on_screen = false;
                        entered_index = 1 ;
                    }
                }
                if (( a[y_b][x_n] > 1) && ( a[y_b-2][x_n] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a[y_b][x_n];
                    }else{
                        is_on_road = true;
                        pop_on_screen = false;
                        entered_index = 1 ;
                    }
                }
                break;

                default:
                break;
            }
        }
}


void GameObject :: Update(){
        srcR.h=20;
        srcR.w=20;
        srcR.x=0;
        srcR.y=0;

        destR.h = 30;
        destR.w = 30;
        destR.x = (x_cord-15);
        destR.y = (y_cord-15);

        srcR_map.h=1200;
        srcR_map.w=3000;
        srcR_map.x=0;
        srcR_map.y=0;

        destR_map.h = 1200;
        destR_map.w = 3000;

        destR_screen.h =800;
        destR_screen.w =1000;
        destR_screen.x = 0 ;
        destR_screen.y = 0 ;

        destR_health.h =20;
        destR_health.w = 100;
        destR_health.x =1000-300;
        destR_health.y = 10;

        destR_health_level.h = 11.5;
        destR_health_level.w = (100 - 19)*(health)/(max_health);
        destR_health_level.x = (100 - 19)*(max_health-health)/(max_health) + destR_health.x + 17.5 ;
        destR_health_level.y = 10+5;

        destR_money.h =20;
        destR_money.w = 100;
        destR_money.x = destR_health.x + destR_health.w + 20 ;
        destR_money.y = 10 ;
 
        if(hospital_task > 0 && food_task > 0 && lhc_task >0){
            won = 1;
        }else{
            won = 0;
        }
        textureText = to_string(my_money);
        SDL_Color textColor = { 182 , 237 , 10 };
        textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

}



void GameObject :: Render( SDL_Texture* player_2 , int position_1 , int position_2 ){

    SDL_RenderCopy(renderer,player_texture, NULL , &destR);
    SDL_RenderCopy(renderer, money_bar, NULL , &destR_money);
    SDL_RenderCopy(renderer, health_bar, NULL , &destR_health);
    SDL_RenderCopy(renderer, health_level, NULL , &destR_health_level);

    if( (position_1 >= abs(destR_map.x) ) && (position_1 <=  abs(destR_map.x) + 1000) &&  (position_2 >= abs(destR_map.y) ) && (position_2 <= abs(destR_map.y)+800 )){
        SDL_Rect Temp_destR ;
        Temp_destR.h=30;
        Temp_destR.w=30;
        Temp_destR.x= (position_1 - abs(destR_map.x) -15) ;
        Temp_destR.y= (position_2 - abs(destR_map.y) -15) ;
        SDL_RenderCopy(renderer, player_2, NULL , &Temp_destR);
    }else{
        SDL_Rect Temp_destR ;
        Temp_destR.h=20;
        Temp_destR.w=20;
        if( position_1 == abs(destR_map.x) + destR.x ){
            if(position_2 < abs(destR_map.y) + destR.y ){
                Temp_destR.x= position_1 ;
                Temp_destR.y= 80 -10;
            }else{
                Temp_destR.x= position_1 ;
                Temp_destR.y= 800 -80  -10;
            }
        }else if ( position_1 < abs(destR_map.x) + destR.x ){
            if(position_2 == abs(destR_map.y) + destR.y ){
                Temp_destR.x= 80 -10;
                Temp_destR.y= position_2;
            }else if(position_2 < abs(destR_map.y) + destR.y ){
                int y = dot_y ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 80 -10);
                if ( y >= 0 ){
                    Temp_destR.x= 80 -10;
                    Temp_destR.y= y;
                    if( Temp_destR.y < 80 -10 ) {
                        Temp_destR.y= 80 -10;
                    }
                }else{
                    Temp_destR.x= dot_x ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 80 -10);
                    Temp_destR.y= 80 -10;
                    if( Temp_destR.x < 80 -10 ) {
                        Temp_destR.x= 80 -10;
                    }
                }
            }else{
                int y = dot_y ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 80 -10);
                if ( y <= 800 ){
                    Temp_destR.x= 80 -10;
                    Temp_destR.y= y ;
                    if( Temp_destR.y > 800 -80  -10 ) {
                        Temp_destR.y = 800 -80  -10;
                    }
                }else{
                    Temp_destR.x= dot_x ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 800 -80 -10);
                    Temp_destR.y= 800 -80  -10;
                    if( Temp_destR.x < 80 -10 ) {
                        Temp_destR.x= 80 -10;
                    }
                }
            }
        }else{
            if(position_2 == abs(destR_map.y) + destR.y ){
                Temp_destR.x= 1000-80 -10;
                Temp_destR.y= position_2;
            }else if(position_2 < abs(destR_map.y) + destR.y ){
                int y = dot_y ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 1000 -80  -10);
                if ( y >= 0 ){
                    Temp_destR.x= 1000-80 -10;
                    Temp_destR.y= y;
                    if( Temp_destR.y < 80 -10 ) {
                        Temp_destR.y= 80 -10;
                    }
                    
                }else{
                    Temp_destR.x= dot_x ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 80-10);
                    Temp_destR.y= 80-10;
                    if( Temp_destR.x > 1000-80-10 ) {
                        Temp_destR.x = 1000-80-10;
                    }
                }
            }else{
                int y = dot_y ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 1000 -80-10);
                if ( y <= 800 ){
                    Temp_destR.x= 1000-80-10;
                    Temp_destR.y= y;
                    if( Temp_destR.y > 800 -80  -10 ) {
                        Temp_destR.y = 800 -80  -10;
                    }
                }else{
                    Temp_destR.x= dot_x ( position_1 , position_2 , abs(destR_map.x) + destR.x , abs(destR_map.y) + destR.y , 800 -80-10);
                    Temp_destR.y= 800-80-10;
                    if( Temp_destR.x > 1000-80-10 ) {
                        Temp_destR.x = 1000-80-10;
                    }
                }
            }
        }
        
       // Temp_destR.x= 100;
        //Temp_destR.y= 100;
        SDL_RenderCopy(renderer, warning , NULL , &Temp_destR);
    }
    if(!is_on_road){
        SDL_RenderCopy(renderer, entered[entered_index] , NULL , &destR_screen);
    }

    //text rendering
    SDL_Rect renderQuad = {  destR_money.x + 35 , destR_money.y + 6 , destR_money.w - 58 , destR_money.h - 8 };
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
    
}

void GameObject::ShowMap(SDL_Renderer* ren_chan ){
    Texture_m::Show(ren_chan , whole_map , srcR_map , destR_map );

}

