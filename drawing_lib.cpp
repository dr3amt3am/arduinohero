#include "ddr.h"


// draws hit boxes - coordinates are going to change depending on the difficulty
// of the game
void triangle_hit_boxes () {

    tft.drawTriangle(10, 150, 24, 142, 24, 158, ST7735_WHITE);
    tft.drawTriangle(39, 142, 47, 158, 55, 142, ST7735_WHITE);
    tft.drawTriangle(68, 158, 76, 142, 84, 158, ST7735_WHITE);
    tft.drawTriangle(99, 142, 99, 158, 113,150, ST7735_WHITE);

}

// does the drawing work for void draw_arrow
void _draw_arrow(int x1, int x2, int x3, int y1, int y2, int y3, uint16_t color) { 
    // all the drawing work  
    tft.drawTriangle(x1, y1, x2, y2, x3, y3, color);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
	
}

// main function that determines the flow of arrows
void draw_arrow(int arrow_type) { 
   
    // flags to ensure that only 1 point gets assigned or taken away
    // in one iteration 
    int flag = 0;
    int flag2 = 0;
    
    // choose arrow mode
    // left arrow
    if(arrow_type == 1) { 
	
        uint16_t color = magenta; // assigns a color
        int ypos = 10; // initial position of y
        int  x = arrow_left_x; // initial position of x
        _draw_arrow(x,x + 14, x + 14, ypos, ypos - 8, ypos + 8, color); // draws the arrow at the top
       
        // stops when the arrow is off the screen 
        while(ypos < 180) { 

            // draws over the previous arrow 
            _draw_arrow(x,x + 14, x + 14, ypos, ypos - 8, ypos + 8, black);
            ypos+=speed; // changes the location of the arrow and is the difficulty of the game
            
            // draws the new arrow in the next position of the screen
            _draw_arrow(x,x + 14, x + 14, ypos, ypos - 8, ypos + 8, color);

            // checks that the user has made the correct analog stick movement
            // user recieves a point
            if (ypos >= 140 && analogRead(HOR) < 15 && ypos <= 160 && flag == 0) { 
            
                score = score + score_increment; // increments the score
                play_sound(1); // plays the sound
                flag = 1; // dont deduct future points!
                color = green; // changes the color of arrows to green

            }
            
            // re draws hit boxes as incoming arrow comes over
            if(ypos >= 140) {
                triangle_hit_boxes();
            }

            // if they missed the hit box, deduct a point
            if(ypos > 160 && flag == 0) { 
                --score; // deducts a point from user score
                flag = 1;
                          
            }
                        
	}		       	
    }


    // choose arrow mode
    // down arrow
    // previous comments apply here
    if(arrow_type == 2) { 
	
        uint16_t color = red;
        int ypos = 2;
        int  x = arrow_up_x;
        _draw_arrow(x,x + 8, x + 14, ypos, ypos + 14, ypos, color);
        while(ypos < 180) { 
            
            _draw_arrow(x,x + 8, x + 14, ypos, ypos + 14, ypos, black);
            ypos+=speed;
            
            _draw_arrow(x,x + 8, x + 14, ypos, ypos + 14, ypos, color);
            if (ypos >= 140 && analogRead(VERT) > 1000 && ypos <= 160 && flag == 0) { 

                score = score + score_increment;
                play_sound(2);
                flag = 1; // dont deduct future points!
                color = green;

            }

            if(ypos >= 140) {
                triangle_hit_boxes();
            }


            // if they missed the hit box, deduct a point
            if(ypos > 160 && flag == 0) { 
                --score;
                flag = 1;
            }           
	}		      	
    }


    // determine arrow type
    // down arrow
    // previous comments apply here
    if(arrow_type == 3) { 
	
        uint16_t color = blue;
        int ypos = 18;
        int  x = arrow_down_x;
       
        _draw_arrow(x,x + 8, x + 14, ypos, ypos - 14, ypos, color);
       

        while(ypos < 180) { 
            
            _draw_arrow(x,x + 8, x + 14, ypos, ypos - 14, ypos, black);
            ypos+=speed; 
          
            _draw_arrow(x,x + 8, x + 14, ypos, ypos - 14, ypos, color);
           
           
            if (ypos >= 140 && analogRead(VERT) < 15 && ypos <= 160 && flag == 0) { 

                score = score + score_increment;
                play_sound(3); 
                flag = 1; 
                color = green; 

            }
          
            if(ypos >= 140) {

                triangle_hit_boxes();

            }

            // if they missed the hit box, deduct a point
            if(ypos > 160 && flag == 0) { 
                --score;
                flag = 1;
            }
	}		       	
    }


    // determine arrow type
    // right arrow
    // previous comments apply here
    if(arrow_type == 4) { 
	
        uint16_t color = cyan;
        int ypos = 2;
        int  x = arrow_right_x;
        
        _draw_arrow(x,x, x + 14, ypos, ypos+14, ypos+6, color);
        
        while(ypos < 180) { 
           
            _draw_arrow(x,x, x+14, ypos, ypos+14, ypos+6, black);
            ypos+=speed;    
            _draw_arrow(x,x, x+14, ypos, ypos+14, ypos+6, color);
            

            if (ypos >= 140 && analogRead(HOR) > 1000 && ypos <= 160 && flag == 0) { 
                play_sound(4);
                score = score + score_increment;
                flag = 1; // dont deduct future points!
                color = green;

            }

            if(ypos >= 140) {
                triangle_hit_boxes();
            }

            // if they missed the hit box, deduct a point
            if(ypos > 160 && flag  == 0) { 
                --score;
                flag = 1;
            }         
	}		       	
    }
  
}
