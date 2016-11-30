Project: Arduino Hero
By: Kelvin Liang, Joey-Michael Fallone
Section: A1

Description: This program is an emulation of popular DDR and 
Guitar Hero video games for the Arduino. The game’s objective is 
to “hit” the arrows as they move down the screen and into the 
“hitboxes” located at the bottom of the screen.There are three 
difficulties, amateur, rock star and legendary, which may be 
chosen. The easiest difficulty is amateur, the hardest is 
legendary. There is an incremental increase in the speed at 
which arrows move for rock star and legendary modes. The game 
may be played with a single player or with another player if two 
Arduinos are present. For more details on playing with two 
players, please see the setup section of this README.
During the game the LEDs act as a multiplier indicator. One 
light on means the user has the lowest multiplier meaning he/she 
only gets one point for each arrow hit. Two lights means each \
arrow hit counts for two points, and of course three lights 
increases the value of an arrow hit to three points. The 
multiplier starts at one and increases every five arrow hits in 
a row up to the maximum multiplier value of three points per 
arrow hit. If an arrow is not hit, the score is decremented by 
one, and the multiplier is reset to one. A total of 32 arrows 
will come down the screen during one single game with a maximum 
score of 81, and a minimum score of -32. Once the game is 
complete the score will be displayed on the screen. In a 
multiplayer game the opponent’s score will also be displayed, 
and the winner will be notified. 


Game Instructions: Upon compiling and uploading to the Arduino 
the main menu will load onto the screen, user will then hear the 
theme music of the game and the 3 LED's should start flashing. 
After this a menu will appear on the screen prompting the user 
to choose the number of players. Once the number of players is 
decided the Arduino will prompt the user for difficulty level.In 
one-player mode, the Arduino will immediately countdown towards 
the start of the game after difficulty level is chosen. Each LED 
will also light up during countdown. In two-player mode, a menu 
will appear with two options: host and join. If no Arduino has 
set up a new game yet, choose host. If a game has already been 
hosted on one of the Arduinos, please select join. Upon choosing 
a mode the arduino will attempt to connect to the other arduino. 
Once a connection is established the Arduino will commence 
countdown to the game. 

A new game may be started at any time by resetting the Arduino.



Setup: This game makes use of the adafruit LCD screen, a 
joystick, the piezo speaker, 3 LED's, and a 4GB micro SD card. 
To properly setup the arduino, first wire the screen and 
joystick up according to the University of Alberta standards, 
which may be found at the following url: http://ugweb.cs.ualberta
.ca/~c274/web/ConcreteComputing/section/adafruit_lcd.htm. Ensure 
that you leave room for the three LEDs, while orienting the 
joystick and LCD screen in a fashion with which you may 
comfortably interact with the joystick while seeing the screen.. 
Now wire the speaker with one wire to GND and one wire to pin 13 
on the arduino. When wiring the three LEDs, please find a 
position where they may be seen while playing the game. The 
leftmost LED should be wired to pin 10, the middle one to pin 11 
and the rightmost one to pin 12. Remember to use a 560 Ohm (
Green Blue Brown) for each of the LEDs. Finally included with 
the rest of the code files should be a set of images named "start
.bmp", "diffi.bmp", "mode.bmp" and "server.bmp" in a directory 
titled “SD_FILES.” Take these images and load them onto the 
microSD card (FAT32) and insert into the screen on the arduino. 
The arduino should now be ready to play a single player game. If 
user wants to play with another arduino connect two arduinos by 
first making a common ground between the two devices and 
connecting the arduinos through the "TX3" and "RX3" pins. 
Note: Please only use the Makefile provided in the package, as 
Adafruit and lcdimagedraw libraries are required. 

Acknowledgements: This program makes use of numerous in-class (CMPUT 274)
functions. 
From eClass: 
			void create_song (modification of random16bits)
			SD Card initialization 
			Header File Examples
From Arduino Intro Labs: 
			void playTone
From our old assignments: 
				the server and client functions were taken from 
				our earlier 
				assignment 1 part 2, specifically our 
				implementation of the three 
				way handshake.
From the Internet: 
				“extern” which was used in the header file to 
				allow for declaration of global
				variables (http://www.cplusplus.
				com/forum/general/21368/)


