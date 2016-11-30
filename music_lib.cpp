#include <ddr.h>

// determins the tone of each arrow
void playTone(int period, int duration) {
    // elapsed time in microseconds, the long is needed to get
    // a big enough range.
 
    long elapsedTime = 0;
 
    // note we are making a slight error here if period is not even
    int  halfPeriod = period / 2;
 
    while (elapsedTime < duration * 1000L) {
      
        // generate a square wave of the given period.  Half the 
        // period is on, the other half is off.
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(halfPeriod);
 
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(halfPeriod);
 
        // count the time we just consumed for one cycle of the tone
        elapsedTime = elapsedTime + period;
    }
     
}
     

// plays the tone when called upon
void play_sound(int arrow_type) {
     // (1, 3, 5, 7 on a D Major Scale)
    // 7 might get a little yucky, we will have to see 
    // we need a different type of sound for every type of arrow
    // C Major scale!
   
    int tone; 
    
    if(arrow_type == 1) { 
        // first type is a "D note"
        // wikipedia search returns that (in microseconds) D
        // has a peroid of ~2273
        tone = 3405;
    }
    
    if(arrow_type == 2) { 
        // second type is a "F#"
        // wikipedia search gives us peroid in microseconds of
        // 2703
        tone = 2703;
    }

    if(arrow_type == 3) { 
        // we need an "A"
        // peroid: 2273
        tone = 2273;
    }

    if(arrow_type == 4) { 
        // this will be a C#
        // peroid: 1805
        tone = 1805;

    }
    playTone(tone, 50);
}

  
/* function to take in random analog input and convert it 
   to a 32-bit number called a song. 
   Please ensure when using this function that the analog pin A2 is left 
   EMPTY. README will specify this as well.

   Some code from the random number generator posted on eclass is used here. 
   This will also be documented in the README
*/
#define random_pin 2
uint32_t create_song() { 
    
    // ideally this should be done in setup 
    pinMode(random_pin, INPUT);
   
    uint32_t song;
   
    // now the part borrowed from class code: 
    for(int i = 0; i < 31; ++i) {
    
        // bit-wise assignment 
        song = song + analogRead(random_pin) % 2;
        song = song << 1; // next bit
        // class code has a delay here, going to try without it first
    }
    return song;
}



/* this function will take the song and interpret it as arrow types
   as well as tones in a "song"

   it is also heavily based on information from the course provided Arduion intro 
   labs. 
   This is to be documented in the README
   please ensure int * arrow_type has enough mem for 
   8 int elements (declare using int arrow_type[8])
*/

void play_song(uint32_t song, int * arrow_type) { 
    // first let's find the arrow type
    // take four bits from song

    // index variables
    int k = 0; 
    int j = 0;
   
    while(k < 8) {
    
        int value = 0; // intermediate value
       
        for(int i = j; i < j + 3; ++i) {
            // (the transfer is inverted but for our purposes this does not matter) 
            value += (song >> i) % 2;
        }
        arrow_type[k] = value + 1;
        ++k;
        j+=3;

    }
        
}

void menu_lights1() {

    digitalWrite(LEDPINS[0], HIGH);
    digitalWrite(LEDPINS[1], LOW);
    digitalWrite(LEDPINS[2], HIGH);
}

void menu_lights2() {

    digitalWrite(LEDPINS[0], LOW);
    digitalWrite(LEDPINS[1], HIGH);
    digitalWrite(LEDPINS[2], LOW);
}


void menu_song() {

int loop_the_song = 0;
    while(loop_the_song < 4) {
        play_sound(1);
        menu_lights1();
        play_sound(1);
        menu_lights2();
        play_sound(3);
        menu_lights1();
        play_sound(3);
        menu_lights2();
        play_sound(1);
        menu_lights1();
        play_sound(1);
        menu_lights2();
        play_sound(3);
        menu_lights1();
        play_sound(3);
        menu_lights2();
        play_sound(1);
        menu_lights1();
        play_sound(1);
        menu_lights2();
        play_sound(2);
        menu_lights1();
        play_sound(2);
        menu_lights2();
        play_sound(4);
        menu_lights1();
        play_sound(1);
        menu_lights2();
        play_sound(1);
        menu_lights1();
        ++loop_the_song;
    }
    play_sound(1);
    menu_lights2();
    play_sound(2);
    menu_lights1();
    play_sound(3);
    menu_lights2();
    play_sound(4);
    menu_lights1();
    play_sound(1);
    menu_lights2();
  
    while(loop_the_song < 8) {
        play_sound(1);
        menu_lights1();
        play_sound(1);
        menu_lights2();
        play_sound(4);
        menu_lights1();
        play_sound(4);
        menu_lights2();
        play_sound(1);
        menu_lights1();
        play_sound(1);
        menu_lights2();
        play_sound(2);
        menu_lights1();
        play_sound(2);
        menu_lights2();
        play_sound(3);
        menu_lights1();
        play_sound(3);
        menu_lights2();
        play_sound(1);
        menu_lights1();
        play_sound(1);
        ++loop_the_song;
    }
    play_sound(1);
    menu_lights1();
    play_sound(1);
    menu_lights2();
    play_sound(1);
    menu_lights1();
    play_sound(1);
    menu_lights2();
    play_sound(1);
    menu_lights1();
    play_sound(1);
    menu_lights2();

    digitalWrite(LEDPINS[0], LOW);
    digitalWrite(LEDPINS[1], LOW);
    digitalWrite(LEDPINS[2], LOW);

}

  


