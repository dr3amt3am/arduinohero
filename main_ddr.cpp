#include <ddr.h>

// standard initialization
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Sd2Card card;

// menu images
lcd_image_t start_i = {"start.lcd", 128, 160}; // start menu
lcd_image_t diffi_i = {"diffi.lcd", 128, 160}; // difficulty menu
lcd_image_t multi_i = {"mode.lcd", 128, 160};  // multiplayer menu
lcd_image_t server_i = {"server.lcd", 128, 160}; // server menu


// global variables needed to keep track of score/counter type variables
int speed = 2; // speed of the game
int difficulty = 1; // variable decided by menu option
int score_increment = 1; // how much score goes up by
int streak = 0; // keeps track of how many symbols in a row a user has hit
int score = 0; // score of the player

  
void setup() {

    // purely for testing purproses has no function for in game use
    Serial.begin(9600); // initiate Serial monitor 
    Serial3.begin(9600); // intitate communication with other arduino
    tft.initR(INITR_BLACKTAB); // intitate LCD screen

     // setting up joystick input
    pinMode(SEL, INPUT);
    digitalWrite(SEL, HIGH);

    // setting up speaker
    pinMode(speakerPin, HIGH);  

    int n = 0; // index for LED loop
     // makes all LED's outputs
    for(n = 0; n<3; ++n) {
        pinMode(LEDPINS[n], OUTPUT);
    }

    // initialize song array
    // this is the length of song for a game
    // means 32 arrows
    int song_array[32];


    // starts SD card
    Serial.print("Initializing SD card... ");
    if(!SD.begin(SD_CS)) {
        Serial.println("failed!");
        while(1){} // do nothing SD card not working
    }

    

    if (!card.init(SPI_HALF_SPEED, SD_CS)) {
        Serial.println("Raw SD Initialization has failed");
        while (1) {};  // Just wait, stuff exploded.
        // SD is working
        Serial.println("OKAY!");
    }

    // loads menu's and determines difficulty and # of players 
    int players = load_menu(); 
    int server_num = 0;

    // song variables
    uint32_t song1;
    uint32_t song2;
    uint32_t song3;
    uint32_t song4;

    // checks if multiplayer functionality is needed
    if(players > 1) { 

    server_num = join_host_menu(); // upload server menu

    }

    // code if user is the server
    if(server_num == 1) {
        tft.fillScreen(black);
        tft.println("Server mode engaged....");
        // enter server mode
        // we need four songs from our client!
        tft.print("wait for worthy opponent");
        delay(1000);
        tft.print(".");
        delay(1000);
        tft.print(".");
        delay(1000);
        tft.println(".");
         song1 = server_setup(1);
 
          // arduino recieves 4 sets of numbers of length 8 that together represent the whole song
         // to be played by both players
        while(!song1) { 
            // timeout try again
            song1 = server_setup(1);
            } 
            delay(100);
        song2 = server_setup(1);
        while(!song2) { 
            // timeout try again
            song2 = server_setup(1);
            } 
            delay(100);
        song3 = server_setup(1);
        while(!song3) { 
            // timeout try again
            song3 = server_setup(1);
            } 
            delay(100);
            song4 = server_setup(1);
        while(!song4) { 
            song4 = server_setup(1);
        }

        tft.print("Data transfer complete.... Engage!");\
        delay(3000);
    }






    // checks difficulty level and determines speed of game

   if(difficulty == 1) {

    speed = 5;
   }

   if(difficulty == 2) {

    speed = 7;
   }

   if(difficulty == 3) {

    speed = 9;
   }


    // create song if user is playing by themselves or is the client
   if(server_num == 0 || server_num == 2) {
        // create songs
        song1 = create_song();
        song2 = create_song();
        song3 = create_song();
        song4 = create_song();
    }
    if(server_num == 2) { 
        // client mode should be started
        tft.fillScreen(black);
        tft.setCursor(0,0);
        tft.println("Client mode engaged...");
        tft.println("Waiting for someone to accept your challenge...");
        Serial.println("client mode engaged");
        // send the songs over
        int check = 0;
        check = client_setup(song1);
        while(!check) { 
            // loop through timeouts
            check  = client_setup(song1);

        }
        delay(100);
        check = 0;
        check = client_setup(song2);
        while(!check) { 
            check = client_setup(song2);
        }
        delay(100);

        check = 0;
        check = client_setup(song3);
        while(!check) { 
            check = client_setup(song3);
        }
        delay(100);

        check = 0;
        check = client_setup(song4);
        while(!check) { 
            check = client_setup(song4);
        }

        tft.print("Data transfer complete.... Engage!");
        delay(3000);
    }




    play_song(song1, song_array);
    play_song(song2, song_array + 8);
    play_song(song3, song_array + 16);
    play_song(song4, song_array + 24);
    // code below is purely for running the main game

    tft.fillScreen(black); // fills the screen to black

    // prints out a countdown before game begins
    // LED's will light up
    tft.setCursor(0,0);
    tft.println("Ready?");
    delay(500);
    tft.println("3");
    digitalWrite(LEDPINS[0], HIGH);
    play_sound(1);
    delay(1000);
    tft.println("2");
    digitalWrite(LEDPINS[1], HIGH);
    play_sound(2);
    delay(1000);
    tft.println("1");
    digitalWrite(LEDPINS[2], HIGH);
    play_sound(3);
    delay(1000);
    tft.println("GO");
    play_sound(4);
    delay(500);
    tft.fillScreen(black);
    triangle_hit_boxes(); // draw hit boxes
    int i = 0;
    
    
    while( i < 32) {

        int score_previous = score;

            // below the if determines what lights to turn on
            // depends on the streak that the player is on
           if(score_increment == 1)
            {
                digitalWrite(LEDPINS[0], HIGH);
                digitalWrite(LEDPINS[1], LOW);
                digitalWrite(LEDPINS[2], LOW);
            }

              if(score_increment == 2)
            {
                digitalWrite(LEDPINS[0], HIGH);
                digitalWrite(LEDPINS[1], HIGH);
                digitalWrite(LEDPINS[2], LOW);
            }

              if(score_increment == 3)
            {
                digitalWrite(LEDPINS[0], HIGH);
                digitalWrite(LEDPINS[1], HIGH);
                digitalWrite(LEDPINS[2], HIGH);
            }


        // draws arrows randomly
        // same length as song
        draw_arrow(song_array[i]);

        // increments streak if user has successfully hit the arrow
        if(score > score_previous) {
            ++streak;
        }

        // increments score incrementer every 5 arrows in a row hit
         if(streak >= 5 && score_increment < 3) {

                    ++score_increment;
                    streak = 0;
                }

        // if arrow was missed resets streak and score_increment
        if(score < score_previous) {

            streak = 0;
            score_increment = 1;
        }
        i++;
              
    }


    tft.fillScreen(black);
    tft.setCursor(0,0);
 
    // prints out users score for single player
    if(!server_num) {
        tft.print("Your Score Was: ");
        tft.print(score);    
    }

    // if user was in a multiplayer match
    // calls cilent and server again to compare scores
    // prints out users score and opponents score
    // tells user if he won, lost or tied
    else { 

        int other_score = 0;

       if(server_num == 2) {

        other_score = client_setup(score);


       }

       if(server_num == 1) {

        other_score = server_setup(score);
       }

    
        

        if(other_score > score) { 
            tft.println("You lose :'(");
            tft.print("Your Score Was: ");
            tft.println(score);
            tft.print("Opponents Score was:");
            tft.println(other_score);

        }
        else if(score > other_score) { 
            tft.println("You win!");
            tft.print("Your Score Was: ");
            tft.println(score);
            tft.print("Opponents Score was:");
            tft.println(other_score);
            menu_song();
        }
        else { 
            tft.println("You tied!");
            tft.print("Your Score Was: ");
            tft.println(score);
            tft.print("Opponents Score was:");
            tft.println(other_score);
        }
    

    }
    
}




void loop() {}
