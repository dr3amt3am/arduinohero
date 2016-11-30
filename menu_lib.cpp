 #include <ddr.h>


// loads menu and returns number of players
int load_menu() {

int player_num = 1;

 // loads start menu screen 
     lcd_image_draw(&start_i, &tft, 0, 0, 0, 0, 128, 160);
       
     menu_song(); // plays menu music

     lcd_image_draw(&multi_i, &tft, 0, 0, 0, 0, 128, 160); // loads multiplayer menu

        int menu_y = 37; // coordinate for menu box


    while(digitalRead(SEL)) {


        // amateur menu
        tft.drawRect(37, menu_y, 57, 52, blue);

        // detects user joystick movement down
        if(analogRead(VERT) > 1000 && player_num < 2) {

            ++player_num; // corresponds to number of players
            // rock start coordiantes
            lcd_image_draw(&multi_i, &tft, 37, menu_y, 37, menu_y, 57, 52);
            menu_y+=57; // increments menu coordinates

            // legendary cursor box
            tft.drawRect(37, menu_y, 57, 52, blue);
            delay(50); // delay to avoid unwanted feedback
    }

    // this if watches for upward joystick movement
    if(analogRead(VERT) < 15 && player_num > 1) {

            --player_num;
            lcd_image_draw(&multi_i, &tft, 37, menu_y, 37, menu_y, 57, 52);
           
            menu_y-= 57;
            
            tft.drawRect(37, menu_y, 57, 52, blue);
            delay(50);

    }

    }






     lcd_image_draw(&diffi_i, &tft, 0, 0, 0, 0, 128, 160); // loads difficulty menu

         menu_y = 33; // coordinate for menu box

        // amateur menu
        tft.drawRect(3, menu_y, 122, 23, blue);
       
    // until user chooses a menu option do nothing
    while(digitalRead(SEL)) {

        // detects user joystick movement down
        if(analogRead(VERT) > 1000 && difficulty < 3) {

            ++difficulty; // corresponds to user choice in difficulty
            // rock start coordiantes
            lcd_image_draw(&diffi_i, &tft, 3, menu_y, 3, menu_y, 122, 23);
            menu_y+=37; // increments menu coordinates

            // legendary cursor box
            tft.drawRect(3, menu_y, 122, 23, blue);
            delay(50); // delay to avoid unwanted feedback
    }

    // this if watches for upward joystick movement
    if(analogRead(VERT) < 15 && difficulty  > 1) {

            --difficulty;
            lcd_image_draw(&diffi_i, &tft, 3, menu_y, 3, menu_y, 122, 23);
            menu_y-=37;
            tft.drawRect(3, menu_y, 122, 23, blue);
            delay(50);

    }


}

return player_num;
}

// loads specific join or host menu
// returns 1 or 2, 1 being new, 2 being join
int join_host_menu () {

int k = 1;
int menu_y = 23;

lcd_image_draw(&server_i, &tft, 0, 0, 0, 0, 128, 160); // loads server menu

 while(digitalRead(SEL)) {


        // amateur menu
        tft.drawRect(0, menu_y, 128, 54, blue);

        // detects user joystick movement down
        if(analogRead(VERT) > 1000 && k < 2) {

            ++k; // corresponds to number of players
            // rock start coordiantes
            lcd_image_draw(&server_i, &tft, 0, menu_y, 0, menu_y, 128, 54);
            menu_y+=60; // increments menu coordinates

            // legendary cursor box
            tft.drawRect(0, menu_y, 128, 54, blue);
            delay(50); // delay to avoid unwanted feedback
    }

    // this if watches for upward joystick movement
    if(analogRead(VERT) < 15 && k > 1) {

            --k;
            lcd_image_draw(&server_i, &tft, 0, menu_y, 0, menu_y, 128, 54);
           
            menu_y-= 60;
            
            tft.drawRect(0, menu_y, 128, 54, blue);
            delay(50);

    }

    }


return k;
}