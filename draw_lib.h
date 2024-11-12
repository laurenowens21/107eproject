
#include "uart.h"
#include "mymodule.h"
#include "gl.h"
#include "fb.h"
#include "font.h"
#include "myprogram.h"
#include "timer.h"
#include "printf.h"
#include "mcp3008.h"
#include "malloc.h"
#include "i2s.h"
#include "audio.h"
#include "dma.h"




/*Draws the car avatar at an offset with 0 being the left boundary of the road.  
@Params: offset: position relative to the left boundary for the car to be drawn 
@Return: void*/
void draw_car(int offset);

/*Wipe the car from the last row to change the car position with new potentiometer reading. 
@Params: reading: potentiometer reading to determine when to wipe the car
@Return: void*/
void erase_car(int reading);

/*Draws the small version of the mango in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn 
@Return: void*/
void draw_mango_small(int lane);

/*Draws the small version of the obstacle in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn 
@Return: void*/
void draw_obstacle_small(int lane);

/*Erases the small version of the mango and obstacle in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn 
@Return: void*/
void erase_obj_small(int lane);

/*Draws the medium version of the mango in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn 
@Return: void*/
void draw_mango_medium(int lane);

/*Draws the medium version of the obstacle in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn 
@Return: void*/
void draw_obstacle_medium(int lane);

/*Erases the medium version of the mango and obstacle in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn 
@Return: void
*/
void erase_obj_medium(int lane);

/*Draws the large version of the mango in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn
@Return: void */
void draw_mango_large(int lane);

/*Draws the large version of the obstacle in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn
@Return: void */
void draw_obstacle_large(int lane);

/*Erases the large version of the mango and obstacle in the designated lane. 
Includes offsets within the function to draw it at appropriate x and y coordinate to be the farthest position.
@Params: lane: lane to be drawn 
@Return: void
*/
void erase_obj_large(int lane);

/*Wipes the start banner when the game starts. 
@Params: void
@Return: void
*/
void erase_start_banner(void);

/*Draws the start banner when the game starts. 
@Params: void
@Return: void
*/
void draw_start_banner(void);


/*Draws text for the time into the appropriate buffer to be displayed
@Params: char* buf: string of time to be updated
@Return: void
*/
void draw_text(char* buf);

/*Erases score to be overwritten once mango is collected
@Params: void
@Return: void
*/
void erase_score(void);


