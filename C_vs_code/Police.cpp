#include <bits/stdc++.h>
#include "Game.h"
#include "Texture_m.h"
#include "maze.h"


int a_2[200][500] = Matrix__;
Police :: Police( SDL_Renderer* ren_chan , const char* name , int x , int y){

    renderer = ren_chan;
    player_texture = Texture_m :: Load_Texture( player_texture , ren_chan , name);
    
    
    Police_img = name;
    whole_map = Texture_m::Load_Texture(  whole_map , ren_chan , "map.png");
    blend = Texture_m::Load_Texture(  blend , ren_chan , "blend.png");

    money_bar = Texture_m::Load_Texture(  money_bar , ren_chan , "bars/money_bar.png");
    health_bar = Texture_m::Load_Texture(  health_bar, ren_chan , "bars/health_bar.png");
    health_level = Texture_m::Load_Texture(  health_level, ren_chan , "bars/health.png");
    time_level = Texture_m::Load_Texture(  time_level , ren_chan , "bars/blue_time.png");
    
    task_list = Texture_m::Load_Texture(  task_list , ren_chan , "entered/task_list.png");
    


    x_cord =x;
    y_cord = y;
    destR_map.x = 0;
    destR_map.y = 0;
    steps_per_event = 5;

    is_on_road = true;
    is_on_yulu = false;
    pop_on_screen = false;
    show_task_list = false;

    entered_index = 0;
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
    health = 190;
    max_health = 190;

    total_shift_time = 3*60;
    shift_time_spent = 1;
    yulu_counter =0;

        //Open the font
    TTF_Init();
    gFont = TTF_OpenFont( "Helvetica-BoldOblique.ttf", 28 );

    //Render text
    textureText = to_string(my_money);

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) ; 
    
    m_transaction = Mix_LoadWAV( "music/transaction.wav" );  
    m_eating = Mix_LoadWAV( "music/eating.wav" ); 
    m_drinking = Mix_LoadWAV( "music/drinking.mp3" ); 

}

void Police :: Handle_events( SDL_Event event ){



            if( event.type == SDL_KEYDOWN )
            {
            switch( event.key.keysym.sym )
            {


                case SDLK_SPACE:
                if( !show_task_list ){
                    
                    show_task_list = true;
                }else{

                    show_task_list = false;
                }break;


                case SDLK_UP:
                if(is_on_road){
                    y_cord = (y_cord -steps_per_event);
                    if (destR_map.y >= 0){

                        if (y_cord < 0 ){
                            y_cord = 0;
                        }
                        if ( a_2[ (abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1) {
                            y_cord = y_cord+steps_per_event;
                        }
                    }else {

                        if ( a_2[ (abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1) {
                            y_cord = y_cord+steps_per_event;
                        }else {
                            if ( y_cord < 200){
                                y_cord = 200;
                                destR_map.y = destR_map.y+steps_per_event;
                            }
                        }
                    }
                }
                break;

                case SDLK_DOWN:
                if(is_on_road){
                    y_cord = (y_cord +steps_per_event);
                    if (destR_map.y <= -1000){
                        if (y_cord >= 800 ){
                            y_cord = 800-steps_per_event;
                        }
                        if ( a_2[(abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1){
                            y_cord = (y_cord -steps_per_event);
                        }
                    }else {
                        if ( a_2[(abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1){
                            y_cord = (y_cord -steps_per_event);
                        }else {
                            if ( y_cord > 800-200){
                                y_cord = 800-200;
                                destR_map.y = destR_map.y-steps_per_event;
                            }
                        }

                    }
                }
                break;


                case SDLK_LEFT:
                if(is_on_road){
                    x_cord = (x_cord -steps_per_event);
                    if (destR_map.x >= 0){
                        if (x_cord < 0 ){
                            x_cord = 0;
                        }
                        if ( a_2[ (abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1){
                            x_cord = (x_cord +steps_per_event);
                        }
                    }else{
                        if ( a_2[ (abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1){
                            x_cord = (x_cord +steps_per_event);
                        }else{
                            if ( x_cord < 250){
                                x_cord = 250;
                                destR_map.x = destR_map.x+steps_per_event;
                            }
                        }
                    }
                }
                break;


                case SDLK_RIGHT:
                if(is_on_road){
                    x_cord = (x_cord +steps_per_event);
                    if (destR_map.x <= -3500){
                        if (x_cord >= 1000 ){
                            x_cord = 1000-steps_per_event;
                        }
                        if ( a_2[ (abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1){
                            x_cord = (x_cord - steps_per_event);
                        }
                    }else{
                        if ( a_2[ (abs(destR_map.y)  + y_cord)/9 ][ (abs(destR_map.x)+ x_cord)/9 ] != 1){
                            x_cord = (x_cord - steps_per_event);
                        }else{
                            if ( x_cord > 1000 -250){
                                x_cord = 1000 -250;
                                destR_map.x = destR_map.x -steps_per_event;
                            }
                        }
                    }
                }
                break;

                //  (entered_index == 22) /*amul*/
                //  (entered_index == 26) /*apollo*/
                //  (entered_index == 11) /*ccd*/
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
                        steps_per_event = 9;
                        is_on_yulu = true;
                        yulu_counter = 10;
                        Mix_PlayChannel( -1, m_transaction , 0 );
                    }
                }else{
                    if( (!is_on_road) && (entered_index == 9) /*yulu*/){
                        steps_per_event = 5;
                        is_on_yulu = false;
                        yulu_counter = 0;
                    }
                }
                
                break;

                case SDLK_6:
                if( (!is_on_road) && my_money > 10 ){
                    
                    if(     (entered_index == 26) /*apollo*/                             
                            ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if(      
                             (entered_index == 17) /*delhi16*/                           
                            
                            || (entered_index == 25) /*masala_mix*/
                            || (entered_index == 18) /*rajdhani*/
                            
                            
                            || (entered_index == 24) /*staff_canteen*/
                            ){
                                Mix_PlayChannel( -1, m_drinking , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }


                }break;
                
                case SDLK_5:
                if( (!is_on_road) && my_money > 10 ){
                    if(     (entered_index == 26) /*apollo*/                             
                            || (entered_index == 36) /*grocery*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            //|| (entered_index == 19) /*scoop*/    
                            //|| (entered_index == 16) /*pentonic*/
                            ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if(      
                             (entered_index == 17) /*delhi16*/                           
                            
                            || (entered_index == 25) /*masala_mix*/
                            || (entered_index == 18) /*rajdhani*/
                            
                            
                            || (entered_index == 24) /*staff_canteen*/
                            ){
                                Mix_PlayChannel( -1, m_drinking , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }


                }break;
                
                case SDLK_4:
                if( (!is_on_road) && my_money > 10 ){
                    if(     (entered_index == 26) /*apollo*/                             
                            ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if(        (entered_index == 19) /*scoop*/    
                            || (entered_index == 16) /*pentonic*/
                            ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                my_money = my_money -10;
                    }
                    if(      
                            (entered_index == 11) /*ccd*/
                            || (entered_index == 17) /*delhi16*/                           
                            || (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            || (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            
                            || (entered_index == 24) /*staff_canteen*/
                            ){
                                Mix_PlayChannel( -1, m_drinking , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }

                }break;
                
                case SDLK_3:
                if( (!is_on_road) && my_money > 10 ){

                    if(     (entered_index == 26) /*apollo*/                             
                            || (entered_index == 36) /*grocery*/
                            || (entered_index == 35) /*mother_dairy*/
                            ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if(      (entered_index == 19) /*scoop*/    
                        ||  (entered_index == 16) /*pentonic*/  ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                my_money = my_money -10;    
                    }
                    if(     (entered_index == 22) /*amul*/ 
                            //|| (entered_index == 26) /*apollo*/ 
                            //|| (entered_index == 11) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            //|| (entered_index == 36) /*grocery*/
                            //|| (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            //|| (entered_index == 8) /*night_mess*/
                            //|| (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/){
                                Mix_PlayChannel( -1, m_eating , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if(      
                            (entered_index == 11) /*ccd*/
                            //|| (entered_index == 17) /*delhi16*/                           
                            || (entered_index == 29) /*ich*/
                            //|| (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            || (entered_index == 28) /*shiru*/
                            //|| (entered_index == 24) /*staff_canteen*/
                            ){
                                Mix_PlayChannel( -1, m_drinking , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    


                }break;
                
                case SDLK_2:
                if( (!is_on_road) && my_money >= 10 ){

                    if(     (entered_index == 26) /*apollo*/                             
                            || (entered_index == 36) /*grocery*/
                            || (entered_index == 35) /*mother_dairy*/
                            
                            ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }

                    if(         (entered_index == 19) /*scoop*/    
                            || (entered_index == 16) /*pentonic*/  ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                my_money = my_money -10;    
                    }

                    if(     (entered_index == 22) /*amul*/ 
                            //|| (entered_index == 26) /*apollo*/ 
                            //|| (entered_index == 11) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            //|| (entered_index == 36) /*grocery*/
                            //|| (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            //|| (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/){
                                Mix_PlayChannel( -1, m_eating , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if(      
                            (entered_index == 11) /*ccd*/
                            //|| (entered_index == 17) /*delhi16*/                           
                            || (entered_index == 29) /*ich*/
                            //|| (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 18) /*rajdhani*/
                            //|| (entered_index == 8) /*night_mess*/
                            || (entered_index == 28) /*shiru*/
                            //|| (entered_index == 24) /*staff_canteen*/
                            ){
                                Mix_PlayChannel( -1, m_drinking , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }

                    


                }break;
                
                case SDLK_1:
                if( (!is_on_road) && my_money >= 10 ){

                if(    (entered_index == 26) /*apollo*/ 
                    || (entered_index == 36) /*grocery*/
                    || (entered_index == 35) /*mother_dairy*/  ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                           
                    }
                    if(      (entered_index == 19) /*scoop*/    
                        || (entered_index == 16) /*pentonic*/  ){
                                Mix_PlayChannel( -1, m_transaction , 0 );
                                my_money = my_money -10;    
                    }

                    if(     (entered_index == 22) /*amul*/ 
                            //|| (entered_index == 26) /*apollo*/ 
                            //|| (entered_index == 11) /*ccd*/
                            || (entered_index == 17) /*delhi16*/
                            //|| (entered_index == 36) /*grocery*/
                            //|| (entered_index == 29) /*ich*/
                            || (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            || (entered_index == 18) /*rajdhani*/
                            || (entered_index == 8) /*night_mess*/
                            //|| (entered_index == 28) /*shiru*/
                            || (entered_index == 24) /*staff_canteen*/){
                                Mix_PlayChannel( -1, m_eating , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }
                    if(     //(entered_index == 22) /*amul*/ 
                            //|| (entered_index == 26) /*apollo*/ 
                            (entered_index == 11) /*ccd*/
                            //|| (entered_index == 17) /*delhi16*/
                            //|| (entered_index == 36) /*grocery*/
                            || (entered_index == 29) /*ich*/
                            //|| (entered_index == 25) /*masala_mix*/
                            //|| (entered_index == 35) /*mother_dairy*/
                            //|| (entered_index == 18) /*rajdhani*/
                            //|| (entered_index == 8) /*night_mess*/
                            || (entered_index == 28) /*shiru*/
                            //|| (entered_index == 24) /*staff_canteen*/
                            ){
                                Mix_PlayChannel( -1, m_drinking , 0 );
                                health = health +10;
                                if(health > max_health){
                                    health = health - 10;
                                }
                                my_money = my_money -10;
                    }                    

                    


                }break;

                case SDLK_e:
                x_s = (abs(destR_map.x)+ x_cord - 27 )/9;
                x_b = (abs(destR_map.x)+ x_cord + 27 )/9;
                y_s = (abs(destR_map.y)  + y_cord -27 )/9;
                y_b = (abs(destR_map.y)  + y_cord +27 )/9;
                x_n = (abs(destR_map.x)+ x_cord )/9;
                y_n = (abs(destR_map.y)  + y_cord )/9;
                if ( (a_2[y_n][x_s] > 1) && (a_2[y_n][x_s+2] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a_2[y_n][x_s];
                    }else{
                        is_on_road = true;
                        pop_on_screen = false;
                        entered_index = 1 ;
                    }
                }
                if ( (a_2[y_n][x_b] > 1) && (a_2[y_n][x_b-2] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a_2[y_n][x_b];
                    }else{
                        is_on_road = true;
                        pop_on_screen = false;
                        entered_index = 1 ;
                    }
                }
                if (( a_2[y_s][x_n] > 1) && ( a_2[y_s+2][x_n] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a_2[y_s][x_n];
                    }else{
                        is_on_road = true;
                        pop_on_screen = false;
                        entered_index = 1 ;
                    }
                }
                if (( a_2[y_b][x_n] > 1) && ( a_2[y_b-2][x_n] > 1)){
                    if(is_on_road){
                        is_on_road = false;
                        pop_on_screen = true;
                        entered_index = a_2[y_b][x_n];
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


void Police :: Update(){
        srcR.h=20;
        srcR.w=20;
        srcR.x=0;
        srcR.y=0;

        destR.h = 30;
        destR.w = 30;
        destR.x = (x_cord -15);
        destR.y = (y_cord -15);

        srcR_map.h=1800;
        srcR_map.w=4500;
        srcR_map.x=0;
        srcR_map.y=0;

        destR_map.h = 1800;
        destR_map.w = 4500;

        destR_screen.h=800;
        destR_screen.w=1000;
        destR_screen.x= 0 ;
        destR_screen.y= 0 ;

        destR_health.h =20;
        destR_health.w = 100;
        destR_health.x =1000-300;
        destR_health.y = 10;

        destR_time.h =20;
        destR_time.w = 100;
        destR_time.x =1000-300 -120 ;
        destR_time.y = 10;

        destR_health_level.h = 11.5;
        destR_health_level.w = (100 - 19)*(health)/(max_health);
        destR_health_level.x = (100 - 19)*(max_health-health)/(max_health) + destR_health.x + 17.5 ;
        destR_health_level.y = 10+5;

        destR_time_level.h = 11.5;
        destR_time_level.w = (100 - 19)*(total_shift_time-shift_time_spent)/(total_shift_time);
        destR_time_level.x = (100 - 19)*(shift_time_spent)/(total_shift_time) + destR_time.x + 17.5 ;
        destR_time_level.y = 10+5;

        destR_money.h =20;
        destR_money.w = 100;
        destR_money.x = destR_health.x + destR_health.w + 20 ;
        destR_money.y = 10 ;
 
        textureText = to_string(my_money);
        SDL_Color textColor = { 182 , 237 , 10 };
        textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

        if(yulu_counter == 0){
            steps_per_event = 5;
            is_on_yulu = false;
            
        }
}


void Police :: Render( SDL_Texture* player_2 , int position_1 , int position_2 ){
    SDL_RenderCopy(renderer , player_texture, NULL , &destR);
    SDL_RenderCopy(renderer, money_bar, NULL , &destR_money);
    SDL_RenderCopy(renderer, health_bar, NULL , &destR_health);
    SDL_RenderCopy(renderer, health_level, NULL , &destR_health_level);
    SDL_RenderCopy(renderer, health_bar, NULL , &destR_time);
    SDL_RenderCopy(renderer, time_level, NULL , &destR_time_level);

    if( (position_1 >= abs(destR_map.x) ) && (position_1 <=  abs(destR_map.x) + 1000) &&  (position_2 >= abs(destR_map.y) ) && (position_2 <= abs(destR_map.y)+800 )){
        SDL_Rect Temp_destR ;
        Temp_destR.h=30;
        Temp_destR.w=30;
        Temp_destR.x= (position_1 - abs(destR_map.x) -15)/1 ;
        Temp_destR.y= (position_2 - abs(destR_map.y) -15)/1 ;
        //SDL_DestroyRenderer(renderer);
        SDL_RenderCopy(renderer, player_2, NULL , &Temp_destR);
    }
    if(!is_on_road){
        SDL_RenderCopy(renderer, entered[entered_index] , NULL , &destR_screen);
    }
    SDL_Rect blend_destR ;
        blend_destR.h=800;
        blend_destR.w=1000;
        blend_destR.x= 0 ;
        blend_destR.y= 0 ;
    SDL_RenderCopy(renderer , blend , NULL , &blend_destR);
    
    //text rendering
    SDL_Rect renderQuad;
    if ( my_money < 10){
        renderQuad = {  destR_money.x + 35+7+3 , destR_money.y + 06 , (destR_money.w - 58)/3 , destR_money.h - 8 };
    }else if(my_money < 100){
        renderQuad = {  destR_money.x + 35+7 , destR_money.y + 06 , (destR_money.w - 58)*2/3 , destR_money.h - 8 };
    }else{
        renderQuad = {  destR_money.x + 35 , destR_money.y + 06 , (destR_money.w - 58) , destR_money.h - 8 };
    }
    if(show_task_list){
        SDL_RenderCopy( renderer, task_list, NULL, &destR_screen );
    }

    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );


}

void Police ::ShowMap(SDL_Renderer* ren_chan ){
    //SDL_RenderCopy(renderer, whole_map , NULL , &destR_);
    Texture_m::Show(ren_chan , whole_map , srcR_map , destR_map );
    

}

