/* Lauren Owens, Jael Lopez-Saucedo
June 7, 2024
Final Project
Professor Chris Gregg

This file contains the program to drive our game "Shoebox Racing"
*/

#include "uart.h"
#include "mymodule.h"
#include "gl.h"
#include "fb.h"
#include "font.h"
#include "myprogram.h"
#include "timer.h"
#include "printf.h"
#include "draw_lib.h"
#include "mcp3008.h"
#include "malloc.h"
#include "sound-headers/race_sound.h"
#include "i2s.h"
#include "audio.h"
#include "dma.h"

#define MAX_LEN 1024
#define MAX_OUTPUT_LEN 1024

struct game {
    int sec; 
    int score;
    int car_pos;
    int obstacle_pos[3];
    bool game_is_playing;
    bool lost;
    bool won;
};


/*Draws the score (current number of mangos) to the appropriate place on screen
@Params: g - current game instance
@Return: void
*/
void draw_score(struct game *g);


/*  Adjusts the bolts of the car to give the illusion that the car is moving
    Draws bolts at a designated upper or lower location
    @Params: offset - offset position of the car to denote where the bolts are
            start - used to determine the alternating nature of the function
    @Return: void
*/
void move_car(int offset, bool start);


/*  Adjusts the rectangles on the border of the road to add to visual illusion that the car is moving.
    Switches rectangles from red->white->red to white->red-> white
    @Params: start - used to determine the alternating nature of the function
    @Return: void
*/
void create_boundary(bool start);

/*  Creates road and grass barrier
    @Params: void
    @Return: void
*/
void create_road(void);


/*Draws the score (current number of mangos) to the appropriate place on screen
@Params: g - current game instance
@Return: void
*/
void draw_score(struct game *g);

/*  Loads the starting screen for the game with values initialized to 0 and start banner displayed
    Adjusts game member variables to note that the game is playing
    @Params: g - current game instance
    @Return: void
*/

void load_start_screen(struct game *g);

/*  Loads the losing screen: Variables cleared and "You lose" displayed
    Adjusts game member variables to note that the game is not playing
    @Params: g - current game instance
    @Return: void
*/
void trigger_finish_screen(struct game *g);

/*  Loads the winning screen: Variables cleared and "You win" displayed
    Adjusts game member variables to note that the game is no longer playing
    @Params: g - current game instance
    @Return: void
*/
void trigger_win_screen(struct game *g);

/*  Adjusts the rectangles on the border of the road to add to visual illusion that the car is moving.
    Switches rectangles from red->white->red to white->red-> white
    @Params: curr_reading - current potentiometer of steering wheel reading
             time - current time from timer
             bound_start - x coordinate of the boundaries (red and white rectangles)
             car_start - x coordinate of the left most point on the car 
             g - current game instance
    @Return: void
*/
void update_screen(int curr_reading, unsigned long time,bool bound_start, bool car_start, struct game* g);


/* Updates the obstacles and mangoes present in the road. Uses a global pointer variable to mark where we are at in the road and display appropriate features.
It will then trickle these objects down until it hits the position of the car. 
It will then load these objects into a member variable that is used to determine collisions.
@Params: time: current tick value from timer
        bound_start: x coordinate of the boundaries
        car_start: x coordinate of the left most point of the car
        g - current game instance
@Return: void
 */
void update_road(unsigned long time, bool bound_start, bool car_start, struct game* g);


/* Detects if there is a collision with an object (mango or obstacle) and updates appropriate parameters, writing these to screen*
    @Params:   g - current game instance
    @Return: void
*/
void car_collision(struct game* g);


int unsigned_to_base1(char *buf, size_t bufsize, unsigned long val, int base, size_t min_width);

int road[176][3]= {
   {1, 0, 0},
   {0, 0, 0},
   {0, 1, 0}, //3
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0}, //6
   {1, 0 ,0},
   {0, 0, 0},
   {0, 0, 0}, //9
   {0, 0, 0},
   {0, 1, 0},
   {0, 0, 0}, //12
   {0, 0, 0},
   {0, 0, 1},
   {0, 0, 0}, //15
   {0, 1, 0},
   {0, 0, 0},
   {1, 0, 0}, //18
   {0, 0, 0},
   {0, 2, 0},
   {0, 0, 0}, //21
   {0, 0, 0}, 
   {0, 0, 1},
   {0, 0, 0},
   {0, 1, 0}, //25
   {0, 0, 0},
   {2, 0, 0},
   {0, 0, 0}, //28
   {0, 1, 0},
   {0, 0, 0},
   {0, 1, 0}, //31
   {0, 0, 0},
   {1, 0, 0},
   {0, 0, 0}, //34
   {0, 2, 0},
   {0, 0, 0},
   {0, 0, 1}, //37
   {0, 0, 0},
   {0, 2, 0},
   {0, 0, 0}, //40
   {0, 1, 0},
   {0, 0, 0},
   {1, 0, 0}, //43
   {0, 0, 0},
   {0, 2, 0},
   {0, 0, 0},
   {0, 1, 0}, //47
   {0, 0, 0},
   {0, 0, 1},
   {0, 2, 0}, //50
   {1, 0, 0},
   {0, 0, 0},
   {0, 0, 1}, //53
   {0, 1, 0},
   {0, 0, 0},
   {2, 0, 0}, //56
   {0, 0, 0},
   {0, 0, 0},
   {0, 1, 0}, //59
   {1, 0, 0},
   {0, 0, 0},
   {0, 0, 2}, //62
   {0, 0, 0},
   {0, 0, 1},
   {0, 1, 0}, //65
   {0, 0, 0},
   {0, 0, 0},
   {1, 0, 0},
   {0, 0, 0}, //69
   {0, 1, 0},
   {2, 0, 0},
   {0, 0, 0}, //72
   {0, 1, 0},
   {0, 0, 0},
   {1, 0, 0}, //75
   {0, 0, 1},
   {0, 0 ,0},
   {1, 2, 0}, //78
   {0, 0, 0},
   {0, 1, 0},
   {0, 0, 0}, //81
   {0, 1, 0},
   {0, 0, 1},
   {0, 0, 0}, //84
   {2, 1, 0},
   {0, 0, 0},
   {0, 0, 1}, //87
   {0, 2, 0},
   {0, 0, 0},
   {1, 1, 0},
   {0, 0, 0}, //91
   {0, 2, 0},
   {0, 1, 0},
   {0, 0, 0}, //94
   {1, 0, 1},
   {0, 0, 0},
   {1, 0, 1}, //97
   {0, 0, 0},
   {0, 2, 0},
   {1, 0, 0}, //100
   {0, 0, 0},
   {1, 0, 0},
   {0, 1, 0}, //103
   {0, 0, 0},
   {2, 0, 1},
   {0, 0, 0}, //106
   {1, 0, 1},
   {0, 0, 0},
   {1, 0, 0}, //109
   {0, 0, 0},
   {1, 1, 0},
   {0, 0, 0},
   {0, 1, 0}, //113
   {0, 0, 2},
   {1, 0, 0},
   {0, 0, 0}, //116
   {0, 1, 0},
   {1, 0, 0},
   {0, 0, 1}, //119
   {0, 2, 0},
   {0, 0, 0},
   {0, 1, 0}, //122
   {2, 0, 0},
   {0, 1, 0},
   {1, 0, 0}, //125
   {0, 0, 1},
   {0, 0, 0},
   {0, 0, 1}, //128
   {0, 0, 0},
   {0, 1, 0},
   {0, 0, 0}, //131
   {1, 0, 0},
   {0, 0, 1},
   {1, 0, 1},
   {0, 0, 0}, //135
   {0, 0, 2},
   {0, 1, 0},
   {0, 0, 0}, //138
   {1, 0, 0},
   {0, 2, 0},
   {0, 0, 1}, //141
   {0, 1, 0},
   {1, 0, 0},
   {1, 0, 0}, //144
   {2, 0, 1},
   {0, 1, 0},
   {0, 0, 0}, //147
   {0, 1, 0},
   {1, 0, 0},
   {0, 1, 0}, //150
   {0, 0, 0},
   {1, 0, 0},
   {0, 0, 1}, //153
   {0, 0, 0},
   {0, 1, 0},
   {0, 1, 0},
   {1, 0, 0}, //157
   {0, 0, 0},
   {0, 0, 0},
   {0, 1, 0}, //160
   {0, 0, 0},
   {1, 0, 0},
   {0, 0, 1}, //163
   {0, 0, 0},
   {0, 1, 0},
   {0, 0, 0}, //166
   {0, 1, 0},
   {2, 0, 0},
   {0, 1, 0}, //169
   {0, 0, 1},
   {0, 2, 0},
   {1, 1, 0}, //172
   {0, 0, 0},
   {0, 0, 0},
   {0, 0, 0}, //175
   {0,0,0}
};

int* traverse_ptr = road[0]; //initializes traverse pointer to the start of the road
int* road_end_ptr = &road[176][3];
int display_small[3] = {0,0,0}; //display arrays for obstacles
int display_medium[3] = {0,0,0};
int display_large[3] = {0,0,0};
bool start = 0;

/*Updates the road by displaying the obstacles at their appropriate place, 
Uses traverse pointer to determine what row to display
Copies all elements from previous array to following two arrays 
@ Params: time -  current times
          bound_start - current x coordinate to boundary
          car_start - current x coordinate of car
          g - current game instance
@Return: void
*/
void update_road(unsigned long time, bool bound_start, bool car_start, struct game* g) {
   if (traverse_ptr != NULL) {
       for (int i = 0; i <= 2; i++) { //copies all elements to the uppermost row on the road in smallest size
           display_small[i] = traverse_ptr[i];
       }

       for (int i = 0; i <= 2; i++) {
           if (display_small[i] == 1) { //if array holds a 1, display a mango
               draw_mango_small(i);
           } if (display_small[i] == 2) { //if array holds a 1, display a obstacle
               draw_obstacle_small(i);
           }
           if (display_small[i] == 0) { //if array holds a 1, do not display anything
               erase_obj_small(i);
           }
       }

       for (int i = 0; i <= 2; i++) {
           if (display_medium[i] == 1) {
               draw_mango_medium(i);
           } if (display_medium[i] == 2) {
               draw_obstacle_medium(i);
           }
           if (display_medium[i] == 0) {
               erase_obj_medium(i);
           }
       }

       for (int i = 0; i <= 2; i++) {
           if (display_large[i] == 1) {
                if (i == 0 && g->car_pos > 226) { //prevents overriding over the car
                    draw_mango_large(i);
                } if (i == 1 && (g->car_pos > 426 || g -> car_pos + 180 < 366)) { 
                    draw_mango_large(i);
                } if (i == 2 && (g->car_pos < 566 - 180)) {
                    draw_mango_large(i);
                }
               g -> obstacle_pos[i] = 1; //copies object to an array to determine if there is a collision
            }
            if (display_large[i] == 2) {
                if (i == 0 && g->car_pos > 226) {
                    draw_obstacle_large(i);
                } if (i == 1 && (g->car_pos > 426 || g -> car_pos + 180 < 366)) {
                    draw_obstacle_large(i);
                } if (i == 2 && (g->car_pos < 566 - 180)) {
                    draw_obstacle_large(i);
                }
                g -> obstacle_pos[i] = 2; 
            } if (display_large[i] == 0) {
                if (i == 0 && g->car_pos > 226) {
                    erase_obj_large(i);
                } if (i == 1 && (g->car_pos > 426 || g -> car_pos + 180 < 366)) {
                    erase_obj_large(i);
                } if (i == 2 && (g->car_pos < 566 - 180)) {
                    erase_obj_large(i);;
                }
                g -> obstacle_pos[i] = 0; 
            }
        }

       for (int i = 0; i <=2; i++) {
           display_large[i] = display_medium[i];
        }

       for (int i = 0; i <=2; i++) {
           display_medium[i] = display_small[i];
       }

       create_boundary(bound_start);

   }
}

void draw_score(struct game* g){
	erase_score();
	char buf[MAX_LEN];
    size_t bufsize = sizeof(buf);
    static int prev_reading = 0;
    unsigned_to_base1(buf, bufsize, g->score, 10, 0);
	gl_draw_string(10, 36, buf, GL_RED);	
}

void load_start_screen(struct game *g) {
    g->game_is_playing = 0; //denote game is playing
    draw_start_banner();
    create_road();

    gl_draw_string(10, 10, "MANGOES", GL_RED);
    gl_draw_string(10, 36, "0", GL_RED); 

    gl_draw_string(114, 10, "TM", GL_WHITE);
    gl_draw_string(114, 36, "0", GL_WHITE);

    gl_draw_string(182, 10, "SPEED", GL_BLACK);
    gl_draw_string(182, 36, "100", GL_BLACK);

    draw_car(220); //draws car at center
}

void trigger_finish_screen(struct game *g) {
    g->game_is_playing = 0; //denote game is no longer playing
    g->lost = 1;
    gl_clear(gl_color(0x43, 0x48, 0xca));
    gl_draw_string(50, 50, "YOU LOSE", gl_color(0x80, 0x80, 0x80));
}


void trigger_win_screen(struct game *g) {
    g->game_is_playing = 0; //denote game is no longer playing
    g->won = 1;
    gl_clear(gl_color(0x43, 0x48, 0xca));
    gl_draw_string(50, 50, "YOU WIN!", gl_color(0x80, 0x80, 0x80));
}


void update_screen(int curr_reading, unsigned long time,bool bound_start, bool car_start, struct game* g){     
	static int previous_sec = 0;   //previous time 
	char buf[MAX_LEN];
	size_t bufsize = sizeof(buf);
	static int prev_reading = 0;         
	unsigned_to_base1(buf, bufsize, time, 10, 0);     
	if (previous_sec != time){      
		previous_sec = time;        
		draw_text(buf);    //read in time to buffer and draw it
	}             
	if (prev_reading != curr_reading && prev_reading != curr_reading + 1 && prev_reading != curr_reading - 1 && prev_reading != curr_reading + 2 && prev_reading != curr_reading - 2){      
		erase_car(curr_reading);  //erase car at current positiong   
		prev_reading = curr_reading;   
		draw_car(curr_reading); 
		move_car(curr_reading, car_start);
		g->car_pos = curr_reading+100;	 //offset to be within the boundaries
		car_collision(g); //see if there is a collision
        draw_score(g); //update the statistics at top
	} 	
}

void car_collision(struct game* g){
        if (g->obstacle_pos[0] == 1 && (g->car_pos > 160 && g->car_pos < 220)){ // detects if there is a mango in lane 1
			g->score += 1;	//increase score		
			return;
		}
                       
		if (g->obstacle_pos[1] == 1 && (g->car_pos > 367 && g->car_pos < 427)){ // detects if there is a obstacle in lane 1
			g->score += 1;
			return;
		}
			      
	    if (g->obstacle_pos[2] == 1 && (g->car_pos > 567 && g->car_pos < 627)){ 
            g->score += 1;
			return;
        }
			
		if (g->obstacle_pos[0] == 2 && (g->car_pos > 160 && g->car_pos < 220)){ 
            trigger_finish_screen(g);  //game over, denote that we have hit an obstacle   
			return;			
		}

		if (g->obstacle_pos[1] == 2 && (g->car_pos > 367 && g->car_pos < 427)){                       
			trigger_finish_screen(g);
			return;
		}

        if (g->obstacle_pos[2] == 2 && (g->car_pos > 567 && g->car_pos < 627)){
            trigger_finish_screen(g);
		    return;
        }			

}

void move_car(int offset, bool start) {
   if (offset < 441){
   if (start) { //used for alternating
       gl_draw_rect(255 + offset, 530, 5, 5, gl_color(0x60, 0x60, 0x60)); //ERASEright back upper bolt
       gl_draw_rect(255 + offset, 575, 5, 5, gl_color(0x60, 0x60, 0x60)); // ERASE right back lower bolt


       gl_draw_rect(100 + offset, 530, 5, 5, gl_color(0x60, 0x60, 0x60)); //ERASE left back upper bolt
       gl_draw_rect(100 + offset, 575, 5, 5, gl_color(0x60, 0x60, 0x60)); //ERASE right back lower bolt


       gl_draw_rect(230 + offset, 500, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE right front upper bolt
       gl_draw_rect(230 + offset, 512, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE right front lower bolt


       gl_draw_rect(127 + offset, 500, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE left front upper bolt
       gl_draw_rect(127 + offset, 512, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE left front lower bolt


       gl_draw_rect(255 + offset, 535, 5, 5, GL_YELLOW); //DRAW right back upper bolt
       gl_draw_rect(255 + offset, 570, 5, 5, GL_YELLOW); //DRAW right back lower bolt


       gl_draw_rect(100 + offset, 535, 5, 5, GL_YELLOW); //DRAW left back upper bolt
       gl_draw_rect(100 + offset, 570, 5, 5, GL_YELLOW); //DRAW right back lower bolt


       gl_draw_rect(230 + offset, 502, 3, 3, GL_YELLOW); //DRAW right front upper bolt
       gl_draw_rect(230 + offset, 510, 3, 3, GL_YELLOW); //DRAW right front lower bolt


       gl_draw_rect(127 + offset, 502, 3, 3, GL_YELLOW); //DRAWleft front upper bolt
       gl_draw_rect(127 + offset, 510, 3, 3, GL_YELLOW); //DRAW left front lower bolt

   } else {
       gl_draw_rect(255 + offset, 535, 5, 5, gl_color(0x60, 0x60, 0x60)); //ERASE right back upper bolt
       gl_draw_rect(255 + offset, 570, 5, 5, gl_color(0x60, 0x60, 0x60)); //ERASE right back lower bolt


       gl_draw_rect(100 + offset, 535, 5, 5, gl_color(0x60, 0x60, 0x60)); //ERASE left back upper bolt
       gl_draw_rect(100 + offset, 570, 5, 5, gl_color(0x60, 0x60, 0x60)); //ERASE right back lower bolt


       gl_draw_rect(230 + offset, 502, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE right front upper bolt
       gl_draw_rect(230 + offset, 510, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE right front lower bolt


       gl_draw_rect(127 + offset, 502, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE left front upper bolt
       gl_draw_rect(127 + offset, 510, 3, 3, gl_color(0x60, 0x60, 0x60)); //ERASE left front lower bolt
      
       gl_draw_rect(255 + offset, 530, 5, 5, GL_YELLOW); //DRAW right back upper bolt
       gl_draw_rect(255 + offset, 575, 5, 5, GL_YELLOW); //DRAW right back lower bolt


       gl_draw_rect(100 + offset, 530, 5, 5, GL_YELLOW); //DRAW left back upper bolt
       gl_draw_rect(100 + offset, 575, 5, 5, GL_YELLOW); //DRAW right back lower bolt


       gl_draw_rect(230 + offset, 500, 3, 3, GL_YELLOW); //DRAW right front upper bolt
       gl_draw_rect(230 + offset, 512, 3, 3, GL_YELLOW); //DRAW right front lower bolt


       gl_draw_rect(127 + offset, 500, 3, 3, GL_YELLOW); //DRAW left front upper bolt
       gl_draw_rect(127 + offset, 512, 3, 3, GL_YELLOW); //DRAW left front lower bolt
   }}
}


void create_boundary(bool start) {
   if (start) { //alternation for rectangles on border of road
    for (int i = 0; i < 15; i++) {
        int y_coord = 225 + (25 * i);
        color_t c;
        if (i %2 == 0) {
           c = GL_RED;


        } else {
            c = GL_WHITE;
        }
        gl_draw_rect(75, y_coord, 25, 25, c);
        gl_draw_rect(700, y_coord, 25, 25, c);
    }
   } else {
    for (int i = 0; i < 15; i++) {
        int y_coord = 225 + (25 * i);
        color_t c;
        if (i %2 == 0) {
           c = GL_WHITE;
        } else {
           c = GL_RED;
        }
        gl_draw_rect(75, y_coord, 25, 25, c);
        gl_draw_rect(700, y_coord, 25, 25, c);
        }
   }
}


void create_road(void) {
    gl_draw_rect(100, 225, 600, 375, gl_color(0x60, 0x60, 0x60)); //road
    gl_draw_rect(0, 225, 100, 375 , gl_color(0x00,0x64,0x00)); //grass barrier
    gl_draw_rect(700, 225, 100, 375 , gl_color(0x00,0x64,0x00)); //grass barrier
    create_boundary(1); //creates red and white boundary
}


int determine_tot_digits1(int base, unsigned long val){                  
    unsigned long val_copy = val;                                   
    int tot_digits = 0;                                             
    if (val == 0){tot_digits++;}                                    
    while (val_copy != 0){                                                  
        tot_digits++;                                                   
        val_copy /= base;                                       
    }                                                               
    return tot_digits;                                      
}


char ul_to_char1(unsigned long val){        
	if (val == 0){return (char)'0';}      
	if (val == 1){return (char)'1';}      
	if (val == 2){return (char)'2';}    
	if (val == 3){return (char)'3';}     
	if (val == 4){return (char)'4';}      
	if (val == 5){return (char)'5';}   
	if (val == 6){return (char)'6';}     
	if (val == 7){return (char)'7';}      
	if (val == 8){return (char)'8';}       
	if (val == 9){return (char)'9';} 
	if (val == 10){return (char)'a';}
	if (val == 11){return (char)'b';}
	if (val == 12){return (char)'c';}
	if (val == 13){return (char)'d';}
	if (val == 14){return (char)'e';}
	if (val == 15){return (char)'f';}
	else{return '0';}
}

int unsigned_to_base1(char *buf, size_t bufsize, unsigned long val, int base, size_t min_width) {
  int num_digits = determine_tot_digits1(base, val);
  char temp_buf[MAX_OUTPUT_LEN];
  temp_buf[num_digits] = '\0';
  unsigned long val_copy = val;

  // Get the digits in the array in the correct order
  for (int i = (num_digits-1); i >= 0 ; i--){
         unsigned long digit_num = (val_copy % base);
         char digit_char = ul_to_char1(digit_num);
         temp_buf[i] = digit_char;
         val_copy /= base;
  }

  // Now do the padding!
  size_t len_pad_temp = min_width;
  if (min_width < num_digits){len_pad_temp = num_digits;};
  char pad_temp_buf[len_pad_temp+1];

  // array for padding and digits
  size_t num_zeros = 0;                                           
  if (min_width > num_digits){num_zeros = min_width - num_digits;}                 
  for(int i = 0; i < num_zeros; i++){          // padd with zeros
    char digit1  = '0';
    pad_temp_buf[i] = digit1;
  }

  int index = 0;
  for (int i = num_zeros; i < (len_pad_temp + 1); i++){ // add the digits
        pad_temp_buf[i] = temp_buf[index];
        index++;
  }

   if (bufsize >0){
    if (bufsize > min_width){                   // everything fits!
        for (int i = 0; i < (len_pad_temp + 1); i++){
            buf[i] = pad_temp_buf[i];
        }
    } else{                                    // not everything fits
        for (int i = 0; i < (bufsize - 1); i++){
            buf[i] = pad_temp_buf[i];
        } buf[bufsize-1] = '\0';
     }
    }
    int tot_chars = min_width;
    if (num_digits > tot_chars){tot_chars = num_digits;}
    return len_pad_temp;
}


void main(void) {
    uart_init();
    i2s_init();
    CHANNEL_TYPE ct = pcm_metadata.mono ? MONO : STEREO;
    audio_init(pcm_metadata.sample_freq, pcm_metadata.block_alignment, ct);

    gpio_init();
    mcp3008_init();
    const int WIDTH = 800;
    const int HEIGHT = 600;
    
    // initial screen
    gl_init(WIDTH, HEIGHT, GL_SINGLEBUFFER);
    gl_clear(gl_color(0x43, 0x48, 0xca)); // create blue color
    struct game cur_game;
    cur_game.sec = 0;
    cur_game.score = 0;
    for (int i = 0; i <= 2; i++) {
        cur_game.obstacle_pos[i] = 0;
    }
    cur_game.car_pos = 220;
    cur_game.game_is_playing = 0;
    struct game* g = &cur_game; //Initializes current game member variable
    load_start_screen(g);
    int potentiometer_gas = mcp3008_read(1);
    printf("Gas: %d", potentiometer_gas);
    int prev_read = 0;
    while (potentiometer_gas != 5) { //Waits for throttle to start
        potentiometer_gas = (potentiometer_gas >> 1);
        potentiometer_gas = mcp3008_read(1);
    }
    g->game_is_playing = 1;
    g->lost = 0;
    g->won = 0;
    erase_start_banner();
    create_road();
    while (g->game_is_playing) { //starts game
        // draw data
	audio_write_i16_dma((uint16_t *)pcm_data, sizeof(pcm_data)/sizeof(pcm_data[0]), pcm_metadata.repeat);
        unsigned long ticks = timer_get_ticks() + (24*1000000);   
        //int seconds = 0;
        //int previous_seconds = 0;
	    int potentiometer_steer = 0;

        while (1){
		if (dma_complete(0)){
		audio_write_i16_dma((uint16_t *)pcm_data, sizeof(pcm_data)/sizeof(pcm_data[0]), pcm_metadata.repeat);
		}
            if (timer_get_ticks() >= ticks){
                g->sec+=1;
                ticks = timer_get_ticks()+(24*1000000);
                update_road(g->sec, start, !start, g);
                //seconds++;
                ticks = timer_get_ticks()+(24*1000000);
                update_road(g->sec, start, !start, g);
                if (traverse_ptr != NULL && traverse_ptr +1 < road_end_ptr) {
                    traverse_ptr += 3; //update row of road
                } else {
                    trigger_win_screen(g);
                    break;
                }
                start = !start; //flip start to alternate boundary
            }
	        potentiometer_steer = mcp3008_read(0); //reads data of steering wheel potentiometer
            potentiometer_steer = (potentiometer_steer >> 1);
            update_screen(potentiometer_steer,g->sec,start,!start, g);

	         if (g -> lost == 1 || g-> won == 1){ //determines when to end game and break out of loop
	    	    break;
	    
	    }
        }

	    if (g -> lost == 1 || g-> won == 1){
		    break;
	}
    }
    if (g-> lost == 1){ //triggers game ending screens
    trigger_finish_screen(g);
    }
    if (g-> won == 1){
    	trigger_win_screen(g);
    }

}

