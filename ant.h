#ifndef ANT_H_
#define ANT_H_

/* COLORS */
#define BLACK 0, 0, 0
#define WHITE 1, 1, 1
#define RED 1, 0, 0

/* SIZES */
#define PIXEL_SIZE 2 /* Pixel drawn size */
#define STEP_SIZE 1 /* The size of the steps of the ant. */
#define MAP_X 400
#define MAP_Y 400
#define FRAME_SKIP 5 /* This defines the amount of frames that are skipped for every draw. */

/* PROGRAM DEFINES */
#define W_WIDTH MAP_X * PIXEL_SIZE /* Window width */
#define W_HEIGHT MAP_Y * PIXEL_SIZE /* Window height */
#define PROGRAM_NAME "Langton's Ant" /* Window name */
#define PROGRAM_LIMIT 1500 /* This defines the amount of draws the program does before quitting. */

typedef struct {
    unsigned int x,y;
    unsigned char direction;
} Ant;

/* PROTOTYPES */
void init(void);
void genMap(int noise);
void drawMap(void);
void drawAnt(void);
void gameLoop(void);
void display(void);

#endif // ANT_H_
