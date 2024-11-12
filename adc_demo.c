#define RED     ANSI_ESC(41)                                    #define GREEN   ANSI_ESC(42)                                    #define YELLOW  ANSI_ESC(43)                                    #define BLUE    ANSI_ESC(44)                                    #define MAGENTA ANSI_ESC(45)                                    #define CYAN    ANSI_ESC(46)                                    #define WHITE   ANSI_ESC(47)                                    #define NORMAL  ANSI_ESC(0)                                                                                                                                                                                                                                     void draw_text(char* buf){                                                                                                          gl_draw_string(10, 10, "SCORE", GL_RED);                        gl_draw_string(10, 36, "1999", GL_RED);
                                                                    gl_draw_string(84, 10, "TM", GL_WHITE);
    gl_draw_rect(84, 36,70,30, gl_color(0x43, 0x48, 0xca));         gl_draw_string(84, 36, buf, GL_WHITE);

    //gl_draw_string(126, 10, "LAP", GL_GREEN);
    //gl_draw_string(126, 36, "33", GL_GREEN);

    //gl_draw_string(182, 10, "SPEED", GL_BLACK);
    //gl_draw_string(182, 36, "240", GL_BLACK);


}


void draw_building(int offset, int HEIGHT, int color){
        gl_draw_rect(10+offset,(HEIGHT/2)-120, 60, 120, color);
        gl_draw_rect(20+offset,(HEIGHT/2)-110, 10, 10, GL_WHITE);
        gl_draw_rect(50+offset,(HEIGHT/2)-110, 10, 10, GL_WHITE);
        gl_draw_rect(20+offset,(HEIGHT/2)-90, 10, 10, GL_WHITE);        gl_draw_rect(50+offset,(HEIGHT/2)-90, 10, 10, GL_WHITE);        gl_draw_rect(20+offset,(HEIGHT/2)-70, 10, 10, GL_WHITE);

        gl_draw_rect(50+offset,(HEIGHT/2)-70, 10, 10, GL_WHITE);        gl_draw_rect(20+offset,(HEIGHT/2)-50, 10, 10, GL_WHITE);                                                                        gl_draw_rect(50+offset,(HEIGHT/2)-50, 10, 10, GL_WHITE);        gl_draw_rect(20+offset,(HEIGHT/2)-30, 10, 10, GL_WHITE);                                                                        gl_draw_rect(50+offset,(HEIGHT/2)-30, 10, 10, GL_WHITE);        gl_draw_rect(35+offset,(HEIGHT/2)-15, 10, 15, GL_YELLOW);
}


void erase_building(int offset, int HEIGHT){
        gl_draw_rect(10+offset,(HEIGHT/2)-120, 60, 120, gl_color
(0x43, 0x48, 0xca));
}


void draw_car(void) {
        gl_draw_rect(315, 485, 160, 65, GL_RED);
        gl_draw_rect(315, 475, 160, 10, GL_ORANGE);
        gl_draw_rect(335, 445, 125, 30, GL_RED);
        gl_draw_rect(475, 490, 35, 70, GL_BLACK);
        gl_draw_rect(510, 490, 5, 5, GL_YELLOW);
        gl_draw_rect(510, 555, 5, 5, GL_YELLOW);
        gl_draw_rect(280, 490, 35, 70, GL_BLACK);
        gl_draw_rect(275, 490, 5, 5, GL_YELLOW);
        gl_draw_rect(275, 555, 5, 5, GL_YELLOW);
        gl_draw_rect(460, 445, 15, 20, GL_BLACK);
        gl_draw_rect(475, 445, 3, 3, GL_YELLOW);
        gl_draw_rect(475, 462, 3, 3, GL_YELLOW);
        gl_draw_rect(320, 445, 15, 20, GL_BLACK);
        gl_draw_rect(317, 445, 3, 3, GL_YELLOW);
        gl_draw_rect(317, 462, 3, 3, GL_YELLOW);
}


void create_road(void) {
    gl_draw_rect(100, 225, 600, 375, gl_color(0x60, 0x60, 0x60));

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
}


void draw_car1(int offset){
        if (100+offset > 100 && 100+offset < 675){
                gl_draw_rect(100+offset,575,25,25,GL_BLACK);

        }

}

void erase_car1(int offset){
        if (100+offset > 100 && 100+offset < 675){
                gl_draw_rect(100+offset,575,25,25,gl_color(0x60,0x60,0x60));

        }
}



void update_screen1(int curr_reading, unsigned long time){
        static int previous_sec = 0;
        char buf[MAX_LEN];
        size_t bufsize = sizeof(buf);
        static int prev_reading = 0;
        unsigned_to_base(buf, bufsize, time, 10, 0);
        if (previous_sec != time){
                previous_sec = time;
                draw_text(buf);
        }
        if (prev_reading != curr_reading && prev_reading != curr_reading + 1 && prev_reading != curr_reading - 1){
                erase_car1(prev_reading);
                prev_reading = curr_reading;
                draw_car1(curr_reading);
        }
}



void main(void)  {
    // Initialize everything:

    uart_init();
    gpio_init();                                                       
    mcp3008_init();
    const int WIDTH = 800;                                                                                                  
    const int HEIGHT = 600;                                                                                                 gl_init(WIDTH, HEIGHT, GL_SINGLEBUFFER);
                                                                    // initialize time
    unsigned long ticks = timer_get_ticks() + (24*1000000);                                                                         // draw first scene
    gl_clear(gl_color(0x43, 0x48, 0xca));
    gl_draw_rect(0, HEIGHT/2, WIDTH , HEIGHT/2 , gl_color(0x80,0x80,0x80));
    draw_car();
    create_road();
    draw_car1(0);

    int seconds = 0;
    int previous_seconds = 0;
    int potentiometer;

    while (1){
        if (timer_get_ticks() >= ticks){
              previous_seconds = seconds;
              seconds++;
              ticks = timer_get_ticks()+(24*1000000);
        }
        potentiometer = mcp3008_read(1);
        potentiometer = (potentiometer >> 1);
        update_screen1(potentiometer,seconds);
    }
}
