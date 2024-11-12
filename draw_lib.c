/* Lauren Owens, Jael Lopez-Saucedo
   June 7, 2024
   Final Project
   Professor Chris Gregg

   This file contains the drawing and graphics functions for the Shoebox racing game for cars, obstacles, and text. 
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
#include "i2s.h"
#include "audio.h"
#include "dma.h"


void draw_car(int offset) {
	if ( offset < 441){
		gl_draw_rect(130 + offset, 530, 100, 45, GL_RED); //main rect
		gl_draw_rect(130 + offset, 525, 100, 5, GL_ORANGE); // divider rect
		gl_draw_rect(140 + offset, 500, 80, 25, GL_RED); //top rect

		gl_draw_rect(230 + offset, 530, 25, 50, GL_BLACK); //right back tire
		gl_draw_rect(255 + offset, 530, 5, 5, GL_YELLOW); //right back upper bolt
		gl_draw_rect(255 + offset, 575, 5, 5, GL_YELLOW); //right back lower bolt
		gl_draw_rect(105 + offset, 530, 25, 50, GL_BLACK); //left back tire
		//gl_draw_rect(100 + offset, 530, 5, 5, GL_YELLOW); //left back back upper bolt
		//gl_draw_rect(100 + offset, 575, 5, 5, GL_YELLOW); //right back lower bolt

		gl_draw_rect(220 + offset, 500, 10, 15, GL_BLACK); //right front tire
		//gl_draw_rect(230 + offset, 500, 3, 3, GL_YELLOW); //right front upper bolt
		//gl_draw_rect(230 + offset, 512, 3, 3, GL_YELLOW); //right front lower bolt

		gl_draw_rect(130 + offset, 500, 10, 15, GL_BLACK); //left front tire
		//gl_draw_rect(127 + offset, 500, 3, 3, GL_YELLOW); //right front upper bolt
		//gl_draw_rect(127 + offset, 512, 3, 3, GL_YELLOW); //right front lower bolt
	}
}


void erase_car(int reading) {
    if (reading < 441){
    	gl_draw_rect(100, 500, 600, 700, gl_color(0x60, 0x60, 0x60));
    }
}



void draw_obstacle_small(int lane) {
    if (lane == 0) {
        gl_draw_rect(196, 280, 16, 16, GL_BLACK);
        gl_draw_rect(197, 281, 15, 15, GL_RED);
        gl_draw_rect(206, 283, 2, 12, gl_color(0xed, 0xd6, 0x05)); 
    }
    if (lane == 1) {
        gl_draw_rect(396, 280, 16, 16, GL_BLACK);
        gl_draw_rect(397, 281, 15, 15, GL_RED);
        gl_draw_rect(406, 283, 2, 12, gl_color(0xed, 0xd6, 0x05)); 
    }
    if (lane == 2) {
        gl_draw_rect(596, 280, 16, 16, GL_BLACK);
        gl_draw_rect(597, 281, 15, 15, GL_RED);
        gl_draw_rect(606, 283, 2, 12, gl_color(0xed, 0xd6, 0x05)); 
    }
}

void draw_mango_small(int lane) {
    if (lane == 0) {
        gl_draw_rect(196, 280, 16, 16, GL_BLACK);
        gl_draw_rect(197, 281, 15, 15, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(206, 283, 2, 12, gl_color(0xf5, 0x86, 0x07)); 
    }
    if (lane == 1) {
        gl_draw_rect(396, 280, 16, 16, GL_BLACK);
        gl_draw_rect(397, 281, 15, 15, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(406, 283, 2, 12, gl_color(0xf5, 0x86, 0x07)); 
    }
    if (lane == 2) {
        gl_draw_rect(596, 280, 16, 16, GL_BLACK);
        gl_draw_rect(597, 281, 15, 15, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(606, 283, 2, 12, gl_color(0xf5, 0x86, 0x07)); 
    }
}

void erase_obj_small(int lane) {
    if (lane == 0) {
        gl_draw_rect(196, 280, 16, 16, gl_color(0x60, 0x60, 0x60));
    }
    if (lane == 1) {
        gl_draw_rect(396, 280, 16, 16, gl_color(0x60, 0x60, 0x60));
    }
    if (lane == 2) {
        gl_draw_rect(596, 280, 16, 16, gl_color(0x60, 0x60, 0x60));
    } 
}

void draw_obstacle_medium(int lane) {
    if (lane == 0) {
        gl_draw_rect(166, 400, 45, 45, GL_BLACK);
        gl_draw_rect(167, 401, 44, 44, GL_RED);
        gl_draw_rect(199, 404, 4, 40, gl_color(0xed, 0xd6, 0x05));
    }  
    if (lane == 1) {
        gl_draw_rect(366, 400, 45, 45, GL_BLACK);
        gl_draw_rect(367, 401, 44, 44, GL_RED);
        gl_draw_rect(399, 404, 4, 40, gl_color(0xed, 0xd6, 0x05));

    }
    if (lane == 2) {
        gl_draw_rect(566, 400, 45, 45, GL_BLACK);
        gl_draw_rect(567, 401, 44, 44, GL_RED);
        gl_draw_rect(599, 404, 4, 40, gl_color(0xed, 0xd6, 0x05));
    }
}


void draw_mango_medium(int lane) {
    if (lane == 0) {
        gl_draw_rect(166, 400, 45, 45, GL_BLACK);
        gl_draw_rect(167, 401, 44, 44, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(199, 404, 4, 40, gl_color(0xf5, 0x86, 0x07));
    }  
    if (lane == 1) {
        gl_draw_rect(366, 400, 45, 45, GL_BLACK);
        gl_draw_rect(367, 401, 44, 44, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(399, 404, 4, 40, gl_color(0xf5, 0x86, 0x07));

    }
    if (lane == 2) {
        gl_draw_rect(566, 400, 45, 45, GL_BLACK);
        gl_draw_rect(567, 401, 44, 44, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(599, 404, 4, 40, gl_color(0xf5, 0x86, 0x07));
    }
}

void erase_obj_medium(int lane) {
    if (lane == 0) {
        gl_draw_rect(166, 400, 45, 45, gl_color(0x60, 0x60, 0x60));
    }
    if (lane == 1) {
        gl_draw_rect(366, 400, 45, 45, gl_color(0x60, 0x60, 0x60));
    }
    if (lane == 2) {
        gl_draw_rect(566, 400, 45, 45, gl_color(0x60, 0x60, 0x60));
    }
}

void draw_obstacle_large(int lane){
    if (lane == 0) {
        gl_draw_rect(166, 500, 60, 60, GL_BLACK);
        gl_draw_rect(167, 501, 59, 59, GL_RED);
        gl_draw_rect(209, 506, 6, 50, gl_color(0xed, 0xd6, 0x05));
    }
    if (lane == 1) {
        gl_draw_rect(366, 500, 60, 60, GL_BLACK);
        gl_draw_rect(367, 501, 59, 59, GL_RED);
        gl_draw_rect(409, 506, 6, 50, gl_color(0xed, 0xd6, 0x05));
    }
    if (lane == 2) {
        gl_draw_rect(566, 500, 60, 60, GL_BLACK);
        gl_draw_rect(567, 501, 59, 59, GL_RED);
        gl_draw_rect(609, 506, 6, 50, gl_color(0xed, 0xd6, 0x05));
    }
}

void draw_mango_large(int lane){
    if (lane == 0) {
        gl_draw_rect(166, 500, 60, 60, GL_BLACK);
        gl_draw_rect(167, 501, 59, 59, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(209, 506, 6, 50, gl_color(0xf5, 0x86, 0x07));
    }
    if (lane == 1) {
        gl_draw_rect(366, 500, 60, 60, GL_BLACK);
        gl_draw_rect(367, 501, 59, 59, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(409, 506, 6, 50, gl_color(0xf5, 0x86, 0x07));
    }
    if (lane == 2) {
        gl_draw_rect(566, 500, 60, 60, GL_BLACK);
        gl_draw_rect(567, 501, 59, 59, gl_color(0xff, 0xc2, 0x0e));
        gl_draw_rect(609, 506, 6, 50, gl_color(0xf5, 0x86, 0x07));
    }
}

void erase_obj_large(int lane) {
    if (lane == 0) {
        gl_draw_rect(166, 500, 60, 60, gl_color(0x60, 0x60, 0x60));
    }
    if (lane == 1) {
        gl_draw_rect(366, 500, 60, 60, gl_color(0x60, 0x60, 0x60));
    }
    if (lane == 2) {
        gl_draw_rect(566, 500, 60, 60, gl_color(0x60, 0x60, 0x60));
    }
}


void erase_start_banner(void){
    int WIDTH = 800/4; 
    int HEIGHT =600/4;
    gl_draw_rect(200, HEIGHT, 400, 100, gl_color(0x43, 0x48, 0xca));
}

void draw_start_banner(void){
    int WIDTH = 800; 
    int HEIGHT = 600;
    gl_draw_rect(WIDTH/4, HEIGHT/4, 400, 100, GL_ORANGE);
    gl_draw_string(WIDTH/4+160,HEIGHT/4+40,"START", GL_BLACK);
    gl_draw_rect(WIDTH/4,HEIGHT/4, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+25,HEIGHT/4, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4,HEIGHT/4+25, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+25,HEIGHT/4+25, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4,HEIGHT/4+50, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+25,HEIGHT/4+50, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4,HEIGHT/4+75, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+25,HEIGHT/4+75, 25,25,GL_WHITE);

    gl_draw_rect(WIDTH/4+50,HEIGHT/4, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+75,HEIGHT/4, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+50,HEIGHT/4+25, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+75,HEIGHT/4+25, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+50,HEIGHT/4+50, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+75,HEIGHT/4+50, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+50,HEIGHT/4+75, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+75,HEIGHT/4+75, 25,25,GL_WHITE);

    gl_draw_rect(WIDTH/4+300,HEIGHT/4, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+25+300,HEIGHT/4, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+300,HEIGHT/4+25, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+25+300,HEIGHT/4+25, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+300,HEIGHT/4+50, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+25+300,HEIGHT/4+50, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+300,HEIGHT/4+75, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+25+300,HEIGHT/4+75, 25,25,GL_WHITE);

    gl_draw_rect(WIDTH/4+50+300,HEIGHT/4, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+75+300,HEIGHT/4, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+50+300,HEIGHT/4+25, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+75+300,HEIGHT/4+25, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+50+300,HEIGHT/4+50, 25,25,GL_WHITE);
    gl_draw_rect(WIDTH/4+75+300,HEIGHT/4+50, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+50+300,HEIGHT/4+75, 25,25,GL_BLACK);
    gl_draw_rect(WIDTH/4+75+300,HEIGHT/4+75, 25,25,GL_WHITE);
}


void draw_text(char* buf){                                                                                                          
    gl_draw_string(114, 10, "TM", GL_WHITE);
    gl_draw_rect(114, 36,70,30, gl_color(0x43, 0x48, 0xca));         
    gl_draw_string(114, 36, buf, GL_WHITE);
}


void erase_score(void){
	gl_draw_rect(10, 36,70,30, gl_color(0x43, 0x48, 0xca));
}

