#ifndef DDR_H
#define DDR_H


#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <SD.h>
#include <lcd_image.h> 
#include <Adafruit_GFX.h>


// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define SD_CS    5  // Chip select line for SD card
#define TFT_CS   6  // Chip select line for TFT display
#define TFT_DC   7  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)



extern Adafruit_ST7735 tft;



// menu images
    extern lcd_image_t start_i;
    extern lcd_image_t diffi_i;
    extern lcd_image_t multi_i;
    extern lcd_image_t server_i;



// initializing joystick
const int VERT = 0;
const int HOR = 1;
const int SEL = 9;

// sd card variable
extern Sd2Card card;

extern int speed;
extern int difficulty;
extern int score_increment;
extern int streak;
extern int score;

const int LEDPINS[3] = {10, 11, 12};


 
// constant starting points for arrows
const int arrow_left_x = 10;
const int arrow_up_x = 39;
const int arrow_down_x = 68;
const int arrow_right_x = 99;


// assigning color variables
const uint16_t white = 0xFFFF;
const uint16_t black = 0000;
const uint16_t green = 0x07E0;
const uint16_t red = 0xF800;
const uint16_t cyan = 0x07FF;
const uint16_t magenta = 0xF81F;
const uint16_t blue = 0x001F;


// initialize the speakerPin
const int speakerPin = 13;

#define random_pin 2


// determines the tone of each arrow
void playTone(int period, int duration);

// plays the tone when called upon
void play_sound(int arrow_type);

/* function to take in random analog input and convert it 
   to a 32-bit number called a song. 
   Please ensure when using this function that the analog pin A2 is left 
   EMPTY. README will specify this as well.

   Some code from the random number generator posted on eclass is used here. 
   This will also be documented in the README
*/


uint32_t create_song();

/* this function will take the song and interpret it as arrow types
   as well as tones in a "song"

   it is also heavily based on information from the course provided Arduion intro 
   labs. 
   This is to be documented in the README
   please ensure int * arrow_type has enough mem for 
   8 int elements (declare using int arrow_type[8])
*/

void play_song(uint32_t song, int * arrow_type); 

// runs a certain set of lights for menu start up
void menu_lights1();

// another set of lights
void menu_lights2();

// plays tones for menu music
void menu_song();

// draws hit boxes - coordinates are going to change depending on the difficulty
// of the game
void triangle_hit_boxes();

// does the drawing work for void draw_arrow
void _draw_arrow(int x1, int x2, int x3, int y1, int y2, int y3, uint16_t color);

// main function that determines the flow of arrow
void draw_arrow(int arrow_type);

// loads the initial menu's and determines difficulty of game
int load_menu();

// special multiplayer menu
int join_host_menu();

// function for reading from other arduino
uint32_t read_from_serial3();

// function fo writing to another arduino
uint32_t write_to_serial3(uint32_t num);

// functions to communicate with other arduino
uint32_t server_setup(uint32_t);

uint32_t client_setup(uint32_t);

// arduinoo functions
void setup();

void loop();

#endif